#include "stdafx.h"
#include "kfifo.h"

/**
* fls - find last bit set
* @x: the word to search
*
* This is defined the same way as ffs:
* - return 32..1 to indicate bit 31..0 most significant bit set
* - return 0 to indicate no bits set
*/
#if defined(__GNUC__)
static  int fls(int x)
{
	int r;

	__asm__("bsrl %1,%0\n\t"
		"jnz 1f\n\t"
		"movl $-1,%0\n"
		"1:" : "=r" (r) : "rm" (x));
	return r + 1;
}
#else
static  int fls(int x)
{
	int position;
	int i;
	if (0 != x)
	{
		for (i = (x >> 1), position = 0; i != 0; ++position)
			i >>= 1;
	}
	else
	{
		position = -1;
	}
	return position + 1;
}
#endif
/**
* fls64 - find last bit set in a 64-bit value
* @n: the value to search
*
* This is defined the same way as ffs:
* - return 64..1 to indicate bit 63..0 most significant bit set
* - return 0 to indicate no bits set
*/
static  __u64 fls64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		return fls(h) + 32;
	return  fls(x);
}

static __u64 fls_long(unsigned long l)
{
	if (sizeof(l) == 4)
		return fls(l);
	return fls64(l);
}

static  unsigned long roundup_pow_of_two(unsigned long x)
{
	return 1UL << fls_long(x - 1);
}

/**
* * kfifo_alloc - allocates a new FIFO and its internal buffer
* * @size: the size of the internal buffer to be allocated.
* * @gfp_mask: get_free_pages mask, passed to kmalloc()
* * @lock: the lock to be used to protect the fifo buffer
* *
* * The size will be rounded-up to a power of 2.
* */
struct kfifo *kfifo_alloc(unsigned int size)
{
	unsigned char *buffer;
	struct kfifo *fifo;

	/*
	*       * round up to the next power of 2, since our 'let the indices
	*            * wrap' tachnique works only in this case.
	*                 */
	//保证是2的倍数
	if (size & (size - 1))
	{
		if (size > 0x80000000)
		{
			return NULL;
		}
		size = roundup_pow_of_two(size);
	}
	buffer = (unsigned char *)malloc(size);
	if (!buffer)
		return NULL;

	fifo = (struct kfifo*)malloc(sizeof(struct kfifo));

	if (!fifo)
	{
		free(buffer);
		return NULL;
	}

	fifo->buffer = buffer;
	fifo->size = size;
	fifo->in = fifo->out = 0;

	return fifo;
}

/**
* * kfifo_free - frees the FIFO
* * @fifo: the fifo to be freed.
* */
void kfifo_free(struct kfifo *fifo)
{
	free(fifo->buffer);
	free(fifo);
}

/**
* __kfifo_put - puts some data into the FIFO, no locking version
* @fifo: the fifo to be used.
* @buffer: the data to be added.
* @len: the length of the data to be added.
*
* This function copies at most @len bytes from the @buffer into
* the FIFO depending on the free space, and returns the number of
* bytes copied.
*
* Note that with only one concurrent reader and one concurrent
* writer, you don't need extra locking to use these functions.
*/
unsigned int __kfifo_put(struct kfifo *fifo,
	const unsigned char *buffer, unsigned int len)
{
	unsigned int l;
	//比较存储结构体大小 和剩余可用空间
	//len代表in后面有几个可用空白空间
	len = min(len, fifo->size - fifo->in + fifo->out);

	/* first put the data starting from fifo->in to buffer end */
	//计算出环形队列末尾还剩下多少个空的存储空间
	//l代表in后有多少个存储空间
	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
	memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(fifo->buffer, buffer + l, len - l);

	fifo->in += len;

	return len;
}

/**
* __kfifo_get - gets some data from the FIFO, no locking version
* @fifo: the fifo to be used.
* @buffer: where the data must be copied.
* @len: the size of the destination buffer.
*
* This function copies at most @len bytes from the FIFO into the
* @buffer and returns the number of copied bytes.
*
* Note that with only one concurrent reader and one concurrent
* writer, you don't need extra locking to use these functions.
*/
unsigned int __kfifo_get(struct kfifo *fifo,
	unsigned char *buffer, unsigned int len)
{
	unsigned int l;
	//len代表out后有多少个可读
	len = min(len, fifo->in - fifo->out);

	/* first get the data from fifo->out until the end of the buffer */
	//l代表环形队列后面有多少个空间
	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));

	memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(buffer + l, fifo->buffer, len - l);


	fifo->out += len;

	return len;
}

/**
* __kfifo_reset - removes the entire FIFO contents, no locking version
* @fifo: the fifo to be emptied.
*/
static  void __kfifo_reset(struct kfifo *fifo)
{
	memset(fifo->buffer, 0, fifo->size);
	fifo->in = fifo->out = 0;
}

/**
* __kfifo_len - returns the number of bytes available in the FIFO, no locking version
* @fifo: the fifo to be used.
*/
static  unsigned int __kfifo_len(struct kfifo *fifo)
{
	return fifo->in - fifo->out;
}
