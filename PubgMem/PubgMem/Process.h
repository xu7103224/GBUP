#pragma once

#include "ProcessCore.h"
#include "ProcessMemory.h"
#include "CallResult.h"
#include "ProcessModules.h"
namespace PUBG
{
#define DEFAULT_ACCESS_P  PROCESS_QUERY_INFORMATION | \
	PROCESS_VM_READ | \
	PROCESS_VM_WRITE | \
	PROCESS_VM_OPERATION | \
	PROCESS_CREATE_THREAD | \
	PROCESS_SET_QUOTA | \
	PROCESS_TERMINATE | \
	PROCESS_SUSPEND_RESUME | \
	PROCESS_DUP_HANDLE

	class Process
	{
	public:
		Process();
		~Process(void);
		NTSTATUS Attach(DWORD pid, DWORD access = DEFAULT_ACCESS_P);
		NTSTATUS Attach(const wchar_t* name, DWORD access = DEFAULT_ACCESS_P);
		NTSTATUS Attach(HANDLE hProc);
		static std::vector<DWORD> EnumByName(const std::wstring& name);
		NTSTATUS Detach();
		bool valid();
		inline ProcessCore&     core()       { return _core; }    // Core routines and native 
		inline ProcessMemory&   memory()     { return _memory; }  // Memory manipulations
		inline ProcessModules&  module()     { return _modules; } // Module management
		inline const Wow64Barrier& barrier() const { return _core._native->GetWow64Barrier(); }
	private:
		Process(const Process&) = delete;
		Process& operator =(const Process&) = delete;
	private:
		ProcessCore     _core;          // Core routines and native subsystem
		ProcessModules  _modules;       // Module management
		ProcessMemory   _memory;        // Memory manipulations
	};
}