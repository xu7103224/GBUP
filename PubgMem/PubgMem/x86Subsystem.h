#pragma once

#include "NativeSubsystem.h"

namespace PUBG
{
	/// <summary>
	/// X86 OS subsystem. Used 
	/// </summary>
	class x86Native : public Native
	{
	public:
		x86Native(HANDLE hProcess);
		~x86Native();

		/// Query virtual memory
		virtual NTSTATUS VirtualQueryExT(ptr_t lpAddress, PMEMORY_BASIC_INFORMATION64 lpBuffer);

		/// Get WOW64 thread context
		virtual NTSTATUS GetThreadContextT(HANDLE hThread, _CONTEXT32& ctx);

		/// Get native thread context
		virtual NTSTATUS GetThreadContextT(HANDLE hThread, _CONTEXT64& ctx);

		/// Set WOW64 thread context
		virtual NTSTATUS SetThreadContextT(HANDLE hThread, _CONTEXT32& ctx);

		/// Set native thread context
		virtual NTSTATUS SetThreadContextT(HANDLE hThread, _CONTEXT64& ctx);

		/// Gets WOW64 PEB
		virtual ptr_t getPEB(_PEB32* ppeb);

		/// Get native PEB
		virtual ptr_t getPEB(_PEB64* ppeb);

		/// Get WOW64 TEB
		virtual ptr_t getTEB(HANDLE hThread, _TEB32* pteb);

		/// Get native TEB
		virtual ptr_t getTEB(HANDLE hThread, _TEB64* pteb);

	private:
	};
}