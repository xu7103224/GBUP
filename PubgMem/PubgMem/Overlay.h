#pragma once
#include "windows.h"
#include <Uxtheme.h>
#include <d3d9.h>
#include <D3dx9core.h>
#include <vector>
#include <mutex>
#include <unordered_map>


#define SYN_ITEM_MAX (10000)
#define ITEM_MAX			(200)	//只迭代前200个
#define SKELETON_MAX		(2000)	//只迭代前2000个
namespace PUBG
{
	struct D3DXLine {
		D3DXVECTOR2 t1;
		D3DXVECTOR2 t2;
	};


	template <typename T, size_t SIZE>
	struct SynArray {
		SynArray() :_size(0), _end(0), _array(std::vector<T>(SIZE)) {
		}

		inline void set(T &item) {
			_array[_size] = item;
			_size += 1;
		};
		inline void end(size_t size) { _end = size; };
		inline size_t end() { return _end; }
		inline void size(size_t size) { _size = size; };
		inline size_t size() { return _size; };
		inline T& get(size_t index) { return _array[index]; }
		std::vector<T>	_array;
		size_t			_size;
		size_t			_end;
	};

	//struct SynData {
	//	SynData() { alive = false; };
	//	SynData(bool alive) :alive(alive) {};
	//	SynData(SynData &_Rt) {
	//		alive = _Rt.alive;
	//	}
	//	bool		alive;
	//};

	struct DroppedItemInfo
	{
		DWORD_PTR	id;
		DWORD       index;
		uint8_t     Category;
		D3DXVECTOR2 vec;

		DroppedItemInfo(int i = NULL):index(0),
			Category(0), vec(0.0, 0.0)
		{
		}
		DroppedItemInfo(DroppedItemInfo& cop) {
			id = cop.id;
			index = cop.index;
			Category = cop.Category;
			vec = cop.vec;
		}
	};

	struct SkeletonInfo
	{
		SkeletonInfo() :t1(0.0, 0.0), t2(0.0, 0.0) {}
		SkeletonInfo(SkeletonInfo & _Rt) {
			memcpy(this, &_Rt, sizeof(SkeletonInfo));
		}

		D3DXVECTOR2 t1;
		D3DXVECTOR2 t2;
	};

typedef SynArray<DroppedItemInfo, SYN_ITEM_MAX>					ITEMBUFFER;
typedef SynArray<SkeletonInfo,	SYN_ITEM_MAX>					SKELETONBUFFER;
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
		inline SKELETONBUFFER &getSkeletons() { return skeletons; };

		//掉落
		inline ITEMBUFFER &getItems() { return items; };

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
		SKELETONBUFFER skeletons;

		//所有item
		ITEMBUFFER items;




	};

}