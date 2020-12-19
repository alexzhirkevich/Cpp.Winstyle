#include "../include/Sound.h"

void wstyle::ToggleSounds() {
	if (Sound::IsOn) {
		PlaySound(nullptr, nullptr, 0);
		Sound::IsOn = false;
	}
	else Sound::IsOn = true;
}

bool wstyle::Sound::IsOn = true;

 void wstyle::Sound::Clone(const Sound& s) {
	if (!path.empty())
		SetPath(s.path.c_str());
	else
		Load(s.id);
}

 wstyle::Sound& wstyle::Sound::operator=(const Sound& s) {
	if (this == &s)
		return *this;
	Erase();
	Clone(s);
	return *this;
}

 bool wstyle::Sound::Load(int RES_ID)
{
	hMod = GetModuleHandle(nullptr); if (!hMod) return false;
	HRSRC hRes = FindResource(hMod, (PCTCH)RES_ID, RT_RCDATA); if (!hRes) return false;
	hGlob = LoadResource(hMod, hRes); if (!hGlob) return false;
	lpbArray = (BYTE*)LockResource(hGlob); if (!lpbArray) return false;
	return true;
}

 void wstyle::Sound::SetPath(PCTCH _path) {
	path = _path;
}

 bool wstyle::Sound::Play(DWORD fdwSound) const {
	if ((path.empty() && !lpbArray) || (!IsOn))
		return false;
	if (!path.empty())
		return PlaySound(path.c_str(), hMod, fdwSound);
	if (lpbArray)
		return PlaySound((PCTCH)lpbArray, hMod, fdwSound | SND_MEMORY);
	return false;
}

 void wstyle::Sound::Erase() {
	PlaySound(nullptr, nullptr, NULL);
	UnlockResource(hGlob);
	FreeResource(hGlob);
	hGlob = nullptr;
	path = nullptr;
	lpbArray = nullptr;
	hMod = nullptr;
	id = 0;
}