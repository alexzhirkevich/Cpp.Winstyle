//
// Init.h
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

#ifndef _WSTYLE_INIT_
#define _WSTYLE_INIT_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <commctrl.h>
#include <exception>
#include <ctime>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <shellapi.h>
#include <Vfw.h>
#include <gdiplus.h>
#include <string>
#include <thread>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Vfw32.lib")
#pragma comment(lib,"Gdiplus.lib")

#ifndef WSTYLE_OLD_INTERFACE
#pragma comment(linker,"\"/manifestdependency:type='win32' \
		name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
		processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif //WSTYLE_OLD_INTERFACE

#define WSTYLE_VER 201127

#define WSTYLE_MAXSTR		256

#if defined WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#ifdef UNICODE
#define WSTYLE_UNICODE_DEFINED true
#define _tstring	std::wstring
#define	to_tstring	std::to_wstring
#define _tfstream	std::wfstream
#define _tistream	std::wistream
#define _tostream	std::wostream
#define _tifstream	std::wifstream
#define _tofstream	std::wofstream
#else
#define WSTYLE_UNICODE_DEFINED false
#define _tstring	std::string
#define to_tstring	std::to_string
#define _tfstream	std::fstream
#define _tistream	std::istream
#define _tostream	std::ostream
#define _tifstream	std::ifstream
#define _tofstream	std::ofstream
#endif //UNICODE

#endif // !_WSTYLE_INIT_