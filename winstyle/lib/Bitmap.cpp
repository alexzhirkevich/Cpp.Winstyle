#include "../include/Bitmap.h"


inline wstyle::Bitmap::Bitmap() :hbitmap(nullptr), hdc(nullptr), id(0), hWnd(nullptr), hInstance(nullptr) {
	ZeroMemory(&bitmap, sizeof(BITMAP));
}

inline void wstyle::Bitmap::Clone(const Bitmap& bmp) {
	if (!bmp.path.empty())
		Load(bmp.hWnd, bmp.path.c_str());
	else
		Load(bmp.hWnd, bmp.hInstance, bmp.id);
}

inline wstyle::Bitmap& wstyle::Bitmap::operator=(const Bitmap& p) {
	if (this == &p)
		return *this;
	Erase();
	Clone(p);
	return *this;
}

inline bool wstyle::Bitmap::Load(HWND hwnd, PCTCH _path) {

	if (!_path || !hwnd)
		return false;

	hWnd = hwnd;

	path = new TCHAR[_tcslen(_path) + 1];
	path =_path;

	if (!(hbitmap = (HBITMAP)LoadImage(NULL, _path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)))
		return false;

	ZeroMemory(&bitmap, sizeof(BITMAP));
	GetObject(hbitmap, sizeof(bitmap), (LPVOID)&bitmap);
	HDC tmp = GetDC(hwnd);
	if (!(hdc = CreateCompatibleDC(tmp)))
		return false;
	SelectObject(hdc, hbitmap);
	ReleaseDC(hwnd, tmp);
	return true;
}

inline bool wstyle::Bitmap::Load(HWND _hwnd, HINSTANCE _hInst, int IDB_BITMAP) {

	if (!_hwnd)
		return false;

	id = IDB_BITMAP;
	hWnd = _hwnd;
	hInstance = _hInst;

	if (!(hbitmap = LoadBitmap(_hInst, (PCTCH)IDB_BITMAP)))
		return false;

	ZeroMemory(&bitmap, sizeof(BITMAP));
	GetObject(hbitmap, sizeof(bitmap), (LPVOID)&bitmap);
	HDC tmp = GetDC(_hwnd);
	if (!(hdc = CreateCompatibleDC(tmp)))
		return false;
	SelectObject(hdc, hbitmap);
	ReleaseDC(_hwnd, tmp);
	return true;
}

inline bool wstyle::Bitmap::Paint(HDC hDC, int x, int y) const {
	if (!hdc)
		return false;

	return BitBlt(hDC, x, y, bitmap.bmWidth, bitmap.bmHeight, hdc, 0, 0, SRCCOPY);
}

bool wstyle::Bitmap::Erase() {
	path = nullptr;
	id = 0;
	hWnd = nullptr;
	hInstance = nullptr;
	ZeroMemory(&bitmap, sizeof(BITMAP));
	return (DeleteObject(hbitmap) && DeleteDC(hdc));
}