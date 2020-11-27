#include "../include/EditText.h"


inline void wstyle::EditText::Clone(const EditText& b) {
	__super::Clone(b);
	RECT r = b.GetRectangle();
	Create(r.top, r.left, r.right - r.left, r.bottom - r.top, style);
}

inline wstyle::EditText& wstyle::EditText::operator = (const EditText& b) {
	if (this == &b)
		return *this;

	Delete();
	Clone(b);
	return *this;
}

inline bool wstyle::EditText::SetStyle(DWORD style)
{
	if (!__super::SetStyle(style))
		return false;
	RECT r = GetRectangle();
	Create(r.top, r.left, r.right - r.left, r.bottom - r.top, style);
	return hWnd != INVALID_HANDLE_VALUE;
}

inline wstyle::EditText::EditText(Window* form) : Control(form, ControlType::EditText)
{
	Create(0, 0, 0, 0, style);
}