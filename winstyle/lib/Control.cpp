#include "../include/Control.h"
#include "../include/Window.h"
#include "../include/AbstractAction.h"

#if defined _MSC_VER && _MSC_VER >=1200
#pragma warning(push)
#endif

#pragma warning(disable:4312)
#pragma warning(disable:6001)


  wstyle::Control::Control(Window* form, ControlType type) : type(type), id(controlID++),
	style(WS_CHILD | WS_VISIBLE), hWnd(nullptr), owner(form), text(TEXT("Control")),action(nullptr) {
	  owner->AddControl(this);
  }

int wstyle::Control::GetMenuID() const { return id; }

wstyle:: Window* wstyle::Control::GetParent() const { return owner; }

HWND wstyle::Control::GetHWND() const { return hWnd; }

void wstyle::Control::Create(int x, int y, int width, int height, DWORD style)
{
	if (hWnd != nullptr)
		Delete();
	switch (type) {
	case ControlType::Button:
 		hWnd = CreateWindow(TEXT("Button"), text.c_str(), style,
			x, y, width, height,
			owner->Get.hWnd(), reinterpret_cast<HMENU>(GetMenuID()), nullptr, nullptr);
		break;
	case ControlType::EditText:
		hWnd = CreateWindow(TEXT("Edit"), text.c_str(), style,
			x, y, width, height,
			owner->Get.hWnd(), reinterpret_cast<HMENU>(GetMenuID()), nullptr, nullptr);
		break;
	case ControlType::ProgressBar:
		hWnd = CreateWindowEx(0, PROGRESS_CLASS, TEXT("ProgressBar"), WS_CHILD | WS_BORDER | WS_VISIBLE,
			x, y, width, height, owner->Get.hWnd(), NULL, nullptr, NULL);
		SendMessage(hWnd, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0, 10));
		SendMessage(hWnd, PBM_SETSTEP, (WPARAM)1, 0);
		break;
	}
}

 bool wstyle::Control::SetText(PCTCH text) {
	if (!text)
		return false;
	this->text = text;
	return SetWindowText(hWnd, text);
}

 _tstring wstyle::Control::GetText() const {
	return text;
}

 bool wstyle::Control::SetBounds(int x, int y, int width, int height) {
	return SetWindowPos(hWnd, 0, x, y, width, height, 0);
}

 bool  wstyle::Control::SetStyle(DWORD style)
{
	if (this->style == style)
		return false;
	this->style = style;
	return true;
}

  RECT wstyle::Control::GetRectangle() const {
	RECT r;
	::GetWindowRect(hWnd,&r);
	return r;
}

  void wstyle::Control::addActionListener(const AbstractAction* action) {
	  this->action = action;
  }

void wstyle::Control::Clone(const Control& control)
{
	if (this == &control)
		return;
	this->owner = control.owner;
	this->text = control.text;
}

 void wstyle::Control::Delete() {
	DestroyWindow(hWnd);
	owner->RemoveControl(this);
	hWnd = nullptr;
	if (action && action->willBeDeleted())
		delete action;
}


 void wstyle::Control::SetVisible(bool isVisible) {
	if (isVisible)
		ShowWindow(hWnd, SW_SHOW);
	else
		ShowWindow(hWnd, SW_HIDE);
}

  wstyle::Control::~Control() { Delete(); };

int wstyle::Control::controlID = 10001;


#if defined _MSC_VER && _MSC_VER >=1200
#pragma warning(pop)
#endif
