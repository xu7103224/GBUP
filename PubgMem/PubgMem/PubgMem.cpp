#include "stdafx.h"
#include <iostream>
#include <future>
#include "GameManager.h"
using namespace PUBG;
#ifdef _DEBUG
UINT WINAPI workThread()
{
	auto t = std::bind(&pubgCon::MainLoop, pubgCon::instance());
	std::thread t1(t);
	t1.detach();
	return 0;
}
#else
#endif
#ifdef _DEBUG
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2) {
		std::cout << "Invaild par!" << std::endl;
		return ERROR_INVALID_ACCEL_HANDLE;
	}
	TragetHandle = reinterpret_cast<HANDLE>(atoll(argv[1]));
	workThread();
	getchar();
	system("pasue");
	return 0;
}

#else
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	return TRUE;
}

#endif