#include "../include/FontDialog.h"

inline void wstyle::FontDialog::Clone(const FontDialog fd) {
	cf = fd.cf;
	lf = fd.lf;
	_tcscpy_s(lf.lfFaceName, _tcslen(fd.lf.lfFaceName)*sizeof(TCHAR), fd.lf.lfFaceName);
	cf.lpLogFont = &lf;
}

inline wstyle::FontDialog::FontDialog() {
	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	lf.lfHeight = 20;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
	cf.hwndOwner = nullptr;
	cf.lpLogFont = &lf;
	cf.rgbColors = RGB(0, 0, 0);
}

inline wstyle::FontDialog::FontDialog(HWND hWnd, HINSTANCE hInstance) : FontDialog() {
	cf.hwndOwner = hWnd;
	cf.hInstance = hInstance;
}

inline bool wstyle::FontDialog::ShowDialog() {
	if (ChooseFont(&cf))
		return true;
	return false;
}

inline bool wstyle::FontDialog::ShowDialog(HWND hWnd) {
	HWND hPrevOwner = cf.hwndOwner;
	cf.hwndOwner = hWnd;
	if (ChooseFont(&cf))
	{
		cf.hwndOwner = hPrevOwner;
		return true;
	}
	cf.hwndOwner = hPrevOwner;
	return false;
}

inline wstyle::FontDialog& wstyle::FontDialog::operator=(const FontDialog& fd) {
	if (this == &fd)
		return *this;
	Clone(fd);
	return *this;
}