//
// Control.h
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

#ifndef _WINSTYLE_CONTROL_
#define _WINSTYLE_CONTROL_

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
#include "Window.h"

namespace wstyle {

	enum class ControlType { Button, EditText, ProgressBar };

	class Control {
	private:
		static int controlID;
		int id;
	protected:
		ControlType type;
		HWND hWnd;
		_tstring text;
		DWORD style;
		Window* owner;
		virtual void Clone(const Control& control);
		virtual void Create(int x, int y, int width, int height, DWORD style);
	public:
		Control(Window* form, ControlType type);
		int GetMenuID() const { return id; }
		Window* GetParent() const { return owner; }
		HWND GetHWND() const { return hWnd; }
		_tstring GetText() const;
		bool SetText(PCTCH text);
		virtual bool SetStyle(DWORD style) = 0;
		bool SetBounds(int x, int y, int width, int height);         
		RECT GetRectangle() const;
		void Delete();
		void Visible(bool isVisible);
		virtual ~Control();
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_CONTROL_