//
// SaveFileDialog.h
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

#ifndef _WINSTYLE_SAVEFILEDIALOG_
#define _WINSTYLE_SAVEFILEDIALOG_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include "FileDialog.h"

namespace wstyle {

	class SaveFileDialog : public FileDialog
	{
	public:
		virtual bool ShowDialog();
		virtual bool ShowDialog(HWND hWnd);
	};

}

#endif // _WINSTYLE_SAVEFILEDIALOG_