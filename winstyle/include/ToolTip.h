//
// ToolTip.h
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

#ifndef _WINSTYLE_TOOLTIP_
#define _WINSTYLE_TOOLTIP_

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

namespace wstyle {

	class ToolTip
	{
	protected:
		HWND hWndToolTip;
		TOOLINFO toolInfo;
		_tstring title;
		bool isOn;
	public:
		ToolTip();
		ToolTip(HWND owner, PCTCH pszText) :ToolTip() { Create(owner, pszText); }
		ToolTip(const ToolTip& tTip);
		ToolTip& operator = (const ToolTip& tTip);
		bool Create(HWND owner, PCTCH pszText);
		bool Erase(); /* Destroy ToolTip window */
		bool Disable(); /* Disable ToolTip with enable check */
		bool Enable(); /* Enable ToolTip with disable check */
		bool SetTip(PCTCH pszText);
		bool SetParent(HWND owner);
		_tstring GetTip() { return title; }
		HWND GetWnd() const { return hWndToolTip; }
		HWND GetParent() const { return toolInfo.hwnd; }
		bool IsOn() const { return isOn; } /* Is enabled */
		virtual ~ToolTip() { Erase(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_TOOLTIP_