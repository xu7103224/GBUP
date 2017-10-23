#pragma once
#include "windows.h"
#include <Uxtheme.h>
#include <d3d9.h>
#include <D3dx9core.h>
#include <vector>
#include <mutex>

namespace PUBG
{
	struct D3DXLine {
		D3DXVECTOR2 t1;
		D3DXVECTOR2 t2;
	};

	struct DroppedItemInfo
	{
		DWORD       index;
		uint8_t     Category;
		D3DXVECTOR2 vec;

		DroppedItemInfo(int i = NULL) {
			index = 0;
			Category = 0;
		}
		DroppedItemInfo(DroppedItemInfo& cop) {
			index = cop.index;
			Category = cop.Category;
			vec = cop.vec;
		}
	};


	class Overlay
	{
	public:
		~Overlay();
		static Overlay *instance();
		BOOL SetupWindow();
		void DrawLine(float x, float y, float xx, float yy, D3DCOLOR color);
		void DrawBox(float x, float y, float width, float height, D3DCOLOR color);
		void RenderPlayersSkeleton();  ///画骨骼
		void RenderDrawItem();  ///画物品
		void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char * fmt, ...);
		void InitWindow();
		void initD3D(HWND hWnd);
		BOOL ForwardMessage(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline HWND hWnd() { return _hWnd; };
		inline void hWnd(HWND hwd) { _hWnd = hwd; };
		

		//骨骼
		void updateSkeletons(std::vector<D3DXLine> &skeletons, size_t size);
		void CopySkeletons();
		//掉落
		void updateItems(std::vector<DroppedItemInfo> &items, size_t size);
		void CopyItems();

	private:
		Overlay();
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
		//所有玩家骨骼线
		std::vector<D3DXLine>		SynSkeletons;		//要同步的
		size_t						SynSkeletonsSize;	//
		std::vector<D3DXLine>		SkeletonsRender;
		size_t						SkeletonsRenderSize;	//
		std::mutex					SkeletonsLock;

		//所有item
		std::vector<DroppedItemInfo> SynItems;
		size_t						 SynItemsSize;
		std::vector<DroppedItemInfo> ItemsRander;
		size_t						 ItemsRanderSize;
		std::mutex					 ItemsLock;



	};

}