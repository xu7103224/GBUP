#include "Types.h"
#include "Winheaders.h"
#include "Utils.h"
#include <unordered_map>

namespace PUBG
{
	class DynImport
	{
	public:
		static DynImport& Instance()
		{
			static DynImport instance;
			return instance;
		}

		/// <summary>
		/// Get dll function
		/// </summary>
		/// <param name="name">Function name</param>
		/// <returns>Function pointer</returns>
		template<typename T>
		inline T get(const std::string& name)
		{
			CSLock lck(_mapGuard);

			auto iter = _funcs.find(name);
			if (iter != _funcs.end())
				return reinterpret_cast<T>(iter->second);

			return nullptr;
		}

		/// <summary>
		/// Safely call import
		/// If import not found - return STATUS_ORDINAL_NOT_FOUND
		/// </summary>
		/// <param name="name">Import name.</param>
		/// <param name="...args">Function args</param>
		/// <returns>Function result or STATUS_ORDINAL_NOT_FOUND if import not found</returns>
		template<typename T, typename... Args>
		inline NTSTATUS safeNativeCall(const std::string& name, Args&&... args)
		{
			auto pfn = DynImport::get<T>(name);
			if (pfn)
			{
				auto res = pfn(std::forward<Args>(args)...);
				return res;
			}
			else
			{
				return STATUS_ORDINAL_NOT_FOUND;
			}
			return pfn ? pfn(std::forward<Args>(args)...) : STATUS_ORDINAL_NOT_FOUND;
		}


		/// <summary>
		/// Load function into database
		/// </summary>
		/// <param name="name">Function name</param>
		/// <param name="module">Module name</param>
		/// <returns>true on success</returns>
		FARPROC load(const std::string& name, const std::wstring& module)
		{
			auto mod = GetModuleHandleW(module.c_str());
			return load(name, mod);
		}

		/// <summary>
		/// Load function into database
		/// </summary>
		/// <param name="name">Function name</param>
		/// <param name="hMod">Module base</param>
		/// <returns>true on success</returns>
		FARPROC load(const std::string& name, HMODULE hMod)
		{
			CSLock lck(_mapGuard);

			auto proc = GetProcAddress(hMod, name.c_str());
			if (proc)
			{
				_funcs.insert(std::make_pair(name, proc));
				return proc;
			}

			return nullptr;
		}

	private:
		DynImport() = default;
		DynImport(const DynImport&) = delete;

	private:
		std::unordered_map<std::string, FARPROC> _funcs;    // function database
		CriticalSection _mapGuard;                          // function database guard
	};
#define LOAD_IMPORT(name, module) (DynImport::Instance().load( name, module ))
#define SAFE_NATIVE_CALL(name, ...) (DynImport::Instance().safeNativeCall<fn ## name>( #name, __VA_ARGS__ ))
}

