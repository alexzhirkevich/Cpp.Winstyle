#include "../include/Font.h"

void wstyle::Font::Set::Color(COLORREF _color) { owner->color = _color; }
void wstyle::Font::Set::Color(int CLR_CONSTANT) { wstyle::Color temp(CLR_CONSTANT); owner->color = temp.Get.BrushColor(); };
void wstyle::Font::Set::Height(LONG Height) { owner->lfont.lfHeight = Height; owner->Restore(); }
void wstyle::Font::Set::Width(LONG Width) { owner->lfont.lfWidth = Width; owner->Restore(); }
void wstyle::Font::Set::Weight(LONG Weight) { owner->lfont.lfHeight = Weight; owner->Restore(); }
void wstyle::Font::Set::FaceName(PCTCH FaceName) { 
	_tcscpy_s(owner->lfont.lfFaceName, _tcslen(FaceName) * sizeof(TCHAR), FaceName);
	owner->Restore();
}
void wstyle::Font::Set::Icalic(bool Italic) { owner->lfont.lfItalic = Italic; owner->Restore(); }
void wstyle::Font::Set::UnderLine(bool UnderLine) { owner->lfont.lfUnderline = UnderLine; owner->Restore(); }
void wstyle::Font::Set::StrikeOut(bool StrikeOut) { owner->lfont.lfStrikeOut = StrikeOut; owner->Restore(); }
void wstyle::Font::Set::Escapement(LONG Escapement) { owner->lfont.lfEscapement = Escapement; owner->Restore(); }
void wstyle::Font::Set::Orientation(LONG Orientation) { owner->lfont.lfOrientation = Orientation; owner->Restore(); }
void wstyle::Font::Set::CharSet(BYTE CharSet) { owner->lfont.lfCharSet = CharSet; owner->Restore(); }
void wstyle::Font::Set::OutPrecision(BYTE OutPrecision) { owner->lfont.lfOutPrecision = OutPrecision; owner->Restore(); }
void wstyle::Font::Set::ClipPrecision(BYTE ClipPrecision) { owner->lfont.lfClipPrecision = ClipPrecision; owner->Restore(); }
void wstyle::Font::Set::Quality(BYTE Quality) { owner->lfont.lfQuality = Quality; owner->Restore(); }
void wstyle::Font::Set::PitchAndFamily(BYTE PitchAndFamily) { owner->lfont.lfPitchAndFamily = PitchAndFamily; owner->Restore(); }

HFONT wstyle::Font::Get::Hfont() const { return owner->hfont; }
LONG wstyle::Font::Get::Height() const { return owner->lfont.lfHeight; }
LONG wstyle::Font::Get::Width() const { return owner->lfont.lfWidth; }
LONG wstyle::Font::Get::Weight() const { return owner->lfont.lfWeight; }
_tstring wstyle::Font::Get::FaceName() const { return owner->lfont.lfFaceName; }
LONG wstyle::Font::Get::Escapement() const { return owner->lfont.lfEscapement; }
LONG wstyle::Font::Get::Orientation() const { return owner->lfont.lfOrientation; }
BYTE wstyle::Font::Get::CharSer() const { return owner->lfont.lfCharSet; }
BYTE wstyle::Font::Get::OutPrecision() const { return owner->lfont.lfOutPrecision; }
BYTE wstyle::Font::Get::ClipPrecision() const { return owner->lfont.lfClipPrecision; }
BYTE wstyle::Font::Get::Quality() const { return owner->lfont.lfQuality; }
BYTE wstyle::Font::Get::PitchAndFamily() const { return owner->lfont.lfPitchAndFamily; }

inline wstyle::Font& wstyle::Font::operator=(const Font& f) {
	if (this == &f)
		return *this;
	Erase();
	Create(f.lfont);
	return *this;
}

inline void wstyle::Font::Default() {
	lfont.lfHeight = 0;
	lfont.lfWidth = 0;
	lfont.lfEscapement = 0;
	lfont.lfOrientation = 0;
	lfont.lfWeight = 400;
	lfont.lfItalic = 0;
	lfont.lfUnderline = 0;
	lfont.lfStrikeOut = 0;
	lfont.lfCharSet = DEFAULT_CHARSET;
	lfont.lfOutPrecision = 0;
	lfont.lfClipPrecision = 0;
	lfont.lfQuality = 0;
	lfont.lfPitchAndFamily = 0;
	_tcscpy_s(lfont.lfFaceName, _tcslen(TEXT("")) * sizeof(TCHAR), TEXT(""));
	color = RGB(0, 0, 0);
}

inline wstyle::Font::Font(LONG Height, LONG Width, PCTCH FaceName, COLORREF Color, LONG Weight, bool Italic,
	bool UnderLine, bool StrikeOut, LONG Escapement, LONG Orientation, BYTE CharSet,
	BYTE OutPrecision, BYTE ClipPrecision, BYTE Quality, BYTE PitchAndFamily) :Font() {
	Create(Height, Width, FaceName, color, Weight, Italic, UnderLine, StrikeOut, Escapement,
		Orientation, CharSet, OutPrecision, ClipPrecision, Quality, PitchAndFamily);
}

inline void wstyle::Font::Get::LogFont(LPLOGFONT logfont) const {
	logfont->lfHeight = owner->lfont.lfHeight;
	logfont->lfWidth = owner->lfont.lfWidth;
	logfont->lfEscapement = owner->lfont.lfEscapement;
	logfont->lfOrientation = owner->lfont.lfOrientation;
	logfont->lfWeight = owner->lfont.lfWeight;
	logfont->lfItalic = owner->lfont.lfItalic;
	logfont->lfUnderline = owner->lfont.lfUnderline;
	logfont->lfStrikeOut = owner->lfont.lfStrikeOut;
	logfont->lfCharSet = owner->lfont.lfCharSet;
	logfont->lfOutPrecision = owner->lfont.lfOutPrecision;
	logfont->lfClipPrecision = owner->lfont.lfClipPrecision;
	logfont->lfQuality = owner->lfont.lfQuality;
	logfont->lfPitchAndFamily = owner->lfont.lfPitchAndFamily;
	_tcscpy_s(logfont->lfFaceName,_tcslen(logfont->lfFaceName) * sizeof(TCHAR), owner->lfont.lfFaceName);
}

inline void wstyle::Font::Create(LONG Height, LONG Width, PCTCH FaceName, COLORREF Color, LONG Weight, bool Italic,
	bool UnderLine, bool StrikeOut, LONG Escapement, LONG Orientation, BYTE CharSet,
	BYTE OutPrecision, BYTE ClipPrecision, BYTE Quality, BYTE PitchAndFamily) {
	Default();
	lfont.lfHeight = Height;
	lfont.lfWeight = Width;
	lfont.lfEscapement = Escapement;
	lfont.lfOrientation = Orientation;
	lfont.lfWeight = Weight;
	lfont.lfItalic = Italic;
	lfont.lfUnderline = UnderLine;
	lfont.lfStrikeOut = StrikeOut;
	lfont.lfCharSet = CharSet;
	lfont.lfOutPrecision = OutPrecision;
	lfont.lfClipPrecision = ClipPrecision;
	lfont.lfQuality = Quality;
	lfont.lfPitchAndFamily = PitchAndFamily;
	_tcscpy_s(lfont.lfFaceName,_tcslen(FaceName) * sizeof(TCHAR), FaceName);
	Restore();
}

inline void wstyle::Font::Create(LOGFONT lf) {
	Default();
	lfont.lfHeight = lf.lfHeight;
	lfont.lfWeight = lf.lfWidth;
	lfont.lfEscapement = lf.lfEscapement;
	lfont.lfOrientation = lf.lfOrientation;
	lfont.lfWeight = lf.lfWeight;
	lfont.lfItalic = lf.lfItalic;
	lfont.lfUnderline = lf.lfUnderline;
	lfont.lfStrikeOut = lf.lfStrikeOut;
	lfont.lfCharSet = lf.lfCharSet;
	lfont.lfOutPrecision = lf.lfOutPrecision;
	lfont.lfClipPrecision = lf.lfClipPrecision;
	lfont.lfQuality = lf.lfQuality;
	lfont.lfPitchAndFamily = lf.lfPitchAndFamily;
	_tcscpy_s(lfont.lfFaceName,_tcslen(lf.lfFaceName), lf.lfFaceName);
	Restore();
}

inline void wstyle::Font::Erase() {
	DeleteFont(hfont);
	hfont = nullptr;
}