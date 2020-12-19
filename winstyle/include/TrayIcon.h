//
// TrayIcon.h
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

#ifndef _WINSTYLE_TRAYICON_
#define _WINSTYLE_TRAYICON_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


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

#endif // _WINSTYLE_TRAYICON_