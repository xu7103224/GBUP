#include "Overlay.h"
#include "GameManager.h"
#include <tchar.h>
#include <string>
#include <cstdarg>
#include <iostream>
#include <Dwmapi.h>
#include "PUBG_Engine_classes.h"
#include "PUBG_Engine_structs.h"


namespace PUBG
{
	Overlay * Overlay::self = Overlay::instance();

	Overlay::Overlay() :_hWnd(NULL),
		twnd(NULL),
		s_width(0),
		s_height(0),
		d3d(NULL),
		d3dLine(NULL),
		d3ddev(NULL),
		pFont(NULL),
		margin({ 0,0,s_width,s_height }),
		hThd(NULL)
	{
	}



	Overlay::~Overlay()
	{
		if (hThd)
			CloseHandle(hThd);
		SAFE_DELETE(self);
	}

	Overlay * Overlay::instance()
	{
		static Overlay *_this = new Overlay();
		return _this;
	}

	BOOL Overlay::SetupWindow()
	{
		DWORD thdId;
		hThd = CreateThread(NULL, 0, ThreadProc, 0, 0, &thdId);
		if (INVALID_HANDLE_VALUE == hThd)
			return false;


		return true;
	}

	//ESP stuff
	void Overlay::initD3D(HWND hWnd)
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

		D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

		ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
		d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
		d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
		d3dpp.BackBufferWidth = s_width;    // set the width of the buffer
		d3dpp.BackBufferHeight = s_height;    // set the height of the buffer

		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		// create a device class using this information and the info from the d3dpp stuct
		d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

		D3DXCreateFontA(d3ddev, 13, 0, FW_HEAVY, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		D3DXCreateLine(d3ddev, &d3dLine);
	}

	void Overlay::DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char *fmt, ...)
	{
		char buf[1024] = { 0 };
		va_list va_alist;
		RECT FontPos = { x, y, x + 120, y + 16 };
		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		g_pFont->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
	}

	void Overlay::DrawLine(float x, float y, float xx, float yy, D3DCOLOR color)
	{
		D3DXVECTOR2 dLine[2];

		d3dLine->SetWidth(1.f);

		dLine[0].x = x;
		dLine[0].y = y;

		dLine[1].x = xx;
		dLine[1].y = yy;

		d3dLine->Draw(dLine, 2, color);

	}

	void Overlay::DrawBox(float x, float y, float width, float height, D3DCOLOR color)
	{
		D3DXVECTOR2 points[5];
		points[0] = D3DXVECTOR2(x, y);
		points[1] = D3DXVECTOR2(x + width, y);
		points[2] = D3DXVECTOR2(x + width, y + height);
		points[3] = D3DXVECTOR2(x, y + height);
		points[4] = D3DXVECTOR2(x, y);
		d3dLine->SetWidth(1);
		d3dLine->Draw(points, 5, color);
	}

	void Overlay::RenderPlayersSkeleton() {
		std::vector<D3DXLine> skeletons;
		CopySkeletons(skeletons);
		for (auto line : skeletons) {
			DrawLine(line.t1.x, line.t1.y, line.t2.x, line.t2.y, D3DCOLOR_ARGB(255, 153, 249, 9));
		}
	}

	void Overlay::Render()
	{
		// clear the window alpha
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

								 //calculate and and draw esp stuff
		//ESP
		RenderPlayersSkeleton();	//»­¹Ç÷À

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
	}

	void Overlay::updateSkeletons(std::vector<D3DXLine>& skeletons)
	{
		std::lock_guard<std::mutex> l(SkeletonsLock);
		Skeletons.clear();
		for (auto it : skeletons)
			Skeletons.push_back(it);
	}

	void Overlay::CopySkeletons(std::vector<D3DXLine>& skeletons)
	{
		std::lock_guard<std::mutex> l(SkeletonsLock);
		for (auto it : Skeletons) 
			skeletons.push_back(it);
	}

	DWORD Overlay::ThreadProc(LPVOID lpThreadParameter)
	{
		//MessageBox(0, _T("111"), 0, 0);
		Overlay *_this = Overlay::instance();
		_this->InitWindow();
		MSG msg;
		RECT rc;
		while (TRUE)
		{
			ZeroMemory(&msg, sizeof(MSG));
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
				exit(0);
			_this->twnd = NULL;
			_this->twnd = FindWindow(_T("UnrealWindow"), 0);
			if (!_this->twnd)
			{
				std::cout << "shutting" << std::endl;
				//Shutdown();
				ExitProcess(0);
			}
			ZeroMemory(&rc, sizeof(RECT));
			GetWindowRect(_this->twnd, &rc);
			_this->s_width = rc.right - rc.left;
			_this->s_height = rc.bottom - rc.top;

			//SetWindowPos(_this->_hWnd, HWND_TOPMOST, rc.left, rc.top, _this->s_width, _this->s_height, SWP_NOMOVE);
			MoveWindow(_this->_hWnd, rc.left, rc.top, _this->s_width, _this->s_height, true);
			//SetParent(_this->_hWnd, _this->twnd);

			//render your esp
			_this->Render();

			Sleep(5);
		}
		return msg.wParam;
	}

	LRESULT CALLBACK Overlay::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
//#ifdef _DEBUG
//		char szbuff[MAX_PATH];
//		sprintf_s(szbuff, "msg: %x\n hWnd = %x", message, hWnd);
//		OutputDebugStringA(szbuff);
//#endif
		switch (message)
		{
		case WM_PAINT:
			//std::cout << "WM_PAINT" << std::endl;
			Overlay::instance()->Render();
			break;

		case WM_CREATE:
			DwmExtendFrameIntoClientArea(hWnd, &Overlay::instance()->margin);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		
		return DefWindowProc(hWnd, message, wParam, lParam);
	}


	void Overlay::InitWindow()
	{


		RECT rc;


		while (!twnd)
			twnd = FindWindow(_T("UnrealWindow"), 0);
		if (twnd != NULL)
		{
			GetWindowRect(twnd, &rc);
			s_width = rc.right - rc.left;
			s_height = rc.bottom - rc.top;

			margin = { 0,0,s_width,s_height };
		}
		else
		{
			//cout << "Closing..." << GetLastError() << endl;
			//Sleep(3000);
			//Shutdown();
			//ExitProcess(0);
		}
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(0);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
		wc.lpszClassName = _T("AAAAA");
		RegisterClassEx(&wc);

		_hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, wc.lpszClassName, _T(""), WS_POPUP, rc.left, rc.top, s_width, s_height, NULL, NULL, wc.hInstance, NULL);

		SetLayeredWindowAttributes(_hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
		SetLayeredWindowAttributes(_hWnd, 0, 255, LWA_ALPHA);

		ShowWindow(_hWnd, SW_SHOW);
		initD3D(_hWnd);
	}

}