//
// MenuBar.h
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

#ifndef _WINSTYLE_MENUBAR_
#define _WINSTYLE_MENUBAR_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"
#include "Menu.h"

namespace wstyle {


	class Window;
	class Menu;
	class MenuItem;

	class MenuBar : private Menu {

		friend class Menu;
		friend class MenuItem;
		friend class Window;

	protected:
		std::vector<Menu*> menus;
		std::vector<MenuItem*> menuItems;
		Window* owner;
		HMENU hMenu;
	public:
		MenuBar();
		bool add(MenuItem* menu);
		bool add(Menu* menu);
		bool set(Window* owner);
	};

}

#endif //_WINSTYLE_MENUBAR_