#include "Utils.h"
#include <algorithm>
namespace PUBG
{
	std::wstring Utils::StripPath(const std::wstring& path)
	{
		if (path.empty())
			return path;

		auto idx = path.rfind(L'\\');
		if (idx == path.npos)
			idx = path.rfind(L'/');

		if (idx != path.npos)
			return path.substr(idx + 1);
		else
			return path;
	}

	std::wstring Utils::ToLower(const std::wstring& str)
	{
		std::wstring str2(str);
		std::transform(str2.begin(), str2.end(), str2.begin(), ::towlower);

		return str2;
	}
}