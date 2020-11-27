//
// Bitmap.h
//
//      Copyright (c) Alexandr Zhirkevich. All rights reserved.
//		E-mail: mailto:sasha.zhirkevich@yandex.ru;
//		Vk: https://vk.com/id175640630;
//		Telegram: @alexzhirkevich.
//
// The C++ WinApi <winstyle.h> library.
//
// namespace wstyle
//

#ifndef _WINSTYLE_BITMAP_
#define _WINSTYLE_BITMAP_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"

namespace wstyle {

	class Bitmap /* Bitmap image class for WINAPI*/
	{
	protected:
		HWND hWnd;
		HINSTANCE hInstance;
		HBITMAP hbitmap;
		HDC hdc;
		BITMAP bitmap;
		_tstring path;
		int id;
		void Clone(const Bitmap& bmp);
	public:
		Bitmap();
		Bitmap(HWND hwnd, PCTCH path) :Bitmap() { Load(hwnd, path); }
		Bitmap(HINSTANCE hInst, HWND hwnd, int IDB_BITMAP) :Bitmap() { Load(hwnd, hInst, IDB_BITMAP); }
		Bitmap(const Bitmap& p) :Bitmap() { Clone(p); }
		Bitmap& operator =(const Bitmap& p);
		int Width() const { return bitmap.bmWidth; }
		int Height() const { return bitmap.bmHeight; }
		_tstring Path() const { return this->path; }
		bool Paint(HDC hDC, int x, int y) const;
		bool Load(HWND hwnd, PCTCH path);
		bool Load(HWND hwnd, HINSTANCE hInst, int IDB_BITMAP);
		bool Erase();
		virtual ~Bitmap() { Erase(); };
	};

}

#endif // _WINSTYLE_BITMAP_