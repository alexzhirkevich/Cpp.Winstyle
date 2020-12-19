#include "../include/EditText.h"


 void wstyle::EditText::Clone(const EditText& b) {
	__super::Clone(b);
	RECT r = b.GetRectangle();
	Create(r.top, r.left, r.right - r.left, r.bottom - r.top, style);
}

 wstyle::EditText& wstyle::EditText::operator = (const EditText& b) {
	if (this == &b)
		return *this;

	Delete();
	Clone(b);
	return *this;
}

 bool wstyle::EditText::SetStyle(DWORD style)
{
	if (!__super::SetStyle(style))
		return false;
	RECT r = GetRectangle();
	Create(r.top, r.left, r.right - r.left, r.bottom - r.top, style);
	return hWnd != INVALID_HANDLE_VALUE;
}

 wstyle::EditText::EditText(Window* form) : Control(form, ControlType::EditText)
{
	Create(0, 0, 0, 0, style);
}