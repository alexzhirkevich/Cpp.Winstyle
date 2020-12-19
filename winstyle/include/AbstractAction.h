//
// AbstractAction.h
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
//
#ifndef _WINSTYLE_ABSTRACT_ACTION_
#define _WINSTYLE_ABSTRACT_ACTION_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include <functional>

namespace wstyle {

	class AbstractAction
	{
	private:
		std::function<void()> onActionPerfomed;
		AbstractAction();
		bool deleteWithControl;
		bool async;

	public:
		AbstractAction(const std::function<void()> onActionPerfomed, bool deleteWIthControl = false, bool async = false);
		void setOnActionPerfomed(const std::function<void()> onActionPerfomed);
		void setAsync(bool async);
		void setDeleteWithControl(bool del);
		void execute() const;
		bool willBeDeleted() const;
		bool isAsync() const;
	};

}


#endif //_WINSTYLE_ABSTRACT_ACTION_