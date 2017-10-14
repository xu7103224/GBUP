#include "Process.h"
#include "ProcessMemory.h"

namespace PUBG
{
	ProcessMemory::ProcessMemory(Process* process):
		 _process(process)
		, _core(process->core())
	{
	}

	ProcessMemory::~ProcessMemory()
	{
	}

	NTSTATUS ProcessMemory::Read(ptr_t dwAddress, size_t dwSize, PVOID pResult, bool handleHoles /*= false*/)
	{
		DWORD64 dwRead = 0;
		if (dwAddress == 0)
			return STATUS_INVALID_ADDRESS;

		// Simple read
		// Simple read
		if (!handleHoles)
		{
			return _core.native()->ReadProcessMemoryT(dwAddress, pResult, dwSize, &dwRead);
		}
		return STATUS_SUCCESS;
	}

	NTSTATUS ProcessMemory::Write(ptr_t pAddress, size_t dwSize, const void* pData)
	{
		return _core.native()->WriteProcessMemoryT(pAddress, pData, dwSize);
	}

}

