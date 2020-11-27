#include "../include/Button.h"

inline wstyle::Button::Button(const Button& b) : Button(b.owner) { Clone(b); }

bool wstyle::Button::SetStyle(DWORD style)
{
	if (!__super::SetStyle(style))
		return false;
	RECT r = GetRectangle();
	DestroyWindow(hWnd);
	Create(r.left, r.top, r.right - r.left, r.bottom - r.top, style);
	return hWnd != INVALID_HANDLE_VALUE;
}

inline void wstyle::Button::Clone(const Button& b) {
	__super::Clone(b);
	RECT r = b.GetRectangle();
	Create(r.top, r.left, r.right - r.left, r.bottom - r.top, style);
}

inline wstyle::Button& wstyle::Button::operator = (const Button& b) {
	if (this == &b)
		return *this;
	
	Delete();
	Clone(b);
	return *this;
}

inline wstyle::Button::Button(Window* form) : Control(form, ControlType::Button)
{
	style = style | BS_PUSHBUTTON;
	Create(0, 0, 0, 0, style);
}