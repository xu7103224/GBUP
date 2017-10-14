#pragma once
#include "Wow64Subsystem.h"
#include "x86Subsystem.h"
#include "Macro.h"
#include <memory>
#include <stdint.h>
namespace PUBG
{
	class ProcessCore
	{
		friend class Process;
		typedef std::unique_ptr<Native> ptrNative;

	public:
		inline HANDLE handle() const { return _hProcess; }
		inline Native* native() { return _native.get(); }
	private:
		ProcessCore();
		ProcessCore(const ProcessCore&) = delete;
		~ProcessCore();

		NTSTATUS Open(DWORD pid, DWORD access);
		NTSTATUS Open(HANDLE handle);

		NTSTATUS Init();
		//ptrNative _native; // Api wrapper
		void Close();


	private:
		HANDLE    _hProcess = NULL; // Process handle
		DWORD     _pid = 0;         // Process ID
		ptrNative _native;          // Api wrapper
	};
}