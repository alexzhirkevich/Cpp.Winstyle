#include "../include/Window.h"


UINT wstyle::Window::number = 0;
inline 	void wstyle::Window::Set::DoubleBufferring(bool b) const { owner->doubleBufferEnabled = b; }

inline void wstyle::Window::Set::Icon(HICON hIcon) const {
	owner->wc.hIcon = hIcon;
	owner->wc.hIconSm = hIcon;
	SetClassLongPtr(owner->hWnd, GCL_HICON, (LONG)hIcon);
}
inline void wstyle::Window::Set::Cursor(HCURSOR hCursor) const {
	owner->wc.hCursor = hCursor;
	SetClassLongPtr(owner->hWnd, GCL_HCURSOR, (LONG)hCursor);
}
inline void wstyle::Window::Set::Menu(PCTCH lpszMenuName) const {
	owner->wc.lpszMenuName = lpszMenuName;
	SetClassLongPtr(owner->hWnd, GCL_MENUNAME, (LONG)lpszMenuName);
}
inline void wstyle::Window::Set::Style(DWORD style) const {
	owner->style = style;
	SetWindowLongPtr(owner->hWnd, GWL_STYLE, style);
}
inline void wstyle::Window::Set::Title(PCTCH title) const {
	owner->title = title;
	SetWindowText(owner->hWnd, title);
}
inline void wstyle::Window::Set::Parent(Window* parent) const {
	SetParent(this->owner->hWnd, parent->hWnd);
	owner->parent = parent;
}
inline void wstyle::Window::Set::Visible(bool isVisible) const {
	if (!owner->hWnd)
		return;
	if (isVisible)
		ShowWindow(owner->hWnd, owner->_nCmdShow);
	else
		ShowWindow(owner->hWnd, SW_HIDE);
	owner->isVisible = isVisible;
}
inline void wstyle::Window::Set::Enable(bool isEnabled) const {
	if (!owner->hWnd)
		return;
	EnableWindow(owner->hWnd, isEnabled);
	owner->isEnabled = isEnabled;
}

inline int wstyle::Window::Get::Width() const { return owner->width; }
inline int wstyle::Window::Get::Height() const { return owner->height; }
inline RECT wstyle::Window::Get::ClientRect() const { RECT r; GetClientRect(owner->hWnd, &r); return r; }
inline HICON wstyle::Window::Get::Icon() const { return owner->wc.hIcon; }
inline HCURSOR wstyle::Window::Get::Cursor() const { return owner->wc.hCursor; }
inline _tstring wstyle::Window::Get::Title() const { return owner->title; }
inline void wstyle::Window::Get::Menu(PTCHAR buffer) const { _tcscpy_s(buffer, _tcslen(owner->wc.lpszMenuName) * sizeof(TCHAR), owner->wc.lpszMenuName); }
inline DWORD wstyle::Window::Get::Style() const { return owner->style; }
inline _tstring wstyle::Window::Get::WndClassName() const { return owner->wc.lpszClassName; }
inline HBRUSH wstyle::Window::Get::BgBrush() const { return owner->wc.hbrBackground; }
inline wstyle::Window* wstyle::Window::Get::Parent() const { return owner->parent; }
inline HDC wstyle::Window::Get::HDC() const { return GetDC(owner->hWnd); }
inline HWND wstyle::Window::Get::hWnd() const { return owner->hWnd; }
inline bool wstyle::Window::Get::Visible() const { return owner->isVisible; }
inline bool wstyle::Window::Get::Enabled() const { return owner->isEnabled; }

inline wstyle::Window::Window() : hWnd(nullptr), parent(nullptr),
_nCmdShow(SW_SHOW), Set(this), Get(this), doubleBufferEnabled(true),
isVisible(true), isEnabled(true), isPainting(true) {
	className = TEXT("MyApp");
	title = TEXT("MyApp");
	TCHAR* buf = new TCHAR[4];
	_stprintf_s(buf, 4*sizeof(TCHAR), TEXT("%d"), number++);
	className += buf;
	Create(GetModuleHandle(NULL), title.c_str(), 800, 600, SW_SHOWNORMAL);
	delete[] buf;
};

inline wstyle::Window& wstyle::Window::operator = (const Window& window) {
	if (this == &window)
		return *this;
	Destroy();
	Clone(window);
	return *this;
};

inline void wstyle::Window::Destroy() {
	DestroyWindow(hWnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	parent = nullptr;
	const_cast<HWND&>(hWnd) = nullptr;
}

inline bool wstyle::Window::Create(HINSTANCE _hInstance, PCTCH _title, UINT _width, UINT _height,
	UINT nCmdShow, DWORD _style, Window* parent, PCTCH lpszMenuName) {
	style = _style;
	width = _width;
	this->parent = parent;
	this->style = style;
	wc.lpszMenuName = lpszMenuName;
	_nCmdShow = nCmdShow;
	title = _title;
	height = _height;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = _hInstance;
	wc.lpszMenuName = lpszMenuName;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = static_WndProc;
	wc.lpszClassName = className.c_str();

	if (!Register())
		return false;

	SetWindowLong(hWnd, GWLP_USERDATA, (long)this);


	return true;
}

inline bool wstyle::Window::Register() {
	if (!RegisterClassEx(&wc))
		return false;

	hWnd = CreateWindow(wc.lpszClassName, title.c_str(), style,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width, height, parent ? parent->Get.hWnd() : nullptr, LoadMenu(wc.hInstance, wc.lpszMenuName), wc.hInstance, nullptr);

	return (hWnd != INVALID_HANDLE_VALUE);
}

inline void wstyle::Window::Clone(const Window& w) {
	title = w.title;
	parent = w.parent;
	style = w.style;
	width = w.width;
	height = w.height;
	_nCmdShow = w._nCmdShow;
	wc.cbClsExtra = w.wc.cbClsExtra;
	wc.cbSize = w.wc.cbWndExtra;
	wc.cbWndExtra = w.wc.cbWndExtra;
	wc.hbrBackground = w.wc.hbrBackground;
	wc.hCursor = w.wc.hCursor;
	wc.hIcon = w.wc.hIcon;
	wc.hIconSm = w.wc.hIconSm;
	wc.hInstance = w.wc.hInstance;
	wc.lpfnWndProc = w.wc.lpfnWndProc;
	wc.lpszMenuName = w.wc.lpszMenuName;
	wc.style = w.wc.style;
	className = TEXT("MyApp");
	title = TEXT("MyApp");
	TCHAR* buf = new TCHAR[4];
	_stprintf_s(buf, 4 * sizeof(TCHAR), TEXT("%d"), number++);
	className += buf;
	delete[] buf;
	wc.lpszClassName = className.c_str();
	Register();
}

inline HDC wstyle::Window::StartPaint() {
	isPainting = true;
	if (doubleBufferEnabled)
		return paintBuffer.Open(hWnd, wc.hbrBackground);
	return paintBuffer.Open(hWnd, wc.hbrBackground, false);
}

inline HDC wstyle::Window::GetPaintDC() const {
	if (isPainting)
		return (paintBuffer.GetDC());
	else
		return nullptr;
}

inline void wstyle::Window::EndPaint() {
	paintBuffer.Close();
	isPainting = false;
}

inline void wstyle::Window::Run(bool newThread)
{
	UpdateWindow(hWnd);
	ShowWindow(hWnd, _nCmdShow);
	SendMessage(hWnd, WM_CREATE, 0, 0);

	if (newThread) {
		std::thread([]() {
			MSG msg{};
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			}).detach();
	}
	else {
		MSG msg{};
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

inline __declspec(dllexport) LRESULT __stdcall wstyle::Window::static_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* w = (Window*)GetWindowLong(hWnd, GWLP_USERDATA);

	if (!w)
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	return w->WindowProc(hWnd, uMsg, wParam, lParam);
}

inline __declspec(dllexport) __declspec(dllexport) LRESULT wstyle::Window::OnCreate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CREATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ACTIVATEAPP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnAfxFirst(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_AFXFIRST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnAfxLast(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_AFXLAST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnApp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_APP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnAskCBForMatName(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ASKCBFORMATNAME, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCancelJournal(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CANCELJOURNAL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCancelMode(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CANCELMODE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCaptureChanged(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CAPTURECHANGED, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnChangeCBChain(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHANGECBCHAIN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnChangeUIState(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHANGEUISTATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnChar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCharToItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHARTOITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnChildActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHILDACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnChildDActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CHILDACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnClear(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CLEAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCompacting(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_COMPACTING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCompareItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_COMPAREITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnContextMenu(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CONTEXTMENU, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCopy(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_COPY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCopyData(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_COPYDATA, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorBtn(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORBTN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorDlg(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORDLG, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorEdit(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLOREDIT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorListBox(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORLISTBOX, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorMsgBox(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORMSGBOX, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorScrollBar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORSCROLLBAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCtlColorStatic(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CTLCOLORSTATIC, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnCut(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CUT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDeadChar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DEADCHAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDeleteItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DELETEITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDestroyClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DESTROYCLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DEVICECHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDevModeChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DEVMODECHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DISPLAYCHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDrawClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DRAWCLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DRAWITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDropFiles(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_DROPFILES, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEnable(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ENABLE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEndSession(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ENDSESSION, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEnterIdle(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ENTERIDLE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEnterMenuLoop(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ENTERMENULOOP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ENTERSIZEMOVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ERASEBKGND, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnExitMenuLoop(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_EXITMENULOOP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_EXITSIZEMOVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnFontChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_FONTCHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetDlgCode(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETDLGCODE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETFONT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetHotkey(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETHOTKEY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetIcon(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETICON, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETMINMAXINFO, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetObject(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETOBJECT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetText(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETTEXT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnGetTextLength(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_GETTEXTLENGTH, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHandHeldFirst(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HANDHELDFIRST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHandHeldLast(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HANDHELDLAST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHelp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HELP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHotkey(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HOTKEY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHScroll(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HSCROLL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnHScrollClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_HSCROLLCLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_ICONERASEBKGND, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_INITDIALOG, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnInitMenu(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_INITMENU, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnInitMenuPopup(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_INITMENUPOPUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnInputLangChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_INPUTLANGCHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnInputLangChangeRequest(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_INPUTLANGCHANGEREQUEST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_KEYDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnKeyLast(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_KEYLAST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_KEYUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_KILLFOCUS, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_LBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_LBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiCascade(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDICASCADE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiCreate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDICREATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiDestroy(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIDESTROY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiGetActive(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIGETACTIVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiIconArrange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIICONARRANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiMaximize(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIMAXIMIZE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiNext(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDINEXT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiRefreshMenu(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIREFRESHMENU, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiRestore(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDIRESTORE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiSetMenu(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDISETMENU, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMdiTile(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MDITILE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMeasureItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MEASUREITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuChar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENUCHAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuCommand(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENUCOMMAND, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuDrag(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENUDRAG, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuGetObject(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENUGETOBJECT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENURBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMenuSelect(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MENUSELECT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSEACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSEHOVER, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSELEAVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSEMOVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseWheel(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSEWHEEL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMouseHWheel(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOUSEHWHEEL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnMoving(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MOVING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCActivate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCACTIVATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCCalcSize(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCCALCSIZE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCCreate(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCCREATE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCDestroy(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCDESTROY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCHitTest(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCLBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCLButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCLBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCLBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCXButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCXBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCXButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCXBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCXButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCXBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMouseHover(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCMOUSEHOVER, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCMOUSELEAVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMouseMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCMOUSEMOVE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCPaint(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCPAINT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNextDlgCtl(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NEXTDLGCTL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNextMenu(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NEXTMENU, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNotify(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NOTIFY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT  wstyle::Window::OnNotifyFormat(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NOTIFYFORMAT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNull(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NULL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaintClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PAINTCLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaintIcon(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PAINTICON, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_MBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCMButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCMBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCRBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCRBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnNCRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_NCRBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaint(WPARAM wParam, LPARAM lParam)
{

	return DefWindowProc(hWnd, WM_PAINT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaletteChanged(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PALETTECHANGED, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaletteIsChanging(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PALETTEISCHANGING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnParentNotify(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PARENTNOTIFY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPaste(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PASTE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPenWinFirst(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PENWINFIRST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPenWinLast(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PENWINLAST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPower(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_POWER, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPowerBroadcast(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_POWERBROADCAST, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPrint(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PRINT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnPrintClient(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_PRINTCLIENT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQueryDragIcon(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUERYDRAGICON, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQueryEndSession(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUERYENDSESSION, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQueryNewPalette(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUERYNEWPALETTE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQueryOpen(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUERYOPEN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQueueSync(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUEUESYNC, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnQuit(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_QUIT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnRButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_RBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnRButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_RBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnRButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_RBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnRenderAllFormats(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_RENDERALLFORMATS, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnRenderFormat(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_RENDERFORMAT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETCURSOR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETFOCUS, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETFONT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetHotkey(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETHOTKEY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetIcon(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETICON, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetRedraw(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETREDRAW, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSetText(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETTEXT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SETTINGCHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnShowWindow(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SHOWWINDOW, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSize(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SIZE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSizeClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SIZECLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSizing(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SIZING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSpoolerStatus(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SPOOLERSTATUS, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnStyleChanged(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_STYLECHANGED, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnStyleChanging(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_STYLECHANGING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSyncPaint(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYNCPAINT, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysChar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSCHAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysColorChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSCOLORCHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSCOMMAND, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysDeadChar(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSDEADCHAR, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSKEYDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_SYSKEYUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnTCard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_TCARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnTimeChange(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_TIMECHANGE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_TIMER, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnUndo(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_UNDO, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnUNInitMenuPopup(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_UNINITMENUPOPUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnUser(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_USER, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnUserChanged(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_USERCHANGED, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnVKeyToItem(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_VKEYTOITEM, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnVScroll(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_VSCROLL, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnVScrollClipBoard(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_VSCROLLCLIPBOARD, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnWindowPosChanged(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_WINDOWPOSCHANGED, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_WINDOWPOSCHANGING, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnXButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_XBUTTONDBLCLK, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnXButtonDown(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_XBUTTONDOWN, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnXButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_XBUTTONUP, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnClose(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, WM_CLOSE, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	if (!parent)
		PostQuitMessage(EXIT_SUCCESS);
	return DefWindowProc(hWnd, WM_DESTROY, wParam, lParam);
}

inline __declspec(dllexport) LRESULT wstyle::Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return OnCreate(wParam, lParam);
	case WM_ACTIVATE:
		return OnActivate(wParam, lParam);
	case WM_ACTIVATEAPP:
		return OnActivateApp(wParam, lParam);
	case WM_AFXFIRST:
		return OnAfxFirst(wParam, lParam);
	case WM_AFXLAST:
		return OnAfxLast(wParam, lParam);
	case WM_APP:
		return OnApp(wParam, lParam);
	case WM_ASKCBFORMATNAME:
		return OnAskCBForMatName(wParam, lParam);
	case WM_CANCELJOURNAL:
		return OnCancelJournal(wParam, lParam);
	case WM_CANCELMODE:
		return OnCancelMode(wParam, lParam);
	case WM_CAPTURECHANGED:
		return OnCaptureChanged(wParam, lParam);
	case WM_CHANGECBCHAIN:
		return OnChangeCBChain(wParam, lParam);
	case WM_CHANGEUISTATE:
		return OnChangeUIState(wParam, lParam);
	case WM_CHAR:
		return OnChar(wParam, lParam);
	case WM_CHARTOITEM:
		return OnCharToItem(wParam, lParam);
	case WM_CHILDACTIVATE:
		return OnChildActivate(wParam, lParam);
	case WM_CLEAR:
		return OnClear(wParam, lParam);
	case WM_CLOSE:
		return OnClose(wParam, lParam);
	case WM_COMPACTING:
		return OnCompacting(wParam, lParam);
	case WM_COMPAREITEM:
		return OnCompareItem(wParam, lParam);
	case WM_CONTEXTMENU:
		return OnContextMenu(wParam, lParam);
	case WM_COPY:
		return OnCopy(wParam, lParam);
	case WM_COPYDATA:
		return OnCopyData(wParam, lParam);
	case WM_CTLCOLORBTN:
		return OnCtlColorBtn(wParam, lParam);
	case WM_CTLCOLORDLG:
		return OnCtlColorDlg(wParam, lParam);
	case WM_CTLCOLOREDIT:
		return OnCtlColorEdit(wParam, lParam);
	case WM_CTLCOLORLISTBOX:
		return OnCtlColorListBox(wParam, lParam);
	case WM_CTLCOLORMSGBOX:
		return OnCtlColorMsgBox(wParam, lParam);
	case WM_CTLCOLORSCROLLBAR:
		return OnCtlColorScrollBar(wParam, lParam);
	case WM_CTLCOLORSTATIC:
		return OnCtlColorStatic(wParam, lParam);
	case WM_CUT:
		return OnCut(wParam, lParam);
	case WM_DEADCHAR:
		return OnDeadChar(wParam, lParam);
	case WM_DELETEITEM:
		return OnDeleteItem(wParam, lParam);
	case WM_DESTROY:
		return OnDestroy(wParam, lParam);
	case WM_DESTROYCLIPBOARD:
		return OnDestroyClipBoard(wParam, lParam);
	case WM_DEVICECHANGE:
		return OnDeviceChange(wParam, lParam);
	case WM_DEVMODECHANGE:
		return OnDevModeChange(wParam, lParam);
	case WM_DISPLAYCHANGE:
		return OnDisplayChange(wParam, lParam);
	case WM_DRAWCLIPBOARD:
		return OnDrawClipBoard(wParam, lParam);
	case WM_DRAWITEM:
		return OnDrawItem(wParam, lParam);
	case WM_DROPFILES:
		return OnDropFiles(wParam, lParam);
	case WM_ENABLE:
		return OnEnable(wParam, lParam);
	case WM_ENDSESSION:
		return OnEndSession(wParam, lParam);
	case WM_ENTERIDLE:
		return OnEnterIdle(wParam, lParam);
	case WM_ENTERMENULOOP:
		return OnEnterMenuLoop(wParam, lParam);
	case WM_ENTERSIZEMOVE:
		return OnEnterSizeMove(wParam, lParam);
	case WM_ERASEBKGND:
		return OnEraseBkgnd(wParam, lParam);
	case WM_EXITMENULOOP:
		return OnExitMenuLoop(wParam, lParam);
	case WM_EXITSIZEMOVE:
		return OnExitSizeMove(wParam, lParam);
	case WM_FONTCHANGE:
		return OnFontChange(wParam, lParam);
	case WM_GETDLGCODE:
		return OnGetDlgCode(wParam, lParam);
	case WM_GETFONT:
		return OnGetFont(wParam, lParam);
	case WM_GETHOTKEY:
		return OnGetHotkey(wParam, lParam);
	case WM_GETICON:
		return OnGetIcon(wParam, lParam);
	case WM_GETMINMAXINFO:
		return OnGetMinMaxInfo(wParam, lParam);
	case WM_GETOBJECT:
		return OnGetObject(wParam, lParam);
	case WM_GETTEXT:
		return OnGetText(wParam, lParam);
	case WM_GETTEXTLENGTH:
		return OnGetTextLength(wParam, lParam);
	case WM_HANDHELDFIRST:
		return OnHandHeldFirst(wParam, lParam);
	case WM_HANDHELDLAST:
		return OnHandHeldLast(wParam, lParam);
	case WM_HELP:
		return OnHelp(wParam, lParam);
	case WM_HOTKEY:
		return OnHotkey(wParam, lParam);
	case WM_HSCROLL:
		return OnHScroll(wParam, lParam);
	case WM_HSCROLLCLIPBOARD:
		return OnHScrollClipBoard(wParam, lParam);
	case WM_ICONERASEBKGND:
		return OnIconEraseBkgnd(wParam, lParam);
	case WM_INITDIALOG:
		return OnInitDialog(wParam, lParam);
	case WM_INITMENU:
		return OnInitMenu(wParam, lParam);
	case WM_INITMENUPOPUP:
		return OnInitMenuPopup(wParam, lParam);
	case WM_INPUTLANGCHANGE:
		return OnInputLangChange(wParam, lParam);
	case WM_INPUTLANGCHANGEREQUEST:
		return OnInputLangChangeRequest(wParam, lParam);
	case WM_KEYDOWN:
		return OnKeyDown(wParam, lParam);
	case WM_KEYLAST:
		return OnKeyLast(wParam, lParam);
	case WM_KEYUP:
		return OnKeyUp(wParam, lParam);
	case WM_KILLFOCUS:
		return OnKillFocus(wParam, lParam);
	case WM_LBUTTONDBLCLK:
		return OnLButtonDblClk(wParam, lParam);
	case WM_LBUTTONDOWN:
		return OnLButtonDown(wParam, lParam);
	case WM_LBUTTONUP:
		return OnLButtonUp(wParam, lParam);
	case WM_MBUTTONDBLCLK:
		return OnMButtonDblClk(wParam, lParam);
	case WM_MBUTTONDOWN:
		return OnMButtonDown(wParam, lParam);
	case WM_MBUTTONUP:
		return OnMButtonUp(wParam, lParam);
	case WM_MDIACTIVATE:
		return OnMdiActivate(wParam, lParam);
	case WM_MDICASCADE:
		return OnMdiCascade(wParam, lParam);
	case WM_MDICREATE:
		return OnMdiCreate(wParam, lParam);
	case WM_MDIDESTROY:
		return OnMdiDestroy(wParam, lParam);
	case WM_MDIGETACTIVE:
		return OnMdiGetActive(wParam, lParam);
	case WM_MDIICONARRANGE:
		return OnMdiIconArrange(wParam, lParam);
	case WM_MDIMAXIMIZE:
		return OnMdiMaximize(wParam, lParam);
	case WM_MDINEXT:
		return OnMdiNext(wParam, lParam);
	case WM_MDIREFRESHMENU:
		return OnMdiRefreshMenu(wParam, lParam);
	case WM_MDIRESTORE:
		return OnMdiRestore(wParam, lParam);
	case WM_MDISETMENU:
		return OnMdiSetMenu(wParam, lParam);
	case WM_MDITILE:
		return OnMdiTile(wParam, lParam);
	case WM_MEASUREITEM:
		return OnMeasureItem(wParam, lParam);
	case WM_MENUCHAR:
		return OnMenuChar(wParam, lParam);
	case WM_MENUCOMMAND:
		return OnMenuCommand(wParam, lParam);
	case WM_MENUDRAG:
		return OnMenuDrag(wParam, lParam);
	case WM_MENUGETOBJECT:
		return OnMenuGetObject(wParam, lParam);
	case WM_MENURBUTTONUP:
		return OnMenuRButtonUp(wParam, lParam);
	case WM_MENUSELECT:
		return OnMenuSelect(wParam, lParam);
	case WM_MOUSEACTIVATE:
		return OnMouseActivate(wParam, lParam);
	case WM_MOUSEHOVER:
		return OnMouseHover(wParam, lParam);
	case WM_MOUSELEAVE:
		return OnMouseLeave(wParam, lParam);
	case WM_MOUSEMOVE:
		return OnMouseMove(wParam, lParam);
	case WM_MOUSEWHEEL:
		return OnMouseWheel(wParam, lParam);
	case WM_MOUSEHWHEEL:
		return OnMouseHWheel(wParam, lParam);
	case WM_MOVE:
		return OnMove(wParam, lParam);
	case WM_MOVING:
		return OnMoving(wParam, lParam);
	case WM_NCACTIVATE:
		return OnNCActivate(wParam, lParam);
	case WM_NCCALCSIZE:
		return OnNCCalcSize(wParam, lParam);
	case WM_NCCREATE:
		return OnNCCreate(wParam, lParam);
	case WM_NCDESTROY:
		return OnNCDestroy(wParam, lParam);
	case WM_NCHITTEST:
		return OnNCHitTest(wParam, lParam);
	case WM_NCLBUTTONDBLCLK:
		return OnNCLButtonDblClk(wParam, lParam);
	case WM_NCLBUTTONDOWN:
		return OnNCLButtonDown(wParam, lParam);
	case WM_NCLBUTTONUP:
		return OnNCLButtonUp(wParam, lParam);
	case WM_NCMBUTTONDBLCLK:
		return OnNCMButtonDblClk(wParam, lParam);
	case WM_NCMBUTTONDOWN:
		return OnNCMButtonDown(wParam, lParam);
	case WM_NCMBUTTONUP:
		return OnNCMButtonUp(wParam, lParam);
	case WM_NCMOUSEHOVER:
		return OnNCMouseHover(wParam, lParam);
	case WM_NCMOUSELEAVE:
		return OnNCMouseLeave(wParam, lParam);
	case WM_NCMOUSEMOVE:
		return OnNCMouseMove(wParam, lParam);
	case WM_NCPAINT:
		return OnNCPaint(wParam, lParam);
	case WM_NCRBUTTONDBLCLK:
		return OnNCRButtonDblClk(wParam, lParam);
	case WM_NCRBUTTONDOWN:
		return OnNCRButtonDown(wParam, lParam);
	case WM_NCRBUTTONUP:
		return OnNCRButtonUp(wParam, lParam);
	case WM_NCXBUTTONDBLCLK:
		return OnNCXButtonDblClk(wParam, lParam);
	case WM_NCXBUTTONDOWN:
		return OnNCXButtonDown(wParam, lParam);
	case WM_NCXBUTTONUP:
		return OnNCXButtonUp(wParam, lParam);
	case WM_NEXTDLGCTL:
		return OnNextDlgCtl(wParam, lParam);
	case WM_NEXTMENU:
		return OnNextMenu(wParam, lParam);
	case WM_NOTIFY:
		return OnNotify(wParam, lParam);
	case WM_NOTIFYFORMAT:
		return OnNotifyFormat(wParam, lParam);
	case WM_NULL:
		return OnNull(wParam, lParam);
	case WM_PAINTCLIPBOARD:
		return OnPaintClipBoard(wParam, lParam);
	case WM_PAINTICON:
		return OnPaintIcon(wParam, lParam);
	case WM_PALETTECHANGED:
		return OnPaletteChanged(wParam, lParam);
	case WM_PALETTEISCHANGING:
		return OnPaletteIsChanging(wParam, lParam);
	case WM_PARENTNOTIFY:
		return OnParentNotify(wParam, lParam);
	case WM_PASTE:
		return OnPaste(wParam, lParam);
	case WM_PENWINFIRST:
		return OnPenWinFirst(wParam, lParam);
	case WM_PENWINLAST:
		return OnPenWinLast(wParam, lParam);
	case WM_POWER:
		return OnPower(wParam, lParam);
	case WM_POWERBROADCAST:
		return OnPowerBroadcast(wParam, lParam);
	case WM_PRINT:
		return OnPrint(wParam, lParam);
	case WM_PRINTCLIENT:
		return OnPrintClient(wParam, lParam);
	case WM_QUERYDRAGICON:
		return OnQueryDragIcon(wParam, lParam);
	case WM_QUERYENDSESSION:
		return OnQueryEndSession(wParam, lParam);
	case WM_QUERYNEWPALETTE:
		return OnQueryNewPalette(wParam, lParam);
	case WM_QUERYOPEN:
		return OnQueryOpen(wParam, lParam);
	case WM_QUEUESYNC:
		return OnQueueSync(wParam, lParam);
	case WM_QUIT:
		return OnQuit(wParam, lParam);
	case WM_RBUTTONDBLCLK:
		return OnRButtonDblClk(wParam, lParam);
	case WM_RBUTTONDOWN:
		return OnRButtonDown(wParam, lParam);
	case WM_RBUTTONUP:
		return OnRButtonUp(wParam, lParam);
	case WM_RENDERALLFORMATS:
		return OnRenderAllFormats(wParam, lParam);
	case WM_RENDERFORMAT:
		return OnRenderFormat(wParam, lParam);
	case WM_SETCURSOR:
		return OnSetCursor(wParam, lParam);
	case WM_SETFOCUS:
		return OnSetFocus(wParam, lParam);
	case WM_SETFONT:
		return OnSetFont(wParam, lParam);
	case WM_SETHOTKEY:
		return OnSetHotkey(wParam, lParam);
	case WM_SETICON:
		return OnSetIcon(wParam, lParam);
	case WM_SETREDRAW:
		return OnSetRedraw(wParam, lParam);
	case WM_SETTEXT:
		return OnSetText(wParam, lParam);
	case WM_SETTINGCHANGE:
		return OnSettingChange(wParam, lParam);
	case WM_SHOWWINDOW:
		return OnShowWindow(wParam, lParam);
	case WM_SIZE:
		return OnSize(wParam, lParam);
	case WM_SIZECLIPBOARD:
		return OnSizeClipBoard(wParam, lParam);
	case WM_SIZING:
		return OnSizing(wParam, lParam);
	case WM_SPOOLERSTATUS:
		return OnSpoolerStatus(wParam, lParam);
	case WM_STYLECHANGED:
		return OnStyleChanged(wParam, lParam);
	case WM_STYLECHANGING:
		return OnStyleChanging(wParam, lParam);
	case WM_SYNCPAINT:
		return OnSyncPaint(wParam, lParam);
	case WM_SYSCOLORCHANGE:
		return OnSysColorChange(wParam, lParam);
	case WM_SYSCOMMAND:
		return OnSysCommand(wParam, lParam);
	case WM_SYSDEADCHAR:
		return OnSysDeadChar(wParam, lParam);
	case WM_SYSKEYDOWN:
		return OnSysKeyDown(wParam, lParam);
	case WM_SYSKEYUP:
		return OnSysKeyUp(wParam, lParam);
	case WM_TCARD:
		return OnTCard(wParam, lParam);
	case WM_TIMECHANGE:
		return OnTimeChange(wParam, lParam);
	case WM_TIMER:
		return OnTimer(wParam, lParam);
	case WM_UNDO:
		return OnUndo(wParam, lParam);
	case WM_UNINITMENUPOPUP:
		return OnUNInitMenuPopup(wParam, lParam);
	case WM_USER:
		return OnUser(wParam, lParam);
	case WM_USERCHANGED:
		return OnUserChanged(wParam, lParam);
	case WM_VKEYTOITEM:
		return OnVKeyToItem(wParam, lParam);
	case WM_VSCROLL:
		return OnVScroll(wParam, lParam);
	case WM_VSCROLLCLIPBOARD:
		return OnVScrollClipBoard(wParam, lParam);
	case WM_WINDOWPOSCHANGED:
		return OnWindowPosChanged(wParam, lParam);
	case WM_WINDOWPOSCHANGING:
		return OnWindowPosChanging(wParam, lParam);
	case WM_XBUTTONDBLCLK:
		return OnXButtonDblClk(wParam, lParam);
	case WM_XBUTTONDOWN:
		return OnXButtonDown(wParam, lParam);
	case WM_XBUTTONUP:
		return OnXButtonUp(wParam, lParam);
	case WM_PAINT: {
		StartPaint();
		LRESULT res = OnPaint(wParam, lParam);
		EndPaint();
		return res;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
