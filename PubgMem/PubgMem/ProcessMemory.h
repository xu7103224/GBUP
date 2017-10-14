#pragma once
#include "Winheaders.h"
#include "Macro.h"
#include "Types.h"
#include <vector>
#include "CallResult.h"
namespace PUBG
{
	class ProcessMemory
	{
	public:
		ProcessMemory(class Process* process);
		~ProcessMemory();
		NTSTATUS Read(ptr_t dwAddress, size_t dwSize, PVOID pResult, bool handleholes = false);
		NTSTATUS Write(ptr_t pAddress, size_t dwSize, const void* pData);

		template<class T>
		inline call_result_t<T> Read(ptr_t dwAddress)
		{
			T res;
			auto status = Read(dwAddress, sizeof( T ), &res);
			return call_result_t<T>(res, status);
		}
 
		template<class T>
		inline NTSTATUS Read(ptr_t dwAddress, T& result)
		{
			return Read(dwAddress, sizeof(result), &result);
		};

		template<class T>
		inline NTSTATUS Read(ptr_t dwAddress, T* result, size_t size)
		{
			return Read(dwAddress, size, result);
		}

		template<class T>
		inline NTSTATUS Write(ptr_t dwAddress, const T& data)
		{
			return Write(dwAddress, sizeof(T), &data);
		}


	private:
		ProcessMemory(const ProcessMemory&) = delete;
		ProcessMemory& operator =(const ProcessMemory&) = delete;

	private:
		class Process* _process;    // Owning process object
		class ProcessCore& _core;
	};
}