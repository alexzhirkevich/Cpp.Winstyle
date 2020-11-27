//
// Image.h
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

#ifndef _WINSTYLE_IMAGE_
#define _WINSTYLE_IMAGE_

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

	class Image /* Gdiplus image class */
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::Image* img;
		WCHAR* buf;
		PTCHAR path;
		void Clone(const Image& img);
	public:
		Image();
		Image(PCTCH path) :Image() { Load(path); };
		Image(const Image& img) :Image() { Clone(img); }
		Image& operator = (const Image& img);
		bool Load(PCTCH path);
		bool Paint(HDC hDC, HWND hWnd, int x, int y, int width, int height);
		bool Erase();
		virtual ~Image() { Erase(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_IMAGE_