#include "../include/Image.h"

inline wstyle::Image::Image() :img(nullptr), buf(nullptr), path(nullptr) {
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

inline void wstyle::Image::Clone(const Image& img) {
	if (img.buf) {
		delete[] buf;
		buf = new WCHAR[wcslen(img.buf) + 1];
		_tcscpy_s(buf, _tcslen(img.buf) * sizeof(WCHAR), img.buf);
	}
	if (img.path)
		Load(img.path);
}

inline bool wstyle::Image::Erase() {
	if (!img) {
		delete[] buf;
		return false;
	}
	delete[] buf;
	buf = nullptr;
	delete[] path;
	path = nullptr;
	delete img;
	img = nullptr;
	return true;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

inline wstyle::Image& wstyle::Image::operator=(const Image& img) {
	if (this == &img)
		return *this;
	Erase();
	Clone(img);
	return *this;
}

inline bool wstyle::Image::Load(PCTCH _path) {
	if (img)
		delete img;

	if (WSTYLE_UNICODE_DEFINED)
		img = new Gdiplus::Image((LPCWSTR)_path);
	else {
		if (buf)
			delete[] buf;
		buf = new WCHAR[_tcslen(_path) * 2 + 1];
		MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)_path, _tcslen(_path), buf, 0);
		img = new Gdiplus::Image(buf);
	}

	delete[] path;
	path = new TCHAR[_tcslen(_path) + 1];
	_tcscpy_s(path, _tcslen(_path) * sizeof(TCHAR), _path);

	if (img->GetLastStatus() == Gdiplus::Ok)
		return true;
	return false;
}

inline bool wstyle::Image::Paint(HDC hDC, HWND hWnd, int x, int y, int width, int height) {
	if (!img)
		return false;
	Gdiplus::Graphics graph(hDC);
	RECT rc;
	GetClientRect(hWnd, &rc);
	Gdiplus::Rect paintRect(0, 0, rc.right, rc.bottom);
	Gdiplus::Bitmap backBuffer(rc.right, rc.bottom, &graph);
	Gdiplus::Graphics temp(&backBuffer);
	temp.DrawImage(img, x, y, width, height);
	if (graph.DrawImage(&backBuffer, 0, 0, width, height) == Gdiplus::Ok)
		return true;
	else
		return false;
}