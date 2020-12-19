//
// EditText.h
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

#ifndef _WINSTYLE_EDITTEXT_
#define _WINSTYLE_EDITTEXT_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"
#include "Control.h"

namespace wstyle {

	class EditText : public Control {
		using Control::Control;
	protected:
		void Clone(const EditText& b);
	public:
		EditText(Window* window);
		EditText(const EditText& b);
		EditText& operator = (const EditText& b);
		bool SetStyle(DWORD style) override;
	};

}


#endif // _WINSTYLE_EDITTEXT_