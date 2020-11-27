#include "../include/Webcam.h"

bool wstyle::Webcam::Dialog::VideoSource() {
	if (!owner)
		return false;
	if (owner->CapDrvCaps.fHasDlgVideoSource) {
		capDlgVideoSource(owner->hWnd);
		return true;
	}
	return false;
}

inline bool wstyle::Webcam::Dialog::VideoFormat() {
	if (!owner)
		return false;
	if (owner->CapDrvCaps.fHasDlgVideoFormat) {
		capDlgVideoFormat(owner->hWnd);
		return true;
	}
	return false;
}

inline bool wstyle::Webcam::Dialog::VideoDisplay() {
	if (!owner)
		return false;
	if (owner->CapDrvCaps.fHasDlgVideoDisplay) {
		capDlgVideoDisplay(owner->hWnd);
		return true;
	}
	return false;
}

inline wstyle::Webcam::Webcam() : wndWidth(640), wndHeight(480),
hWnd(nullptr), Dialog(this), Overlay(this), Settings(this), State(this){
	wndName = new TCHAR[_tcslen(TEXT("Cam")) + 1];
	
	_tcscpy_s(wndName,_tcslen(TEXT("Cam"))*sizeof(TCHAR), TEXT("Cam"));
}

inline void wstyle::Webcam::Create(HWND hWndOwner, int x, int y, int Width, int Height,
	int camResolutionWidth, int camResolutionHeight, int camWindowStyle) {
	if (!hWndOwner)
		return;
	const_cast<HWND&>(hWnd) = capCreateCaptureWindow(wndName, camWindowStyle,
		pos.x = x, pos.y = y, wndWidth = Width, wndHeight = Height, hFatherWnd = hWndOwner, 0);
	//SendMessage(hWnd, WM_CAP_DRIVER_CONNECT, 0, 0L);
	//SendMessage(hWndOwner, WM_CAP_SEQUENCE, 0, 0L);
	capDriverConnect(hWnd, 0);
	capFileSetCaptureFile(hWnd, TEXT("file.avi"));
	UpdateWindow(hWnd);
	State.Show();
	Settings.SetRefreshRate(60);
	capPreviewScale(hWnd, true);
	capDriverGetCaps(hWnd, &CapDrvCaps, sizeof(CAPDRIVERCAPS));
	capCaptureGetSetup(hWnd, &CaptureParams, sizeof(CAPTUREPARMS));

	CaptureParams.dwRequestMicroSecPerFrame = 66667;
	CaptureParams.fMakeUserHitOKToCapture = false;
	CaptureParams.wPercentDropForError = 10;
	CaptureParams.fYield = false;
	CaptureParams.dwIndexSize = 34952;
	CaptureParams.wChunkGranularity = 0;
	CaptureParams.fUsingDOSMemory = 0;
	CaptureParams.wNumVideoRequested = 5;
	CaptureParams.fCaptureAudio = true;
	CaptureParams.wNumAudioRequested = 4;
	CaptureParams.vKeyAbort = VK_ESCAPE;
	CaptureParams.fAbortLeftMouse = true;
	CaptureParams.fAbortRightMouse = true;
	CaptureParams.fLimitEnabled = true;
	CaptureParams.wTimeLimit = 16;
	CaptureParams.fMCIControl = false;
	CaptureParams.fStepMCIDevice = false;
	CaptureParams.dwMCIStartTime = false;
	CaptureParams.dwMCIStopTime = false;
	CaptureParams.fStepCaptureAt2x = false;
	CaptureParams.wStepCaptureAverageFrames = 0;
	CaptureParams.dwAudioBufferSize = 0;
	CaptureParams.fDisableWriteCache = NULL;
	CaptureParams.AVStreamMaster = AVSTREAMMASTER_AUDIO;

	capCaptureSetSetup(hWnd, &CaptureParams, sizeof(CaptureParams));
	capGetStatus(hWnd, &CapStatus, sizeof(CAPSTATUS));
	capGetVideoFormat(hWnd, &s, sizeof(s));
	Settings.SetResolution(camResolutionWidth, camResolutionHeight);
}

inline void wstyle::Webcam::Settings::SetRefreshRate(UINT upd) {
	if (upd > 0)
		capPreviewRate(owner->hWnd, 1000 / upd);
}

inline bool wstyle::Webcam::Settings::SetResolution(int camResolutionWidth, int camResolutionHeight) {
	if (!(camResolutionHeight > 0 && camResolutionWidth > 0))
		return false;
	capGetVideoFormat(owner->hWnd, &owner->s, sizeof(owner->s));
	int prevW = owner->s.bmiHeader.biWidth, prevH = owner->s.bmiHeader.biHeight, prevS = owner->s.bmiHeader.biSizeImage;
	owner->s.bmiHeader.biWidth = camResolutionWidth;
	owner->s.bmiHeader.biHeight = camResolutionHeight;
	owner->s.bmiHeader.biSizeImage = owner->s.bmiHeader.biWidth * owner->s.bmiHeader.biHeight * 3;
	capSetVideoFormat(owner->hWnd, &owner->s, sizeof(owner->s));
	capGetVideoFormat(owner->hWnd, &owner->s, sizeof(owner->s));
	if (!(owner->s.bmiHeader.biWidth == camResolutionWidth && owner->s.bmiHeader.biHeight == camResolutionHeight)) {
		owner->s.bmiHeader.biWidth = prevW;
		owner->s.bmiHeader.biHeight = prevH;
		owner->s.bmiHeader.biSizeImage = prevS;
		capSetVideoFormat(owner->hWnd, &owner->s, sizeof(owner->s));
		return false;
	}
	return true;
}

inline void wstyle::Webcam::Settings::SetBounds(int x, int y, int width, int height) {
	SetWindowPos(owner->hWnd, 0, x, y, width, height, 0);
}

inline bool wstyle::Webcam::Settings::SetWindowName(PCTCH title) {
	if (!title)
		return false;
	delete[] owner->wndName;
	owner->wndName = new TCHAR[_tcslen(title) + 1];
	_tcscpy_s(owner->wndName, _tcslen(title)*sizeof(TCHAR), title);
	return SetWindowText(owner->hWnd, owner->wndName);
}

void wstyle::Webcam::Overlay::Enable() {
	if (owner->CapDrvCaps.fHasOverlay)
		capOverlay(owner->hWnd, TRUE);
}

void wstyle::Webcam::Overlay::Disable() {
	if (owner->CapDrvCaps.fHasOverlay)
		capOverlay(owner->hWnd, FALSE);
}

inline void wstyle::Webcam::State::Show() {
	if (!owner->hWnd)
		return;
	capPreview(owner->hWnd, TRUE);
	ShowWindow(owner->hWnd, SW_SHOW);
}

inline void wstyle::Webcam::State::Hide() {
	capPreview(owner->hWnd, FALSE);
	ShowWindow(owner->hWnd, SW_HIDE);
}

inline bool wstyle::Webcam::MakePhoto(PCTCH fileName) {
	capCaptureSequence(hWnd);
	capGrabFrame(hWnd);
	//PAVIFILE pf;
	////if (capEditCopy(hWnd))
	//	AVIGetFromClipboard(&pf);
	return capFileSaveDIB(hWnd, fileName);
}

inline void wstyle::Webcam::Delete() {
	capDriverDisconnect(hWnd);
	DestroyWindow(hWnd);
	delete[] wndName;
	wndName = nullptr;
}