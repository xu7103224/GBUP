#pragma once
#include "windows.h"
#include <Uxtheme.h>
#include <d3d9.h>
#include <D3dx9core.h>


namespace PUBG
{
	class Overlay
	{
	public:
		Overlay();
		~Overlay();
		static Overlay *instance();
		BOOL SetupWindow();
		void DrawLine(float x, float y, float xx, float yy, D3DCOLOR color);
		void DrawBox(float x, float y, float width, float height, D3DCOLOR color);
		void RenderPlayersSkeleton();
		void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char * fmt, ...);
		void InitWindow();
		void initD3D(HWND hWnd);

		inline HWND hWnd() { return _hWnd; };
		inline void hWnd(HWND hwd) { _hWnd = hwd; };
		
	private:
		static DWORD WINAPI ThreadProc(LPVOID lpThreadParameter);
		static LRESULT CALLBACK WindowProc(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void Render();

		HANDLE hThd;
		HWND _hWnd;
		static Overlay *self;
		HWND twnd;
		int s_width;
		int s_height;
		IDirect3D9 *d3d;
		ID3DXLine* d3dLine;
		LPDIRECT3DDEVICE9 d3ddev;
		LPD3DXFONT pFont;
		MARGINS  margin;
	};

}