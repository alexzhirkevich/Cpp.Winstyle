//
// TrayIcon.h
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

#ifndef _WINSTYLE_TRAYICON_
#define _WINSTYLE_TRAYICON_

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

	class TrayIcon /* Tray icon class for WinApi */
	{
	protected:
		NOTIFYICONDATA pnid{ sizeof(NOTIFYICONDATA) };
		static UINT uID;
		void Clone(const TrayIcon& ti);
	public:
		UINT GetCallbackMsg() { return pnid.uCallbackMessage; }
		TrayIcon(const TrayIcon& trIcon) { Clone(trIcon); };
		TrayIcon& operator = (const TrayIcon& trIcon);
		TrayIcon();
		TrayIcon(HICON hIcon, int CallbackMessage, PCTCH Tip) :TrayIcon() { Load(hIcon, CallbackMessage, Tip); }
		void Load(HICON icon, int CallBackMessage, PCTCH tip);
		bool Set(HWND hwnd); /* Set tray icon for hwnd */
		bool Remove(); /* Delete tray icon */
		HWND GetOwner() const { return pnid.hWnd; }
		virtual ~TrayIcon() { Remove(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_TRAYICON_