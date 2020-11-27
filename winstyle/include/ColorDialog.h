//
// ColorDialog.h
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

#ifndef _WINSTYLE_COLORDIALOG_
#define _WINSTYLE_COLORDIALOG_

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
#include "Color.h"

namespace wstyle {

	class ColorDialog
	{
	protected:
		CHOOSECOLOR cc;
		static COLORREF dColors[16];
		void Clone(const ColorDialog& cd);
	public:
		ColorDialog();
		ColorDialog(HWND hWnd, HINSTANCE hInstance = nullptr);
		ColorDialog(const ColorDialog& cd) :ColorDialog() { Clone(cd); }
		ColorDialog& operator = (const ColorDialog& cd);
		virtual bool ShowDialog();
		virtual bool ShowDialog(HWND hWnd);
		Color GetColor() const { return Color(cc.rgbResult); };
		virtual ~ColorDialog() {};
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_COLORDIALOG_