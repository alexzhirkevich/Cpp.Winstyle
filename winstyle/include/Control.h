//
// Control.h
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

#ifndef _WINSTYLE_CONTROL_
#define _WINSTYLE_CONTROL_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"

namespace wstyle {

	class Window;
	class AbstractAction;
	class MenuItem;

	enum class ControlType { Button, EditText, ProgressBar };

	class Control {
		friend class Window;
		friend class MenuItem;

	private:
		static int controlID;
		int id;
	protected:
		ControlType type;
		const AbstractAction* action;
		HWND hWnd;
		_tstring text;
		DWORD style;
		Window* owner;
		virtual void Clone(const Control& control);
		virtual void Create(int x, int y, int width, int height, DWORD style);
		virtual ~Control();
	public:
		Control(Window* form, ControlType type);
		int GetMenuID() const;
		Window* GetParent() const;
		HWND GetHWND() const;
		_tstring GetText() const;
		bool SetText(PCTCH text);
		virtual bool  SetStyle(DWORD style) = 0;
		bool SetBounds(int x, int y, int width, int height);         
		RECT  GetRectangle() const;
		void addActionListener(const AbstractAction* action);
		void Delete();
		void SetVisible(bool isVisible);
	};

}

#endif // _WINSTYLE_CONTROL_