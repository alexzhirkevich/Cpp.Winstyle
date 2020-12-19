//
// Sound.h
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

#ifndef _WINSTYLE_SOUND_
#define _WINSTYLE_SOUND_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

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

#endif // _WINSTYLE_SOUND_