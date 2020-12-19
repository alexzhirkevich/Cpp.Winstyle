//
// Color.h
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

#ifndef _WINSTYLE_CHILDCLASS_
#define _WINSTYLE_CHILDCLASS_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Init.h"

namespace wstyle {
	template <typename FatherClass>
	class ChildClass
	{
	protected:
		FatherClass* owner;
	public:
		ChildClass() :owner(nullptr) { };
		ChildClass(FatherClass* Owner) : owner(Owner) {};
	};
}

#endif // _WINSTYLE_CHILDCLASS_