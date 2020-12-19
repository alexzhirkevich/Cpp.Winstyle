#include "../include/ColorDialog.h"

COLORREF wstyle::ColorDialog::dColors[16] = { RGB(255, 0, 0),RGB(255, 140, 0),RGB(255, 255, 0),
	RGB(0, 128, 0),RGB(30, 144, 255),RGB(0, 0, 255), RGB(128, 0, 128),RGB(0, 0, 0),
	RGB(255, 255, 255),RGB(128, 128, 128),RGB(0, 255, 255),RGB(0, 100, 0),
	RGB(128, 128, 0),RGB(139, 69, 19),RGB(210, 180, 140), RGB(199, 21, 133) };

 void wstyle::ColorDialog::Clone(const ColorDialog& cd) {
	cc = cd.cc;
	for (int i = 0; i < 16; i++)
		dColors[i] = cd.dColors[i];
	cc.lpCustColors = dColors;
}

 wstyle::ColorDialog::ColorDialog() {
	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = nullptr;
	cc.hInstance = nullptr;
	cc.rgbResult = RGB(0, 0, 0);
	cc.lpfnHook = NULL;
	cc.lpTemplateName = nullptr;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0L;
	cc.lpCustColors = dColors;
}

 wstyle::ColorDialog::ColorDialog(HWND hWnd, HINSTANCE hInstance) : ColorDialog() {
	cc.hwndOwner = hWnd;
	cc.hInstance = (HWND)hInstance;
}

 bool wstyle::ColorDialog::ShowDialog() {
	if (ChooseColor(&cc))
		return true;
	return false;
}

 bool wstyle::ColorDialog::ShowDialog(HWND hWnd) {
	HWND hPrevOwner = cc.hwndOwner;
	cc.hwndOwner = hWnd;
	if (ChooseColor(&cc))
	{
		cc.hwndOwner = hPrevOwner;
		return true;
	}
	cc.hwndOwner = hPrevOwner;
	return false;
}

 wstyle::ColorDialog& wstyle::ColorDialog::operator=(const ColorDialog& cd) {
	if (this == &cd)
		return *this;
	Clone(cd);
	return *this;
}