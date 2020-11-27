#include "../include/FileDialog.h"

#if defined __MSC_VER
#if _MSC_VER >= 1200
#pragma warning(push)
#endif // _MSC_VER >= 1200
#endif // _MSC_VER

#pragma warning(disable:4996)

inline void wstyle::FileDialog::Clone(const FileDialog& fd) {
	of = fd.of;
	if (fd.buff) {
		buff = new TCHAR[_tcslen(fd.buff) + 1];
		_tcscpy(buff, fd.buff);
	}
	of.lpstrFile = buff;
}

inline wstyle::FileDialog::FileDialog() {
	ZeroMemory(&of, sizeof(OPENFILENAME));
	buff = new TCHAR[MAX_PATH];
	buff[0] = '\0';
	of.lStructSize = sizeof(OPENFILENAME);
	of.hwndOwner = nullptr;
	of.hInstance = nullptr;
	of.lpstrFilter = TEXT("All files (*.*)\0*.*\0");
	of.lpstrCustomFilter = nullptr;
	of.nMaxCustFilter = 0;
	of.nFilterIndex = 1;
	of.lpstrFile = buff;
	of.nMaxFile = MAX_PATH;
	of.lpstrFileTitle = nullptr;
	of.nMaxFileTitle = 0;
	of.lpstrInitialDir = nullptr;
	of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
}

inline wstyle::FileDialog::FileDialog(HWND hWnd, HINSTANCE hInstance) :FileDialog() {
	of.hwndOwner = hWnd;
	of.hInstance = hInstance;
}

inline void wstyle::FileDialog::Erase() {
	delete[] buff;
	buff = nullptr;
}

inline wstyle::FileDialog& wstyle::FileDialog::operator=(const FileDialog& fd) {
	if (this == &fd)
		return *this;
	Erase();
	Clone(fd);
	return *this;
}

#if defined __MSC_VER
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif // _MSC_VER >= 1200
#endif // _MSC_VER