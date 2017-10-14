#pragma once

#include "Winheaders.h"
#include "CallResult.h"
#include "Types.h"
#include "Utils.h"

#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>

namespace std
{
	template <>
	struct hash < struct pair<wstring, PUBG::eModType> >
	{
		size_t operator()(const pair<wstring, PUBG::eModType>& value) const
		{
			hash<wstring> sh;
			return sh(value.first) ^ value.second;
		}
	};
}

namespace PUBG
{

	class ProcessModules
	{
	public:
		typedef std::unordered_map<std::pair<std::wstring, eModType>, ModuleDataPtr> mapModules;
	public:
		ProcessModules(class Process& proc);
		~ProcessModules();

		void LoadFuncs();
		bool ValidateModule(module_t base);
		ModuleDataPtr GetModule(
			                    const std::wstring& name,
			                    eModSeachType search = LdrList,
			                    eModType type = mt_default
			                   );

		ModuleDataPtr GetModule(
			                    std::wstring& name,
			                    eModSeachType search = LdrList,
			                    eModType type = mt_default,
			                    const wchar_t* baseModule = L""
			                    );
	private:
		ProcessModules(const ProcessModules&) = delete;
		ProcessModules operator =(const ProcessModules&) = delete;

		void UpdateModuleCache(eModSeachType search, eModType type);

	private:
		class Process&       _proc;
		class ProcessMemory& _memory;
		class ProcessCore&   _core;

		mapModules _modules;            // Fast lookup cache
		CriticalSection _modGuard;      // Module guard        
	};
}