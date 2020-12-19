//
// Window.h
//
//      By Alexandr Zhirkevich.
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
#endif // _MSC_VER

#include "Init.h"
#include "ChildClass.h"
#include "Painter.h"

namespace wstyle {

	class MenuBar;
	class Control;
	class Menu;

	class Window
	{
		friend class Control;
		friend class MenuBar;
		friend class Menu;

	private:
		static LRESULT WINAPI static_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static UINT number;
	protected:
		class Set : public ChildClass<Window> {
			using ChildClass<Window>::ChildClass;
		public:
			void Icon(HICON hIcon) const;
			void Cursor(HCURSOR hCursor) const;
			void MenuBar(wstyle::MenuBar* menuBar) const;
			void Style(DWORD style) const;
			void Title(PCTCH title) const;
			void Parent(Window* parent) const;
			void SetVisible(bool isVisible) const;
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
			void MenuBar(PTCHAR buffer) const;
			DWORD Style() const;
			_tstring WndClassName() const;
			HBRUSH BgBrush() const;
			Window* Parent() const;
			HDC HDC() const;
			HWND hWnd() const;
			bool SetVisible() const;
			bool Enabled() const;
		};

	protected:

		std::vector<Control*> controls;

	private:
		
		bool doubleBufferEnabled, isVisible, isEnabled, isPainting;
		Window* parent;
		DWORD style;
		MenuBar* menuBar;
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
		bool AddControl(Control* c);
		bool RemoveControl(Control* c);
	public:
		const Get Get;
		const Set Set;
		Window();
		Window(const Window& window);
		Window& operator = (const Window& window);
		void Destroy();
		void Run(bool newThread = false);
		void SetFocus();
		void Update();
		HDC GetPaintDC() const;
		~Window();

	public:
		 virtual LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnAfxFirst(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnAfxLast(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnApp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnAskCBForMatName(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCancelJournal(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCancelMode(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCaptureChanged(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnChangeCBChain(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnChangeUIState(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnChar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCharToItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnChildActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnChildDActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnClear(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCompacting(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCompareItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnContextMenu(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCopyData(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorBtn(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorDlg(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorEdit(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorMsgBox(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorScrollBar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCtlColorStatic(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnCut(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDeadChar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDeleteItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDestroyClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDevModeChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDrawClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEnable(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEndSession(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEnterIdle(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEnterMenuLoop(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnExitMenuLoop(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnFontChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetDlgCode(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetHotkey(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetIcon(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetObject(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHandHeldFirst(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHandHeldLast(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHotkey(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHScroll(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnHScrollClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnIconEraseBkgnd(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnInitMenu(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnInitMenuPopup(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnInputLangChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnInputLangChangeRequest(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnKeyLast(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnKeyUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiCascade(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiCreate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiDestroy(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiGetActive(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiIconArrange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiMaximize(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiNext(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiRefreshMenu(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiRestore(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiSetMenu(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMdiTile(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMeasureItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuChar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuCommand(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuDrag(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuGetObject(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuRButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMenuSelect(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseWheel(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMouseHWheel(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMove(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnMoving(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCActivate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCCalcSize(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCCreate(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCDestroy(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCHitTest(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCLButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCLButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCLButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCRButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCRButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCRButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCXButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCXButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCXButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMouseHover(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMouseLeave(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCMouseMove(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNCPaint(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNextDlgCtl(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNextMenu(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNotify(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNotifyFormat(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnNull(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaintClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaintIcon(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaletteChanged(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaletteIsChanging(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnParentNotify(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPenWinFirst(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPenWinLast(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPower(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPowerBroadcast(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPrint(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnPrintClient(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQueryDragIcon(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQueryEndSession(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQueryNewPalette(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQueryOpen(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQueueSync(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnQuit(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnRButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnRButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnRenderAllFormats(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnRenderFormat(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetFocus(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetHotkey(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetIcon(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetRedraw(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnShowWindow(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSizeClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSpoolerStatus(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnStyleChanged(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnStyleChanging(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSyncPaint(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysChar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysColorChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysCommand(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysDeadChar(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysKeyDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnSysKeyUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnTCard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnTimeChange(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnUndo(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnUNInitMenuPopup(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnUser(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnUserChanged(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnVKeyToItem(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnVScroll(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnVScrollClipBoard(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnWindowPosChanged(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnXButtonDblClk(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnXButtonDown(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnXButtonUp(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnClose(WPARAM wParam, LPARAM lParam);
		 virtual LRESULT OnDestroy(WPARAM wParam, LPARAM lParam);
	};

}

#endif // _WINSTYLE_WINDOW_