#include "x86Subsystem.h"
#include "DynImport.h"
#include "Macro.h"


namespace PUBG
{
	x86Native::x86Native(HANDLE hProcess)
		: Native(hProcess, true)
	{
	}

	x86Native::~x86Native()
	{
	}


	/// Query virtual memory
	NTSTATUS x86Native::VirtualQueryExT(ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer)
	{
		MEMORY_BASIC_INFORMATION tmp = { 0 };

		NTSTATUS status = SAFE_NATIVE_CALL(
			NtQueryVirtualMemory,
			_hProcess, reinterpret_cast<PVOID>(lpAddress),
			MemoryBasicInformation, &tmp, sizeof(tmp), nullptr
			);
		if (status != STATUS_SUCCESS)
			return status;

		// Map values
		lpBuffer->AllocationBase = reinterpret_cast<ULONGLONG>(tmp.AllocationBase);
		lpBuffer->AllocationProtect = tmp.AllocationProtect;
		lpBuffer->BaseAddress = reinterpret_cast<ULONGLONG>(tmp.BaseAddress);
		lpBuffer->Protect = tmp.Protect;
		lpBuffer->RegionSize = tmp.RegionSize;
		lpBuffer->State = tmp.State;
		lpBuffer->Type = tmp.Type;

		return status;
	}

	/// Get WOW64 thread context
	NTSTATUS x86Native::GetThreadContextT(HANDLE hThread, _CONTEXT32& ctx)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		GetThreadContext(hThread, reinterpret_cast<PCONTEXT>(&ctx));
		return LastNtStatus();
	}

	/// Get native thread context
	NTSTATUS x86Native::GetThreadContextT(HANDLE /*hThread*/, _CONTEXT64& /*ctx*/)
	{
		// There is no x64 context under x86 OS
		return STATUS_NOT_SUPPORTED;
	}

	/// Set WOW64 thread context
	NTSTATUS x86Native::SetThreadContextT(HANDLE hThread, _CONTEXT32& ctx)
	{
		SetLastNtStatus(STATUS_SUCCESS);
		SetThreadContext(hThread, reinterpret_cast<const CONTEXT*>(&ctx));
		return LastNtStatus();
	}

	/// Set native thread context
	NTSTATUS x86Native::SetThreadContextT(HANDLE /*hThread*/, _CONTEXT64& /*ctx*/)
	{
		// There is no x64 context under x86 OS
		return STATUS_NOT_SUPPORTED;
	}

	/// Gets WOW64 PEB
	ptr_t x86Native::getPEB(_PEB32* ppeb)
	{
		PROCESS_BASIC_INFORMATION pbi = { 0 };
		ULONG bytes = 0;

		if (NT_SUCCESS(SAFE_NATIVE_CALL(NtQueryInformationProcess, _hProcess, ProcessBasicInformation, &pbi, (ULONG)sizeof(pbi), &bytes)) && ppeb)
			ReadProcessMemory(_hProcess, pbi.PebBaseAddress, ppeb, sizeof(_PEB32), NULL);

		return reinterpret_cast<ptr_t>(pbi.PebBaseAddress);
	}

	/// Get native PEB
	ptr_t x86Native::getPEB(_PEB64* /*ppeb*/)
	{
		// There is no x64 PEB under x86 OS
		SetLastNtStatus(STATUS_NOT_SUPPORTED);
		return 0;
	}

	/// Get WOW64 TEB
	ptr_t x86Native::getTEB(HANDLE hThread, _TEB32* pteb)
	{
		_THREAD_BASIC_INFORMATION_T<DWORD> tbi = { 0 };
		ULONG bytes = 0;

		if (NT_SUCCESS(SAFE_NATIVE_CALL(NtQueryInformationThread, hThread, (THREADINFOCLASS)0, &tbi, (ULONG)sizeof(tbi), &bytes)) && pteb)
			ReadProcessMemory(_hProcess, (LPCVOID)((uintptr_t)tbi.TebBaseAddress), pteb, sizeof(_TEB32), NULL);

		return tbi.TebBaseAddress;
	}

	/// Get native TEB
	ptr_t x86Native::getTEB(HANDLE /*hThread*/, _TEB64* /*pteb*/)
	{
		// There is no x64 TEB under x86 OS
		SetLastNtStatus(STATUS_NOT_SUPPORTED);
		return 0;
	}
}