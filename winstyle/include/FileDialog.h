//
// FileDialog.h
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

#ifndef _WINSTYLE_FILEDIALOG_
#define _WINSTYLE_FILEDIALOG_

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
	class FileDialog {
	protected:
		OPENFILENAME of;
		PTCHAR buff;
		void Clone(const FileDialog& fd);
	public:
		FileDialog();
		FileDialog(HWND hWnd, HINSTANCE hInstance = nullptr);
		FileDialog(const FileDialog& fd) :FileDialog() { Clone(fd); }
		FileDialog& operator = (const FileDialog& fd);
		void SetFilter(PCTCH lpsFilter) { of.lpstrFilter = lpsFilter; }
		void SetFlags(int flags) { of.Flags = flags; }
		_tstring GetFileName() const { return buff; }
		virtual bool ShowDialog() = 0;
		virtual bool ShowDialog(HWND hWnd) = 0;
		void Erase();
		virtual ~FileDialog() { Erase(); }
	};
}


#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_FILEDIALOG_