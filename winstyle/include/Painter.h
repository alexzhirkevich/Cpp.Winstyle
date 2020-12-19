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
#endif // _MSC_VER

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
		Painter();
		Painter(HWND hWnd, HBRUSH BgrBrush, bool isBuffered = true, int BkMode = TRANSPARENT);
		HDC Open(HWND hwnd, HBRUSH BgBrush, bool isBuffered = true, int BkMode = TRANSPARENT);
		HDC GetDC() const;
		bool Close();
		~Painter();
	};

}

#endif // _WINSTYLE_PAINTER_