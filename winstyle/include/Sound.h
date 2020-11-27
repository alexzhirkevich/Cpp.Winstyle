//
// Sound.h
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

#ifndef _WINSTYLE_SOUND_
#define _WINSTYLE_SOUND_

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

	void ToggleSounds();

	class Sound /* WAV sound class for WINAPI */
	{
	protected:
		int id;
		bool PrivateOn;
		HMODULE hMod;
		HGLOBAL hGlob;
		BYTE* lpbArray;
		_tstring path;
		static bool IsOn;
		void Clone(const Sound& s);
	public:
		Sound() : hGlob(nullptr), lpbArray(NULL), PrivateOn(true), hMod(nullptr), id(0) {}
		Sound(PCTCH _path) :Sound() { SetPath(_path); }
		Sound(int RESOURCE_ID) :Sound() { Load(RESOURCE_ID); }
		Sound(const Sound& s) :Sound() { Clone(s); }
		Sound& operator =(const Sound&);
		bool Load(int RESOURCE_ID);
		void SetPath(PCTCH _path);
		_tstring GetPath() const { return path; }
		bool Play(DWORD fdwSound) const;
		static friend void ToggleSounds(); /* Toggle ON/OFF mode for all SOUND objects*/
		void Erase();
		virtual ~Sound() { Erase(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_SOUND_