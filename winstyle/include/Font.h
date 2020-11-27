//
// Font.h
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

#ifndef _WINSTYLE_FONT_
#define _WINSTYLE_FONT_

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
#include "Color.h"

namespace wstyle {

	class Font /*Font class for WINAPI*/
	{
	protected:
		class Set : public ChildClass<Font> {
			using ChildClass<Font>::ChildClass;
		public:
			void Color(COLORREF _color);
			void Color(int CLR_CONSTANT);
			void Height(LONG Height);
			void Width(LONG Width);
			void Weight(LONG Weight);
			void FaceName(PCTCH FaceName);
			void Icalic(bool Italic);
			void UnderLine(bool UnderLine);
			void StrikeOut(bool StrikeOut);
			void Escapement(LONG Escapement);
			void Orientation(LONG Orientation);
			void CharSet(BYTE CharSet);
			void OutPrecision(BYTE OutPrecision);
			void ClipPrecision(BYTE ClipPrecision);
			void Quality(BYTE Quality);
			void PitchAndFamily(BYTE PitchAndFamily);
		};

		class Get : public ChildClass<Font> {
			using ChildClass<Font>::ChildClass;
		public:
			HFONT Hfont() const;
			LONG Height() const;
			LONG Width() const;
			LONG Weight() const;
			_tstring FaceName() const;
			void LogFont(LPLOGFONT logfont) const;
			LONG Escapement() const;
			LONG Orientation() const;
			BYTE CharSer() const;
			BYTE OutPrecision() const;
			BYTE ClipPrecision() const;
			BYTE Quality() const;
			BYTE PitchAndFamily() const;
		};
		LOGFONT lfont;
		HFONT hfont;
		COLORREF color;
		void Restore() { DeleteObject(hfont); hfont = CreateFontIndirect(&lfont); }
		void Default(); /* Set font to default values */
		void Erase();
	public:
		Set Set;
		Get Get;
		Font() : color(RGB(0, 0, 0)), hfont(nullptr), Set(this), Get(this) { Default(); Restore(); }
		Font(LOGFONT lf) :Font() { Create(lf); }
		Font(LONG Height, LONG Width, PCTCH FaceName, COLORREF Color = RGB(255, 255, 255), LONG Weight = 400, bool Italic = false,
			bool UnderLine = false, bool StrikeOut = false, LONG Escapement = 0, LONG Orientation = 0, BYTE CharSet = DEFAULT_CHARSET,
			BYTE OutPrecision = 0, BYTE ClipPrecision = 0, BYTE Quality = 0, BYTE PitchAndFamily = 0);
		Font(const Font& f) :Font() { Create(f.lfont); }
		Font& operator =(const Font& f);
		void Create(LONG Height, LONG Width, PCTCH FaceName, COLORREF Color = RGB(255, 255, 255), LONG Weight = 400, bool Italic = false,
			bool UnderLine = false, bool StrikeOut = false, LONG Escapement = 0, LONG Orientation = 0, BYTE CharSet = DEFAULT_CHARSET,
			BYTE OutPrecision = 0, BYTE ClipPrecision = 0, BYTE Quality = 0, BYTE PitchAndFamily = 0);
		void Create(LOGFONT lf);
		bool IsItalic() const { return lfont.lfItalic; }
		bool IsUnderLine() const { return lfont.lfUnderline; }
		bool IsStrikeOut() const { return lfont.lfStrikeOut; }
		HFONT SetOnDC(HDC hdc) const { SetTextColor(hdc, color); return SelectFont(hdc, hfont); } /* Set font object on hdc (Without returning PrevColor)*/
		HFONT SetOnDC(HDC hdc, COLORREF PrevColor) const {
			PrevColor = SetTextColor(hdc, color); return SelectFont(hdc, hfont);
		} /* Set font object on hdc (With returning PrevColor)*/
		virtual ~Font() { Erase(); }
	};

}

#ifdef _MSC_VER

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif //_MSC_VER >= 1200

#endif //_MSC_VER

#endif // _WINSTYLE_FONR_