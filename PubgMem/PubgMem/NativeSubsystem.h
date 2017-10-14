#pragma once

#include "Winheaders.h"
#include "Types.h"
#include "Macro.h"

#include <string>
#include <list>
#include <vector>
#include <unordered_set>
#include <cassert>

namespace PUBG
{
	typedef struct _PROCESS_BASIC_INFORMATION64 {
		NTSTATUS ExitStatus;
		UINT32 Reserved0;
		UINT64 PebBaseAddress;
		UINT64 AffinityMask;
		UINT32 BasePriority;
		UINT32 Reserved1;
		UINT64 UniqueProcessId;
		UINT64 InheritedFromUniqueProcessId;
	} PROCESS_BASIC_INFORMATION64;

	static void LoadFuncs();

	class Native
	{
	public:
		Native(HANDLE hProcess, bool x86OS = false);
		~Native();

		
		/// Get lowest possible valid address value
		inline ptr_t minAddr() const { return 0x10000; }

		/// Get highest possible valid address value
		inline ptr_t maxAddr() const { return 0x7FFFFFFEFFFF; }

		inline const Wow64Barrier& GetWow64Barrier() const { return _wowBarrier; }

		virtual NTSTATUS VirtualQueryExT(ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer);
		virtual NTSTATUS VirtualFreeExT(ptr_t lpAddress, size_t dwSize, DWORD dwFreeType);
		virtual NTSTATUS ReadProcessMemoryT(ptr_t lpBaseAddress, LPVOID lpBuffer, size_t nSize, DWORD64 *lpBytes = nullptr);
		virtual NTSTATUS WriteProcessMemoryT(ptr_t lpBaseAddress, LPCVOID lpBuffer, size_t nSize, DWORD64 *lpBytes = nullptr);
		template<typename T>
		std::vector<ModuleDataPtr> EnumModulesT();

		std::vector<ModuleDataPtr> EnumModules(eModSeachType search = LdrList, eModType mtype = mt_default);

		virtual ptr_t getPEB(_PEB32* ppeb);
		virtual ptr_t getPEB(_PEB64* ppeb);
	protected:
		HANDLE _hProcess;   // Process handle
		Wow64Barrier _wowBarrier;   // WOW64 barrier info
		uint32_t _pageSize;
	};
}