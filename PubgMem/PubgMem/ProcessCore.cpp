#include "Winheaders.h"
#include "ProcessCore.h"
namespace PUBG
{
	ProcessCore::ProcessCore()
		: _native(nullptr)
	{
	}

	ProcessCore::~ProcessCore()
	{
		Close();
	}

	NTSTATUS ProcessCore::Open(DWORD pid, DWORD access)
	{
		Close();
		_hProcess = (pid == GetCurrentProcessId()) ? GetCurrentProcess() : OpenProcess(access, false, pid);
		if (_hProcess != NULL)
		{
			_pid = pid;
			return Init();
		}
		return LastNtStatus();
	}

	NTSTATUS ProcessCore::Open(HANDLE handle)
	{
		Close();
		_hProcess = handle;
		_pid = GetProcessId(_hProcess);
		return Init();
	}

	void ProcessCore::Close()
	{
		if (_hProcess)
		{
			CloseHandle(_hProcess);
			_hProcess = NULL;
			_pid = 0;
		}
	}

	NTSTATUS ProcessCore::Init()
	{
		// Detect x86 OS
		SYSTEM_INFO info = { { 0 } };
		GetNativeSystemInfo(&info);
		bool isx86(false);
		if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		{
			_native.reset(new x86Native(_hProcess));
		}
		else
			_native.reset(new Native(_hProcess));
		return STATUS_SUCCESS;
	}
}