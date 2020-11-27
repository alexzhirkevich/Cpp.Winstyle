//
// Painter.h
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

#ifndef _WINSTYLE_PAINTER_
#define _WINSTYLE_PAINTER_

#ifdef _MSC_VER
#pragma once
#if _MSC_VER >= 1200
#pragma warning(push)
#endif // _MSC_VER >= 1200
#endif // _MSC_VER

#pragma warning(disable:4996)
#pragma warning(disable:4005)
#pragma warning(disable:26444)
#pragma warning(disable:26495)
#pragma warning(disable:493)

#include "Init.h"

namespace wstyle {

	class Painter
	{
	private:
		Painter(const Painter&) :Painter() {};
		Painter& operator = (const Painter&) {};
	protected:
		HWND _hWnd;
		PAINTSTRUCT paintstruct;
		int iWindowHeight, iWindowWidth;
		HDC _hMemDC;
		HBITMAP _hBitmap;
		HBITMAP _hOldBitmap;
		int _iOldBkMode, _BkMode;
	public:
		Painter() : iWindowHeight(0), iWindowWidth(0), _iOldBkMode(0), _BkMode(TRANSPARENT),
			_hMemDC(nullptr), _hBitmap(nullptr), _hOldBitmap(nullptr), _hWnd(nullptr) {};
		Painter(HWND hWnd, HBRUSH BgrBrush, bool isBuffered = true, int BkMode = TRANSPARENT) : Painter() { Open(hWnd, BgrBrush, isBuffered, BkMode); };
		HDC Open(HWND hwnd, HBRUSH BgBrush, bool isBuffered = true, int BkMode = TRANSPARENT);
		HDC GetDC() const;
		bool Close();
		~Painter();
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_PAINTER_