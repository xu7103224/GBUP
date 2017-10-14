#include "Process.h"

#include <memory>

namespace PUBG
{
	Process::Process()
		: _core()
		, _memory(this)
		, _modules(*this)
	{
	}

	Process::~Process()
	{
	}

	NTSTATUS Process::Attach(DWORD pid, DWORD access /*= DEFAULT_ACCESS_P*/)
	{
		Detach();
		auto status = _core.Open(pid, access);
		return status;
	}

	NTSTATUS Process::Attach(HANDLE hProc)
	{
		Detach();

		auto status = _core.Open(hProc);
		if (NT_SUCCESS(status))
		{
			if (!valid())
				return STATUS_INVALID_HANDLE;
		}

		return status;
	}
	DWORD getGameElapsed(DWORD dwPID)
	{
		union
		{
			FILETIME ft;
			__int64 i64;
		} timeCreate, timeNow;

		FILETIME ftCreate;
		FILETIME ftUnuse1;
		FILETIME ftUnuse2;
		FILETIME ftUnuse3;
		HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, dwPID);
		if (hProcess != NULL)
		{
			if (GetProcessTimes(hProcess, &ftCreate, &ftUnuse1, &ftUnuse2, &ftUnuse3))
			{

				SYSTEMTIME sysTm;
				GetSystemTime(&sysTm);
				FILETIME ftNow;
				SystemTimeToFileTime(&sysTm, &ftNow);

				timeCreate.ft = ftCreate;
				timeNow.ft = ftNow;

				::CloseHandle(hProcess);
				return (DWORD)((timeNow.i64 - timeCreate.i64) / 10000000U);
			}
			else
				::CloseHandle(hProcess);
		}

		return -1;
	}

	NTSTATUS Process::Attach(const wchar_t* name, DWORD access /*= DEFAULT_ACCESS_P*/)
	{
		/*auto pids = EnumByName(name);
		return pids.empty() ? STATUS_NOT_FOUND : Attach(pids.front(), access);*/
		auto pids = EnumByName(name);
		if (pids.empty())
		{
			return STATUS_NOT_FOUND;
		}
		else
		{
			if (getGameElapsed(pids.front()) < 15)
				Sleep(10 * 1000);
			return Attach(pids.front(), access);
		}
	}


	std::vector<DWORD> Process::EnumByName(const std::wstring& name)
	{
		std::vector<DWORD> found;
		HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hProcSnap != INVALID_HANDLE_VALUE)
		{
			PROCESSENTRY32W tEntry = { 0 };
			tEntry.dwSize = sizeof(PROCESSENTRY32W);

			// Iterate threads
			for (BOOL success = Process32FirstW(hProcSnap, &tEntry);
				success == TRUE;
				success = Process32NextW(hProcSnap, &tEntry))
			{
				if (name.empty() || _wcsicmp(tEntry.szExeFile, name.c_str()) == 0)
					found.emplace_back(tEntry.th32ProcessID);
			}

			CloseHandle(hProcSnap);
		}

		return found;
	}

	NTSTATUS Process::Detach()
	{
		_core.Close();
		//_memory.reset();
		//_modules.reset();
		return STATUS_SUCCESS;
	}
	bool Process::valid()
	{
		DWORD dwExitCode = 0;

		if (!_core.handle() || !GetExitCodeProcess(_core.handle(), &dwExitCode))
			return false;

		return (dwExitCode == STILL_ACTIVE);
	}
}