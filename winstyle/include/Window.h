//
// Window.h
//
//      Copyright (c) Alexandr Zhirkevich. All rights reserved.
//		E-mail: mailto:sasha.zhirkevich@yandex.ru;
//		Vk: https://vk.com/id175640630;
//		Telegram: @alexzhirkevich.
//
// The C++ WinApi <winstyle.h> library.
//
// namespace wstyle
//

#ifndef _WINSTYLE_WINDOW_
#define _WINSTYLE_WINDOW_

#ifdef _MSC_VER
#pragma once
#if _MSC_VER >= 1200
#pragma warning(push)
#endif // _MSC_VER >= 1200
#endif // _MSC_VER

#pragma warning(disable:4996)
#pragma warning(disable:4005)
#pragma warning(disable:26444)
#pragma warning(disable:26495)
#pragma warning(disable:493)

#include "Init.h"
#include "ChildClass.h"
#include "Painter.h"

namespace wstyle {

	class Window
	{
	private:
		static __declspec(dllimport) LRESULT WINAPI static_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		__declspec(dllimport) LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static UINT number;
	protected:
		class Set : public ChildClass<Window> {
			using ChildClass<Window>::ChildClass;
		public:
			void Icon(HICON hIcon) const;
			void Cursor(HCURSOR hCursor) const;
			void Menu(PCTCH lpszMenuName) const;
			void Style(DWORD style) const;
			void Title(PCTCH title) const;
			void Parent(Window* parent) const;
			void Visible(bool isVisible) const;
			void Enable(bool isActive) const;
			void DoubleBufferring(bool isBuffered) const;
		};
		class Get : public ChildClass<Window> {
			using ChildClass<Window>::ChildClass;
		public:
			int Width() const;
			int Height() const;
			RECT ClientRect() const;
			HICON Icon() const;
			HCURSOR Cursor() const;
			_tstring Title() const;
			void Menu(PTCHAR buffer) const;
			DWORD Style() const;
			_tstring WndClassName() const;
			HBRUSH BgBrush() const;
			Window* Parent() const;
			HDC HDC() const;
			HWND hWnd() const;
			bool Visible() const;
			bool Enabled() const;
		};

	protected:

		bool doubleBufferEnabled, isVisible, isEnabled, isPainting;
		Window* parent;
		DWORD style;
		_tstring title, className;
		UINT width, height;
		INT _nCmdShow;
		Painter paintBuffer;
		HWND hWnd;
		WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
		bool Register();
		void Clone(const Window&);
		bool Create(HINSTANCE hInstance, PCTCH lpszTitle, UINT width, UINT height,
			UINT nCmdShow, DWORD dwStyle = WS_OVERLAPPEDWINDOW, Window* parent = nullptr, PCTCH lpszMenuName = nullptr);
		HDC StartPaint();
		void EndPaint();

	public:
		const Get Get;
		const Set Set;
		Window();
		Window(const Window& window) : Window() { Clone(window); };
		Window& operator = (const Window& window);
		void Destroy();
		void Run(bool newThread = false);
		void SetFocus() { ::SetFocus(hWnd); }
		HDC GetPaintDC() const;
		~Window() { Destroy(); }

	protected:
		virtual __declspec(dllimport) LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnAfxFirst(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnAfxLast(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnApp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnAskCBForMatName(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCancelJournal(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCancelMode(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCaptureChanged(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnChangeCBChain(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnChangeUIState(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnChar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCharToItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnChildActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnChildDActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnClear(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCompacting(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCompareItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnContextMenu(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCopyData(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorBtn(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorDlg(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorEdit(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorMsgBox(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorScrollBar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCtlColorStatic(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnCut(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDeadChar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDeleteItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDestroyClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDevModeChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDrawClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEnable(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEndSession(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEnterIdle(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEnterMenuLoop(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnExitMenuLoop(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnFontChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetDlgCode(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetHotkey(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetIcon(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetObject(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHandHeldFirst(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHandHeldLast(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHotkey(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHScroll(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnHScrollClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnInitMenu(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnInitMenuPopup(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnInputLangChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnInputLangChangeRequest(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnKeyLast(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiCascade(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiCreate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiDestroy(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiGetActive(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiIconArrange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiMaximize(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiNext(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiRefreshMenu(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiRestore(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiSetMenu(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMdiTile(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMeasureItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuChar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuCommand(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuDrag(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuGetObject(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuRButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMenuSelect(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMouseHWheel(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMove(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnMoving(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCActivate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCCalcSize(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCCreate(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCDestroy(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCHitTest(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCLButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCLButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCLButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCRButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCRButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCRButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCXButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCXButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCXButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMouseHover(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMouseLeave(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCMouseMove(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNCPaint(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNextDlgCtl(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNextMenu(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNotify(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNotifyFormat(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnNull(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaintClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaintIcon(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaletteChanged(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaletteIsChanging(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnParentNotify(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPenWinFirst(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPenWinLast(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPower(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPowerBroadcast(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPrint(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnPrintClient(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQueryDragIcon(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQueryNewPalette(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQueryOpen(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQueueSync(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnQuit(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnRButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnRenderAllFormats(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnRenderFormat(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetFocus(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetHotkey(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetIcon(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetRedraw(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnShowWindow(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSize(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSizeClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSpoolerStatus(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnStyleChanged(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnStyleChanging(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSyncPaint(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysChar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysColorChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysDeadChar(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnSysKeyUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnTCard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnTimeChange(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnUndo(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnUNInitMenuPopup(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnUser(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnUserChanged(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnVKeyToItem(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnVScroll(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnVScrollClipBoard(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnXButtonDblClk(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnXButtonDown(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnXButtonUp(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnClose(WPARAM wParam, LPARAM lParam);
		virtual __declspec(dllimport) LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_WINDOW_