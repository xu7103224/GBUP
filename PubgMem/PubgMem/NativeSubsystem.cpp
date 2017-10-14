#include "NativeSubsystem.h"
#include "Utils.h"
#include "DynImport.h"
#include "Macro.h"
#include <iostream>
namespace PUBG
{
	Native::~Native()
	{
		
	}

	Native::Native(HANDLE hProcess, bool x86OS /*= false*/)
		: _hProcess(hProcess)
	{
		LoadFuncs();
		SYSTEM_INFO info = { { 0 } };
		GetNativeSystemInfo(&info);
		_pageSize = info.dwPageSize;

		// x86 OS, emulate WOW64 processes
		if (x86OS)
		{
			_wowBarrier.sourceWow64 = true;
			_wowBarrier.targetWow64 = true;
			_wowBarrier.type = wow_32_32;
			_wowBarrier.x86OS = true;
		}
		else
		{
			BOOL wowSrc = FALSE, wowTgt = FALSE;
			IsWow64Process(GetCurrentProcess(), &wowSrc);
			IsWow64Process(_hProcess, &wowTgt);

			_wowBarrier.sourceWow64 = (wowSrc == TRUE);
			_wowBarrier.targetWow64 = (wowTgt == TRUE);
			if (wowSrc == TRUE && wowTgt == TRUE)
				_wowBarrier.type = wow_32_32;
			else if (wowSrc == FALSE && wowTgt == FALSE)
				_wowBarrier.type = wow_64_64;
			else if (wowSrc == TRUE)
			{
				_wowBarrier.type = wow_32_64;
				_wowBarrier.mismatch = true;
			}
			else
			{
				_wowBarrier.type = wow_64_32;
				_wowBarrier.mismatch = true;
			}
		}
	}

	void LoadFuncs()
	{
		HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
		HMODULE hKernel32 = GetModuleHandleW(L"kernel32.dll");

		LOAD_IMPORT("NtQuerySystemInformation", hNtdll);
		LOAD_IMPORT("RtlDosApplyFileIsolationRedirection_Ustr", hNtdll);
		LOAD_IMPORT("RtlInitUnicodeString", hNtdll);
		LOAD_IMPORT("RtlFreeUnicodeString", hNtdll);
		LOAD_IMPORT("RtlHashUnicodeString", hNtdll);
		LOAD_IMPORT("RtlUpcaseUnicodeChar", hNtdll);
		LOAD_IMPORT("NtQueryInformationProcess", hNtdll);
		LOAD_IMPORT("NtSetInformationProcess", hNtdll);
		LOAD_IMPORT("NtQueryInformationThread", hNtdll);
		LOAD_IMPORT("NtDuplicateObject", hNtdll);
		LOAD_IMPORT("NtQueryObject", hNtdll);
		LOAD_IMPORT("NtQuerySection", hNtdll);
		LOAD_IMPORT("RtlCreateActivationContext", hNtdll);
		LOAD_IMPORT("NtQueryVirtualMemory", hNtdll);
		LOAD_IMPORT("NtCreateThreadEx", hNtdll);
		LOAD_IMPORT("NtLockVirtualMemory", hNtdll);
		LOAD_IMPORT("NtSuspendProcess", hNtdll);
		LOAD_IMPORT("NtResumeProcess", hNtdll);
		LOAD_IMPORT("RtlImageNtHeader", hNtdll);
		LOAD_IMPORT("NtLoadDriver", hNtdll);
		LOAD_IMPORT("NtUnloadDriver", hNtdll);
		LOAD_IMPORT("RtlDosPathNameToNtPathName_U", hNtdll);
		LOAD_IMPORT("NtOpenEvent", hNtdll);
		LOAD_IMPORT("NtCreateEvent", hNtdll);
		LOAD_IMPORT("NtQueueApcThread", hNtdll);
		LOAD_IMPORT("RtlEncodeSystemPointer", hNtdll);
		LOAD_IMPORT("RtlQueueApcWow64Thread", hNtdll);
		LOAD_IMPORT("NtWow64QueryInformationProcess64", hNtdll);
		LOAD_IMPORT("NtWow64ReadVirtualMemory64", hNtdll);
		LOAD_IMPORT("NtWow64WriteVirtualMemory64", hNtdll);
		LOAD_IMPORT("Wow64GetThreadContext", hKernel32);
		LOAD_IMPORT("Wow64SetThreadContext", hKernel32);
		LOAD_IMPORT("Wow64SuspendThread", hKernel32);
		LOAD_IMPORT("GetProcessDEPPolicy", hKernel32);
		LOAD_IMPORT("QueryFullProcessImageNameW", hKernel32);
	}

	NTSTATUS Native::VirtualQueryExT(ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		VirtualQueryEx(
			_hProcess, reinterpret_cast<LPCVOID>(lpAddress),
			reinterpret_cast<PMEMORY_BASIC_INFORMATION>(lpBuffer),
			sizeof(MEMORY_BASIC_INFORMATION)
			);

		return LastNtStatus();
	}

	NTSTATUS Native::VirtualFreeExT(ptr_t lpAddress, size_t dwSize, DWORD dwFreeType)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		VirtualFreeEx(_hProcess, reinterpret_cast<LPVOID>(lpAddress), dwSize, dwFreeType);
		return LastNtStatus();
	}

	NTSTATUS Native::ReadProcessMemoryT(ptr_t lpBaseAddress, LPVOID lpBuffer, size_t nSize, DWORD64 *lpBytes /*= nullptr */)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		ReadProcessMemory(_hProcess, reinterpret_cast<LPVOID>(lpBaseAddress), lpBuffer, nSize, reinterpret_cast<SIZE_T*>(lpBytes));
		return LastNtStatus();
	}

	NTSTATUS Native::WriteProcessMemoryT(ptr_t lpBaseAddress, LPCVOID lpBuffer, size_t nSize, DWORD64 *lpBytes /*= nullptr */)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		WriteProcessMemory(_hProcess, reinterpret_cast<LPVOID>(lpBaseAddress), lpBuffer, nSize, reinterpret_cast<SIZE_T*>(lpBytes));
		return LastNtStatus();
	}

	std::vector<ModuleDataPtr> Native::EnumModules(eModSeachType search/*= LdrList*/, eModType mtype /*= mt_default */)
	{
		if (search == LdrList)
		{
			// Detect module type
			if (mtype == mt_default)
				mtype = _wowBarrier.targetWow64 ? mt_mod32 : mt_mod64;
			return CALL_64_86(mtype == mt_mod64, EnumModulesT);
		}

		return std::vector<ModuleDataPtr>();
	}


	template<typename T>
	std::vector<ModuleDataPtr> Native::EnumModulesT()
	{
		_PEB_T<T> peb = { 0 };
		_PEB_LDR_DATA2_T<T> ldr = { 0 };
		std::vector<ModuleDataPtr> result;
		if (getPEB(&peb) != 0 && ReadProcessMemoryT(peb.Ldr, &ldr, sizeof(ldr), 0) == STATUS_SUCCESS)
		{
			for (T head = ldr.InLoadOrderModuleList.Flink;
				head != (peb.Ldr + FIELD_OFFSET(_PEB_LDR_DATA2_T<T>, InLoadOrderModuleList));
				ReadProcessMemoryT(static_cast<ptr_t>(head), &head, sizeof(head)))
			{
				ModuleData data;
				wchar_t localPath[512] = { 0 };
				_LDR_DATA_TABLE_ENTRY_BASE_T<T> localdata = { { 0 } };

				ReadProcessMemoryT(head, &localdata, sizeof(localdata), 0);
				ReadProcessMemoryT(localdata.FullDllName.Buffer, localPath, localdata.FullDllName.Length);

				data.baseAddress = localdata.DllBase;
				data.size = localdata.SizeOfImage;
				data.fullPath = Utils::ToLower(localPath);
				data.name = Utils::StripPath(data.fullPath);
				data.type = (sizeof(T) < sizeof(uint64_t)) ? mt_mod32 : mt_mod64;
				data.manual = false;

				result.emplace_back(std::make_shared<const ModuleData>(data));
			}
		}

		return result;
	}
	
	ptr_t Native::getPEB(_PEB32* ppeb)
	{
		// Target process is x64. PEB32 is not available.
		if (_wowBarrier.targetWow64 == false)
		{
			return 0;
		}
		else
		{
			PROCESS_BASIC_INFORMATION pbi = { 0 };
			ULONG bytes = 0;

			if (NT_SUCCESS(SAFE_NATIVE_CALL(NtQueryInformationProcess, _hProcess, ProcessBasicInformation, &pbi, (ULONG)sizeof(pbi), &bytes)) && ppeb)
				ReadProcessMemory(_hProcess, pbi.PebBaseAddress, ppeb, sizeof(_PEB32), NULL);

			return reinterpret_cast<ptr_t>(pbi.PebBaseAddress);
		}
	}

	ptr_t Native::getPEB(_PEB64* ppeb)
	{
		PROCESS_BASIC_INFORMATION64 pbi = { 0 };
		ULONG bytes = 0;

		if (NT_SUCCESS(SAFE_NATIVE_CALL(NtQueryInformationProcess, _hProcess, ProcessBasicInformation, &pbi, (ULONG)sizeof(pbi), &bytes)) && ppeb)
			ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(pbi.PebBaseAddress), ppeb, sizeof(_PEB64), NULL);

		return pbi.PebBaseAddress;
	}
}