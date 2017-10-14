#pragma once

#include "NativeSubsystem.h"

namespace PUBG
{
	class NativeWow64 : public Native
	{
	public:
		NativeWow64(HANDLE hProcess);
		~NativeWow64();

		//virtual NTSTATUS VirtualQueryExT(ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer);
	};
}