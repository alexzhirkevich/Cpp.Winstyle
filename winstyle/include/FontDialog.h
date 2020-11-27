//
// FontDialog.h
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

#ifndef _WINSTYLE_FONTDIALOG_
#define _WINSTYLE_FONTDIALOG_

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
#include "Font.h"

namespace wstyle {

	class FontDialog
	{
	protected:
		CHOOSEFONT cf;
		LOGFONT lf;
		void Clone(const FontDialog fd);
	public:
		FontDialog();
		FontDialog(HWND hWnd, HINSTANCE hInstance = nullptr);
		FontDialog(const FontDialog& fd) : FontDialog() { Clone(fd); }
		FontDialog& operator = (const FontDialog& fd);
		virtual bool ShowDialog();
		virtual bool ShowDialog(HWND hWnd);
		Font GetFont() const { return Font(lf); };
		COLORREF GetColor() const { return cf.rgbColors; }
		virtual ~FontDialog() {};
	};


}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_FONTDIALOG_