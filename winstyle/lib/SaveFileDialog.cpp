#include "../include/SaveFileDialog.h"

 bool wstyle::SaveFileDialog::ShowDialog() {
	if (GetSaveFileName(&of))
		return true;
	return false;
}

 bool wstyle::SaveFileDialog::ShowDialog(HWND hWnd) {
	of.hwndOwner = hWnd;
	if (GetSaveFileName(&of))
		return true;
	return false;
}