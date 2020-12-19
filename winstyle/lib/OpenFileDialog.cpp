#include "../include/OpenFileDialog.h"

  bool wstyle::OpenFileDialog::ShowDialog() {
	if (GetOpenFileName(&of))
		return true;
	return false;
}

 bool wstyle::OpenFileDialog::ShowDialog(HWND hWnd) {
	HWND hPrevOwner = of.hwndOwner;
	of.hwndOwner = hWnd;
	if (GetOpenFileName(&of))
	{
		of.hwndOwner = hPrevOwner;
		return true;
	}
	of.hwndOwner = hPrevOwner;
	return false;
}
