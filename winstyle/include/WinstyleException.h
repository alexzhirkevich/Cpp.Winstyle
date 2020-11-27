//
// Progressbar.h
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

#ifndef WINSTYLE_WSTYLEEXCEPTION_
#define WINSTYLE_WSTYLEEXCEPTION_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"

namespace wstyle {

	
	class WstyleException {
	protected:	
		_tstring message;
	public:
		WstyleException(PCTCH message) {
			this->message = message;
		}

		_tstring what() {
			return message;
		}

	};
}

#endif //WINSTYLE_WSTYLEEXCEPTION_