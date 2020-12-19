#include "../include/TrayIcon.h"

UINT wstyle::TrayIcon::uID = 20001;

 void wstyle::TrayIcon::Load(HICON icon, int CallBackMessage, PCTCH tip) {
	pnid.hIcon = icon;
	pnid.uCallbackMessage = CallBackMessage;
	_tcscpy_s(pnid.szTip, sizeof(pnid.szTip), tip);
}

 wstyle::TrayIcon::TrayIcon() {
	pnid.cbSize = sizeof(NOTIFYICONDATA);
	pnid.hWnd = NULL;
	pnid.hIcon = (HICON)LoadIcon(0, IDI_APPLICATION);
	pnid.uID = ++uID;
	pnid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	pnid.uCallbackMessage = 0;
	_tcscpy_s(pnid.szTip, sizeof(pnid.szTip), TEXT(""));
}

 wstyle::TrayIcon& wstyle::TrayIcon::operator = (const TrayIcon& trIcon) {
	if (this == &trIcon)
		return *this;
	Clone(trIcon);
};

 void wstyle::TrayIcon::Clone(const TrayIcon& ti) {
	pnid.hWnd = ti.pnid.hWnd;
	pnid.hIcon = ti.pnid.hIcon;
	pnid.uFlags = ti.pnid.uFlags;
	_tcscpy_s(pnid.szTip, sizeof(pnid.szTip), ti.pnid.szTip);
}

 bool wstyle::TrayIcon::Set(HWND hwnd) { pnid.hWnd = hwnd; return Shell_NotifyIcon(NIM_ADD, &pnid); }

 bool wstyle::TrayIcon::Remove() { return Shell_NotifyIcon(NIM_DELETE, &pnid); }
