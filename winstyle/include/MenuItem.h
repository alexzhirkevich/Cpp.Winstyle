//
// MenuItem.h
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

#ifndef _WINSTYLE_MENUITEM_
#define _WINSTYLE_MENUITEM_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"
#include <functional>

namespace wstyle {


	class Menu;
	class MenuBar;
	class AbstractAction;
	class Window;

	class MenuItem {

		friend class Menu;
		friend class MenuBar;
		friend class Window;

	protected:
		Menu* owner;

		HMENU hMenu;
		bool enabled;
		_tstring title;
		int id;

		const AbstractAction* action;
		virtual ~MenuItem();

	public:
		MenuItem();
		MenuItem(PCTCH title);

		void SetText(PCTCH text);
		_tstring GetText();
		bool SetEnabled(bool enabled);
		void addActionListener(const AbstractAction* aa);

		virtual void Delete();
	};

}

#endif //_WINSTYLE_MENUITEM_