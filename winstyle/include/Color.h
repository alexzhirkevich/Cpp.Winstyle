//
// Color.h
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

#ifndef _WINSTYLE_COLOR_
#define _WINSTYLE_COLOR_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include "ChildClass.h"

#define CLR_RAND			-1
#define CLR_WHITE			0
#define CLR_RED				1
#define CLR_DARKRED			2
#define CLR_TOMATO			3
#define CLR_ORANGE			4
#define CLR_LIGHTORANGE		5
#define CLR_OLIVE			6
#define CLR_GREEN			7
#define CLR_LIME			8
#define CLR_DARKGREEN		9
#define CLR_BLUE			10
#define CLR_SKYBLUE			11
#define CLR_DARKBLUE		12
#define CLR_AQUA			13
#define CLR_YELLOW			14
#define CLR_GOLD			15
#define CLR_BROWN			16
#define CLR_PINK			17
#define CLR_PURPLE			18
#define CLR_INDIGO			19
#define CLR_GRAY			20
#define CLR_BLACK			21

namespace wstyle {

	COLORREF GetBrush(int CLR_CONSTANT);
	COLORREF GetPenColor(int CLR_CONSTANT);

	class Color /* Class for WINAPI brush and pen combinations */
	{
	private:
		static bool RandomizeActivated;
	protected:
		class Select : public ChildClass<Color> {
			using ChildClass<Color>::ChildClass;
		public:
			Color	Red(), Darkred(), Tomato(), Orange(), Lightorange(),
				Olive(), Green(), Lime(), Darkgreen(), Blue(),
				Skyblue(), Darkblue(), Aqua(), Yellow(), Gold(),
				Brown(), Pink(), Purple(), Indigo(), Gray(),
				Black();
		};
		class Set : public ChildClass<Color> {
			using ChildClass<Color>::ChildClass;
		public:
			void BrushColor(COLORREF brush) { owner->BrushRef = brush; owner->Restore(); }
			void PenColor(COLORREF pen) { owner->PenRef = pen;  owner->Restore(); }
			void PenStyle(int _PenStyle) { owner->PenStyle = _PenStyle;  owner->Restore(); }
			void PenWidth(int _PenWidth) { owner->PenWidth = _PenWidth; owner->Restore(); }
		};
		class Get : public ChildClass<Color> {
			using ChildClass<Color>::ChildClass;
		public:
			int PenStyle() { return owner->PenStyle; }
			int PenWidth() { return owner->PenWidth; }
			HBRUSH Brush() const { return owner->Brush; } /* Retun HBRUSH */
			HPEN Pen() const { return owner->Pen; } /* Return HPEN */
			int BrushRValue() const { return GetRValue(owner->BrushRef); }
			int BrushGValue() const { return GetGValue(owner->BrushRef); }
			int BrushBValue() const { return GetBValue(owner->BrushRef); }
			int PenRValue() const { return GetRValue(owner->PenRef); }
			int PenGValue() const { return GetGValue(owner->PenRef); }
			int PenBValue() const { return GetBValue(owner->PenRef); }
			COLORREF BrushColor() const { return owner->BrushRef; } /* Return brush COLORREF */
			COLORREF PenColor() const { return owner->PenRef; } /* Return pen COLORREF */
		};
		COLORREF BrushRef; /* Brush COLORREF */
		COLORREF PenRef; /* Pen COLORREF */
		HBRUSH Brush;
		HPEN Pen;
		int PenStyle;
		UINT PenWidth;
		void Clone(const Color& c);
		void Restore();
		void Erase();
		void TranslateColor(int CLR_COLOR); /* Create a color using a CLR_ constants */
	public:
		Select Select;
		Set Set;
		Get Get;
		Color();
		Color(COLORREF colorref) : Color() { BrushRef = colorref, PenRef = colorref, Restore(); }
		Color(byte r, byte g, byte b) : Color(RGB(r, g, b)) {}
		Color(int CLR_COLOR) :Color() { TranslateColor(CLR_COLOR); };
		Color(COLORREF brush, COLORREF pen) : Color() { BrushRef = brush; PenRef = pen; Restore(); }
		Color(COLORREF brush, COLORREF pen, int PenStyle, UINT PenWidth);
		Color(int CLR_COLOR, int PenStyle, UINT PenWidth);
		Color(const Color& c) : Color() { Clone(c); };
		Color& operator = (const Color& c);
		Color operator ! (void) const; /* Get a color with swapped brush and pen COLORREF */
		Color& operator += (const Color& c); /* Mix colors */
		Color operator + (const Color& c) const; /* Mix colors */
		Color& operator += (int value); /*Increase BrushRef by value*/
		Color operator + (int value) const; /*Get new color with BrushRef increaed by value*/
		Color& operator -= (int value); /*Decrease BrushRef by value*/
		Color operator - (int value) const; /*Get new color with BrushRef decreased by value*/
		Color& operator ++ (void); /*Increase PenRef by 1*/
		Color& operator ++ (int); /*Increase BrushRef by 1*/
		Color& operator -- (void); /*Decrease PenRef by 1*/
		Color& operator -- (int); /*Decrease BrushRef by 1*/
		void PenToBrush() { PenRef = BrushRef; Restore(); } /* Make the pen identical to the brush */
		void BrushToPen() { BrushRef = PenRef; Restore(); } /* Make the brush identical to the pen */
		Color RandStable() { TranslateColor(1 + rand() % 20); return *this; } /* Randomize brush and pen from ready presets (normal colors) */
		Color RandUnstable(); /* Real randomize (unpredictable colors) */
		std::pair<HBRUSH, HPEN> SetOnDC(HDC hdc) const;
		Color Default(); /*Restore color to default values*/
		virtual ~Color() { Erase(); }
	};
}

#endif // _WINSTYLE_COLOR_