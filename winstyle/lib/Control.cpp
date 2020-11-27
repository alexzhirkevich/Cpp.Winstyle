#include "../include/Control.h"

inline wstyle::Control::Control(Window* form, ControlType type) : type(type), id(controlID++), 
	style(WS_CHILD | WS_VISIBLE), hWnd(nullptr), owner(form), text(TEXT("Control")) {}

void wstyle::Control::Create(int x, int y, int width, int height, DWORD style)
{
	if (hWnd != nullptr)
		Delete();
	switch (type) {
	case ControlType::Button:
		hWnd = CreateWindow(TEXT("Button"), text.c_str(), style,
			x, y, width, height,
			owner->Get.hWnd(), (HMENU)GetMenuID(), nullptr, nullptr);
		break;
	case ControlType::EditText:
		hWnd = CreateWindow(TEXT("Edit"), text.c_str(), style,
			x, y, width, height,
			owner->Get.hWnd(), (HMENU)GetMenuID(), nullptr, nullptr);
		break;
	case ControlType::ProgressBar:
		hWnd = CreateWindowEx(0, PROGRESS_CLASS, TEXT("ProgressBar"), WS_CHILD | WS_BORDER | WS_VISIBLE,
			x, y, width, height, owner->Get.hWnd(), NULL, nullptr, NULL);
		SendMessage(hWnd, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 10));
		SendMessage(hWnd, PBM_SETSTEP, (WPARAM)1, 0);
		break;
	}
}

inline bool wstyle::Control::SetText(PCTCH text) {
	if (!text)
		return false;
	this->text = text;
	return SetWindowText(hWnd, text);
}

inline _tstring wstyle::Control::GetText() const {
	return text;
}

inline bool wstyle::Control::SetBounds(int x, int y, int width, int height) {
	return SetWindowPos(hWnd, 0, x, y, width, height, 0);
}

inline bool wstyle::Control::SetStyle(DWORD style)
{
	if (this->style == style)
		return false;
	this->style = style;
	return true;
}

inline RECT wstyle::Control::GetRectangle() const { 
	RECT r;
	::GetWindowRect(hWnd,&r);
	return r;
}

void wstyle::Control::Clone(const Control& control)
{
	if (this == &control)
		return;
	this->owner = control.owner;
	this->text = control.text;
}

inline void wstyle::Control::Delete() {
	DestroyWindow(hWnd);
	hWnd = nullptr;
}

inline void wstyle::Control::Visible(bool isVisible) {
	if (isVisible)
		ShowWindow(hWnd, SW_SHOW);
	else
		ShowWindow(hWnd, SW_HIDE);
}

inline wstyle::Control::~Control() { Delete(); };

int wstyle::Control::controlID = 10001;