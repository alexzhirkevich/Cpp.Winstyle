#include "../include/SaveFileDialog.h"

inline bool wstyle::SaveFileDialog::ShowDialog() {
	if (GetSaveFileName(&of))
		return true;
	return false;
}

inline bool wstyle::SaveFileDialog::ShowDialog(HWND hWnd) {
	of.hwndOwner = hWnd;
	if (GetSaveFileName(&of))
		return true;
	return false;
}