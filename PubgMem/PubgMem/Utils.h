#pragma once

#include "Winheaders.h"
#include <string>
#include <vector>
#include <tuple>

namespace PUBG
{
	class Utils
	{
	public:
		static std::wstring StripPath(const std::wstring& path);
		static std::wstring ToLower(const std::wstring& str);
	};

	class CriticalSection
	{
	public:
		CriticalSection()
		{
			InitializeCriticalSection(&_native);
		}

		 ~CriticalSection()
		{
			DeleteCriticalSection(&_native);
		}

		void lock()
		{
			EnterCriticalSection(&_native);
		}

		void unlock()
		{
			LeaveCriticalSection(&_native);
		}

	private:
		CRITICAL_SECTION _native;
	};


	/// <summary>
	/// std::lock_guard alternative
	/// </summary>
	class CSLock
	{
	public:
		CSLock(CriticalSection& cs)
			: _cs(cs)
		{
			cs.lock();
		}

		 ~CSLock()
		{
			_cs.unlock();
		}

	private:
		CSLock(const CSLock&) = delete;
		CSLock& operator = (const CSLock&) = delete;

	private:
		CriticalSection& _cs;
	};
}