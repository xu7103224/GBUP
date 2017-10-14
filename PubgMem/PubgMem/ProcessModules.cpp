#include "ProcessModules.h"
#include "Process.h"
namespace PUBG
{
	ProcessModules::ProcessModules(class Process& proc)
		: _proc(proc)
		, _memory(_proc.memory())
		, _core(_proc.core())
	{

	}

	ProcessModules::~ProcessModules()
	{
	}

	ModuleDataPtr ProcessModules::GetModule(
		const std::wstring& name,
		eModSeachType search /*= LdrList*/,
		eModType type /*= mt_default*/
		)
	{
		std::wstring namecopy(Utils::StripPath(name));
		return GetModule(namecopy, search, type);
	}

	ModuleDataPtr ProcessModules::GetModule(
		std::wstring& name,
		eModSeachType search /*= LdrList*/,
		eModType type /*= mt_default*/,
		const wchar_t* baseModule /*= L""*/
		)
	{
		// Detect module type
		if (type == mt_default)
			type = _proc.barrier().targetWow64 ? mt_mod32 : mt_mod64;

		CSLock lck(_modGuard);

		auto key = std::make_pair(name, type);

		// Fast lookup
		if (_modules.count(key) && (_modules[key]->manual || ValidateModule(_modules[key]->baseAddress)))
			return _modules[key];

		UpdateModuleCache(search, type);

		if (_modules.count(key))
			return _modules[key];

		return nullptr;
	}

	bool ProcessModules::ValidateModule(module_t base)
	{
		IMAGE_DOS_HEADER idh = { 0 };
		IMAGE_NT_HEADERS inth = { 0 };

		// Validate memory and headers
		if (_memory.Read(base, sizeof(idh), &idh) == STATUS_SUCCESS)
		if (idh.e_magic == IMAGE_DOS_SIGNATURE)
		if (_memory.Read(base + idh.e_lfanew, sizeof(inth), &inth) == STATUS_SUCCESS)
		if (inth.Signature == IMAGE_NT_SIGNATURE)
			return true;

		return false;
	}

	void ProcessModules::UpdateModuleCache(eModSeachType search, eModType type)
	{
		for (const auto& mod : _core.native()->EnumModules(search, type))
			_modules.emplace(std::make_pair(std::make_pair(mod->name, mod->type), mod));
	}

	
}