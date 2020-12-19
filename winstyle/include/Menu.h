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

#ifndef _WINSTYLE_MENU_
#define _WINSTYLE_MENU_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"
#include "MenuItem.h"

namespace wstyle {


	class MenuBar;
	class MenuItem;
	class Window;
	
	enum MenuStyle {Bitmap, Checked, String, };

	class Menu : public MenuItem{

		friend class MenuBar;
		friend class MenuItem;
		friend class Window;
		
	protected:
		MenuBar* owner;

		std::vector<MenuItem*> items;

		~Menu();

	public:

		Menu();
		Menu(PCTCH title);

		bool add(MenuItem* mi);

		void Delete();
	};

}

#endif //_WINSTYLE_MENU_