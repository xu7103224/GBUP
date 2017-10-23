#pragma once
#include "windows.h"
#include <Uxtheme.h>
#include <d3d9.h>
#include <D3dx9core.h>
#include <vector>
#include <mutex>
#include <unordered_map>


#define SYN_ITEM_MAX (10000)
#define ITEM_MAX			(200)	//ֻ����ǰ200��
#define SKELETON_MAX		(2000)	//ֻ����ǰ2000��
namespace PUBG
{
	struct D3DXLine {
		D3DXVECTOR2 t1;
		D3DXVECTOR2 t2;
	};


	template <typename T, size_t SIZE>
	struct SynArray {
		SynArray() :_size(0), _array(std::vector<T>(SIZE)) {
			for (int i = 0; i < SIZE - 1; ++i)
				_array[i].alive = false;
		}

		inline void set(T &item) {
			_array[_size] = item;
			_size += 1;
		};
		inline void end() { _array[_size].alive = false; };
		inline void reset() { _size = 0; };
		T& get(size_t index) { return _array[index]; }
		std::vector<T>	_array;
		size_t			_size;
	};

	struct SynData {
		SynData() { alive = false; };
		SynData(bool alive) :alive(alive) {};
		SynData(SynData &_Rt) {
			alive = _Rt.alive;
		}
		bool		alive;
	};

	struct DroppedItemInfo : public SynData
	{
		DWORD_PTR	id;
		DWORD       index;
		uint8_t     Category;
		D3DXVECTOR2 vec;

		DroppedItemInfo(int i = NULL):SynData(false),index(0),
			Category(0), vec(0.0, 0.0)
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

	struct SkeletonInfo : public SynData 
	{
		SkeletonInfo() :SynData(false), t1(0.0, 0.0), t2(0.0, 0.0) {}
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
		void RenderPlayersSkeleton();  ///������
		void RenderDrawItem();  ///����Ʒ
		void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char * fmt, ...);
		void InitWindow();
		void initD3D(HWND hWnd);
		BOOL ForwardMessage(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline HWND hWnd() { return _hWnd; };
		inline void hWnd(HWND hwd) { _hWnd = hwd; };
		

		//����
		inline SKELETONBUFFER &getSkeletons() { return skeletons; };

		//����
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

		//������ҹ�����
		SKELETONBUFFER skeletons;

		//����item
		ITEMBUFFER items;




	};

}