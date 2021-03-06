#include "../include/Painter.h"

 HDC wstyle::Painter::GetDC() const {
	if (_hBitmap)
		return _hMemDC;
	return paintstruct.hdc;
}

wstyle::Painter::Painter() : iWindowHeight(0), iWindowWidth(0), _iOldBkMode(0), _BkMode(TRANSPARENT),
_hMemDC(nullptr), _hBitmap(nullptr), _hOldBitmap(nullptr), _hWnd(nullptr) {
	ZeroMemory(&paintstruct, sizeof(PAINTSTRUCT));
};

wstyle::Painter::Painter(HWND hWnd, HBRUSH BgrBrush, bool isBuffered, int BkMode) : Painter() {
	Open(hWnd, BgrBrush, isBuffered, BkMode); 
};

 HDC wstyle::Painter::Open(HWND hwnd, HBRUSH BgrBrush, bool isBuffered, int BkMode)
{
	BeginPaint(hwnd, &paintstruct);
	if (isBuffered) {
		_hWnd = hwnd;
		RECT rc;
		GetClientRect(hwnd, &rc);
		iWindowWidth = rc.right - rc.left;
		iWindowHeight = rc.bottom - rc.top;
		_hMemDC = CreateCompatibleDC(paintstruct.hdc);
		_hBitmap = CreateCompatibleBitmap(paintstruct.hdc, iWindowWidth, iWindowHeight);
		_hOldBitmap = SelectBitmap(_hMemDC, _hBitmap);
		FillRect(_hMemDC, &paintstruct.rcPaint, BgrBrush);
		if (_BkMode)
			_iOldBkMode = SetBkMode(_hMemDC, _BkMode);
		return _hMemDC;
	}
	else
		return paintstruct.hdc;
}

 bool wstyle::Painter::Close()
{
	if (!_hBitmap)
		return EndPaint(_hWnd, &paintstruct);

	SetBkMode(_hMemDC, _iOldBkMode);
	BitBlt(paintstruct.hdc, 0, 0, iWindowWidth, iWindowHeight, _hMemDC, 0, 0, SRCCOPY);
	SelectBitmap(_hMemDC, _hOldBitmap);
	DeleteBitmap(_hBitmap);
	DeleteDC(_hMemDC);
	_hBitmap = nullptr;
	_hOldBitmap = nullptr;
	_hMemDC = nullptr;
	return EndPaint(_hWnd, &paintstruct);
}

 wstyle::Painter::~Painter() {
	Close();
}