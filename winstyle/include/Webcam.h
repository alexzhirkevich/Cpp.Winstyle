//
// Webcam.h
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

#ifndef _WINSTYLE_WEBCAM_
#define _WINSTYLE_WEBCAM_

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

namespace wstyle {

	class Webcam {
	protected:
		class Dialog {
		protected:
			Webcam* owner;
		public:
			Dialog() :owner(nullptr) {};
			Dialog(Webcam* _owner) :Dialog() { owner = _owner; }
			bool VideoSource();
			bool VideoFormat();
			bool VideoDisplay();
			~Dialog() {};
		};
		class Overlay {
		protected:
			Webcam* owner;
		public:
			Overlay() :owner(nullptr) {};
			Overlay(Webcam* _owner) : Overlay() { owner = _owner; }
			void Enable();
			void Disable();
		};
		class Settings {
			Webcam* owner;
		public:
			Settings() :owner(nullptr) {};
			Settings(Webcam* _owner) : Settings() { owner = _owner; }
			void SetBounds(int x, int y, int width, int height);
			/* Changes webcam resolution. Returns false, if resolution isn't supported */
			bool SetResolution(int camResolutionWidth, int camResolutionHeight);
			void SetRefreshRate(UINT rPerSec);
			/* Changes window title for WS_OVERLAPPED... styles */
			bool SetWindowName(PCTCH title);
		};
		class State {
		protected:
			Webcam* owner;
		public:
			State() :owner(nullptr) {};
			State(Webcam* _owner) : State() { owner = _owner; }
			void Show();
			void Hide();
		};
		HWND			hFatherWnd;
		CAPDRIVERCAPS	CapDrvCaps;
		CAPSTATUS		CapStatus;
		CAPTUREPARMS	CaptureParams;
		BITMAPINFO		s;
		POINT			pos;
		int				wndWidth;
		int				wndHeight;
		PTCHAR			wndName;
	public:
		Dialog			Dialog;
		Overlay			Overlay;
		Settings		Settings;
		State		State;
		const HWND		hWnd;
		Webcam();
		Webcam(HWND hWndOwner, int x, int y, int Width, int Height, int camResolutionWidth = 0, int camResolutionHeight = 0,
			int camWindowStyle = WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN) :Webcam() {
			Create(hWndOwner, x, y, Width, Height, camResolutionWidth, camResolutionHeight, camWindowStyle);
		}
		void Create(HWND hWndOwner, int x, int y, int Width, int Height, int camResolutionWidth = 0, int camResolutionHeight = 0,
			int camWindowStyle = WS_VISIBLE | WS_BORDER | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		POINT GetLocation() const { return pos; }
		bool MakePhoto(PCTCH fileName);
		void Delete();
		~Webcam() { Delete(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_WEBCAM_