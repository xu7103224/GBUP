#pragma once
#include "kfifo.h"

template<typename T>
class zFifo
{
private:
	kfifo* _kfifo;
public:
	zFifo();
	~zFifo();
	/* zFifo()
	{
	_kfifo = kfifo_alloc(1024);
	}
	~zFifo()
	{
	if(NULL != _kfifo)
	kfifo_free(_kfifo);
	}*/
public:
	bool push(T data);
	T get();
};

template <typename T>
zFifo<T>::zFifo()
{
	_kfifo = kfifo_alloc(8192);
}
template <typename T>
zFifo<T>:: ~zFifo()
{
	if (NULL != _kfifo)
		kfifo_free(_kfifo);
}

template <typename T>
bool zFifo<T>::push(T data)
{
	int len = 0;
	len = __kfifo_put(_kfifo, (const unsigned char *)&data, sizeof(T));

	if (len > 0)
		return true;
	else
		return false;
}

template <typename T>
T zFifo<T>::get()
{
	T data;
	int len = __kfifo_get(_kfifo, (unsigned char *)&data, sizeof(T));
	if (len > 0)
		return data;
	else
		return NULL;
}