//
// FontDialog.h
//
//      By Alexandr Zhirkevich.
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
#endif // _MSC_VER


#include "Init.h"
#include "Font.h"

namespace wstyle {

	class FontDialog
	{
	protected:
		CHOOSEFONT cf;
		LOGFONT lf;
		void Clone(const FontDialog& fd);
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

#endif // _WINSTYLE_FONTDIALOG_