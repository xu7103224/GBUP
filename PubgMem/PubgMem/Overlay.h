#pragma once
#include "windows.h"
#include <Uxtheme.h>
#include <d3d9.h>
#include <D3dx9core.h>
#include <vector>
#include <mutex>
#include <unordered_map>


#define ITEM_MAX			200	//ֻ����ǰ200��
namespace PUBG
{
	struct D3DXLine {
		D3DXVECTOR2 t1;
		D3DXVECTOR2 t2;
	};

	template<typename T>
	struct UPDATE_ITEM {
		T data;
		BOOL update;
	};

	struct DroppedItemInfo
	{
		DWORD_PTR	id;
		DWORD       index;
		uint8_t     Category;
		D3DXVECTOR2 vec;
		BOOL		alive;

		DroppedItemInfo(int i = NULL):index(0),
			Category(0), vec(0.0, 0.0), alive(false)
		{
		}
		DroppedItemInfo(DroppedItemInfo& cop) {
			id = cop.id;
			index = cop.index;
			Category = cop.Category;
			vec = cop.vec;
			alive = cop.alive;
		}

	};

typedef std::vector<DroppedItemInfo>					VITEM;
typedef UPDATE_ITEM<int>								REFTAB_ITEM;
typedef std::unordered_map<DWORD_PTR, REFTAB_ITEM>		REFTAB;
	class Overlay
	{
	public:
		~Overlay();
		static Overlay *instance();
		BOOL SetupWindow();
		void DrawLine(float x, float y, float xx, float yy, D3DCOLOR color);
		void DrawBox(float x, float y, float width, float height, D3DCOLOR color);
		void RenderPlayersSkeleton();  ///������
		void RenderDrawItem();  ///����Ʒ
		void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char * fmt, ...);
		void InitWindow();
		void initD3D(HWND hWnd);
		BOOL ForwardMessage(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline HWND hWnd() { return _hWnd; };
		inline void hWnd(HWND hwd) { _hWnd = hwd; };
		

		//����
		void updateSkeletons(std::vector<D3DXLine> &skeletons, size_t size);
		void CopySkeletons();
		//����
		void updateItems(VITEM &items, int size);
		int FindItemIndexTable(DWORD_PTR id);
		void ItemIndexTableDel(DWORD_PTR id);
		void ItemIndexTableAdd(DWORD_PTR id, REFTAB_ITEM &item);
		void ItemIndexTableReset();
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
		//������ҹ�����
		std::vector<D3DXLine>		SynSkeletons;		//Ҫͬ����
		size_t						SynSkeletonsSize;	//
		std::vector<D3DXLine>		SkeletonsRender;
		size_t						SkeletonsRenderSize;	//
		std::mutex					SkeletonsLock;

		//����item
		VITEM						SynItems;
		REFTAB						ItemIndexTable;



	};

}