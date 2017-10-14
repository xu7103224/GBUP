#pragma once
#if _MSC_VER >= 1800

#include <cassert>
namespace PUBG
{
	template<typename T>
	struct call_result_t
	{
		typedef T type;
		NTSTATUS status = STATUS_UNSUCCESSFUL;
		T result_data;
		call_result_t() = default;

		call_result_t(const T& result_, NTSTATUS status_ = STATUS_SUCCESS)
			: status(status_)
			, result_data(result_)
		{
			assert(status_ != STATUS_SUCCESS);
		}

		call_result_t(NTSTATUS status_): status(status_)
		{
			assert(status_ != STATUS_SUCCESS);
		}
		inline bool success() const { return NT_SUCCESS(status); }

	};
}


#endif