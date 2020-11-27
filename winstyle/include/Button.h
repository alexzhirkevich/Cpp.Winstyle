//
// Button.h
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

#ifndef _WINSTYLE_BUTTON_
#define _WINSTYLE_BUTTON_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include "Control.h"

namespace wstyle {

	class Button : public Control {
	protected:
		void Clone(const Button& b);
	public:
		Button(Window* form);
		Button(const Button& b);
		Button& operator = (const Button& b);
		bool SetStyle(DWORD style) override;
	};

}

#endif // _WINSTYLE_BUTTON_