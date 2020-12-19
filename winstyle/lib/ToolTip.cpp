#include "../include/ToolTip.h"

 wstyle::ToolTip::ToolTip() : hWndToolTip(nullptr), title(nullptr), isOn(false) {
	toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.uFlags = TTF_SUBCLASS;
	title = new TCHAR[4];
	title = TEXT("Tip");
};

 wstyle::ToolTip::ToolTip(const ToolTip& tTip) : ToolTip() {

	toolInfo.hwnd = tTip.toolInfo.hwnd;
	toolInfo.lpszText = new TCHAR[_tcslen(tTip.toolInfo.lpszText) + 1];
	_tcscpy_s(toolInfo.lpszText, _tcslen(tTip.toolInfo.lpszText) * sizeof(TCHAR), tTip.toolInfo.lpszText);
	toolInfo.rect = tTip.toolInfo.rect;
	isOn = tTip.isOn;
	title = tTip.title;
	Create(toolInfo.hwnd, title.c_str());
}

 wstyle::ToolTip& wstyle::ToolTip::operator=(const ToolTip& tTip) {
	if (this == &tTip)
		return *this;
	Erase();
	Create(tTip.hWndToolTip, tTip.title.c_str());
	return *this;
}

 bool wstyle::ToolTip::Create(HWND owner, PCTCH pszText) {
	if (!owner || !pszText)
		return false;

	hWndToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, nullptr,
		WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX,
		0, 0, 0, 0,
		owner, nullptr, nullptr, nullptr);

	if (!hWndToolTip)
		return false;

	if (title != pszText) {
		title = pszText;
	}

	toolInfo.hwnd = owner;
	toolInfo.lpszText = (PTCHAR)pszText;
	GetClientRect(owner, &toolInfo.rect);
	if (!SendMessage(hWndToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo))
		return false;
	isOn = true;
	return true;
}

 bool wstyle::ToolTip::SetTip(PCTCH pszText) {
	if (!pszText)
		return false;
	title = pszText;
	toolInfo.lpszText = (PTCHAR)pszText;
	SendMessage(hWndToolTip, TTM_UPDATETIPTEXT, 0, (LPARAM)&toolInfo);
	return true;
}

 bool wstyle::ToolTip::SetParent(HWND owner) {
	if (!Erase())
		return false;
	return Create(owner, title.c_str());
}

 bool wstyle::ToolTip::Disable() {
	if (!isOn)
		return false;
	SendMessage(hWndToolTip, TTM_DELTOOL, 0, (LPARAM)&toolInfo);
	isOn = false;
	return true;
}

 bool wstyle::ToolTip::Enable() {
	if (isOn || !hWndToolTip)
		return false;
	SendMessage(hWndToolTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
	isOn = true;
	return true;
}

 bool wstyle::ToolTip::Erase() {
	if (!DestroyWindow(hWndToolTip))
		return false;
	hWndToolTip = nullptr;
	return true;
	title = nullptr;
}