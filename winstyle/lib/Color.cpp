#include "../include/Color.h"

COLORREF wstyle::GetBrush(int CLR_CONSTANT) { return wstyle::Color(CLR_CONSTANT).Get.BrushColor(); }
COLORREF wstyle::GetPenColor(int CLR_CONSTANT) { return wstyle::Color(CLR_CONSTANT).Get.PenColor(); }

bool wstyle::Color::RandomizeActivated = false;

wstyle::Color wstyle::Color::Select::Red() { owner->BrushRef = RGB(255, 0, 0); owner->PenRef = RGB(128, 0, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Darkred() { owner->BrushRef = RGB(139, 0, 0); owner->PenRef = RGB(102, 0, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Tomato() { owner->BrushRef = RGB(255, 99, 71); owner->PenRef = RGB(255, 69, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Orange() { owner->BrushRef = RGB(255, 102, 0); owner->PenRef = RGB(153, 61, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Lightorange() { owner->BrushRef = RGB(255, 133, 51); owner->PenRef = RGB(204, 82, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Olive() { owner->BrushRef = RGB(128, 128, 0); owner->PenRef = RGB(68, 102, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Green() { owner->BrushRef = RGB(0, 153, 0); owner->PenRef = RGB(0, 80, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Lime() { owner->BrushRef = RGB(0, 255, 0); owner->PenRef = RGB(0, 153, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Darkgreen() { owner->BrushRef = RGB(0, 100, 0); owner->PenRef = RGB(26, 51, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Blue() { owner->BrushRef = RGB(0, 102, 204); owner->PenRef = RGB(0, 0, 150); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Skyblue() { owner->BrushRef = RGB(102, 153, 255); owner->PenRef = RGB(51, 102, 255); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Darkblue() { owner->BrushRef = RGB(0, 0, 255); owner->PenRef = RGB(0, 0, 150); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Aqua() { owner->BrushRef = RGB(0, 255, 255); owner->PenRef = RGB(0, 153, 153); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Yellow() { owner->BrushRef = RGB(255, 255, 102); owner->PenRef = RGB(179, 179, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Gold() { owner->BrushRef = RGB(255, 215, 0); owner->PenRef = RGB(255, 153, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Brown() { owner->BrushRef = RGB(128, 64, 0); owner->PenRef = RGB(77, 38, 0); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Pink() { owner->BrushRef = RGB(255, 153, 204); owner->PenRef = RGB(204, 51, 153); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Purple() { owner->BrushRef = RGB(128, 0, 128); owner->PenRef = RGB(153, 51, 153); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Indigo() { owner->BrushRef = RGB(153, 51, 255); owner->PenRef = RGB(102, 0, 204); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Gray() { owner->BrushRef = RGB(128, 128, 128); owner->PenRef = RGB(89, 89, 89); owner->Restore(); return *owner; }
wstyle::Color wstyle::Color::Select::Black() { owner->BrushRef = RGB(0, 0, 0); owner->PenRef = RGB(0, 0, 0); owner->Restore(); return *owner; }

 void wstyle::Color::Clone(const Color& c) {
	BrushRef = c.BrushRef;
	PenRef = c.PenRef;
	PenWidth = c.PenWidth;
	PenStyle = c.PenStyle;
	Restore();
}

 wstyle::Color::Color() :Pen(nullptr), Brush(nullptr), Select(this), Set(this), Get(this) {
	if (!RandomizeActivated)
	{
		srand((unsigned int)time(NULL));
		RandomizeActivated = true;
	}
	BrushRef = RGB(255, 255, 255);
	PenRef = RGB(0, 0, 0);
	PenStyle = PS_SOLID;
	PenWidth = 1;
	Brush = CreateSolidBrush(BrushRef);
	Pen = CreatePen(PenStyle, PenWidth, PenRef);
}

 wstyle::Color::Color(int CLR_COLOR, int PenStyle, UINT PenWidth) : Color() {
	this->PenStyle = PenStyle;
	this->PenWidth = PenWidth;
	TranslateColor(CLR_COLOR);
}

 wstyle::Color::Color(COLORREF brush, COLORREF pen, int PenStyle, UINT PenWidth) :Color() {
	this->PenStyle = PenStyle;
	this->PenWidth = PenWidth;
	BrushRef = brush;
	PenRef = pen;
	Brush = CreateSolidBrush(BrushRef);
	Pen = CreatePen(PenStyle, PenWidth, PenRef);
}

std::pair<HBRUSH, HPEN> wstyle::Color::SetOnDC(HDC hdc) const {
	return std::make_pair(SelectBrush(hdc, Brush), SelectPen(hdc, Pen));
}

 wstyle::Color wstyle::Color::RandUnstable() {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	int r1 = 0, g1 = 0, b1 = 0;
	if (r >= 15)
		r1 = r - 15;
	if (g >= 15)
		g1 = g - 15;
	if (b >= 15)
		b1 = b - 15;
	BrushRef = RGB(r, g, b);
	PenRef = RGB(r1, g1, b1);
	Restore();
	return *this;
}

 void wstyle::Color::TranslateColor(int CLR_COLOR) {
	switch (CLR_COLOR)
	{
	case CLR_RAND: RandStable(); return;
	case CLR_WHITE: Default(); return;
	case CLR_RED: Select.Red(); return;
	case CLR_DARKRED: Select.Darkred(); return;
	case CLR_TOMATO: Select.Tomato(); return;
	case CLR_ORANGE: Select.Orange(); return;
	case CLR_LIGHTORANGE: Select.Lightorange(); return;
	case CLR_OLIVE: Select.Olive(); return;
	case CLR_GREEN: Select.Green(); return;
	case CLR_LIME: Select.Lime(); return;
	case CLR_DARKGREEN: Select.Darkgreen(); return;
	case CLR_BLUE: Select.Blue(); return;
	case CLR_SKYBLUE: Select.Skyblue(); return;
	case CLR_DARKBLUE: Select.Darkblue(); return;
	case CLR_AQUA: Select.Aqua(); return;
	case CLR_YELLOW: Select.Yellow(); return;
	case CLR_GOLD: Select.Gold(); return;
	case CLR_BROWN: Select.Brown(); return;
	case CLR_PINK: Select.Pink(); return;
	case CLR_PURPLE: Select.Purple(); return;
	case CLR_INDIGO: Select.Indigo(); return;
	case CLR_GRAY: Select.Gray(); return;
	case CLR_BLACK: Select.Black(); return;
	default: Default();
	}
}

 wstyle::Color& wstyle::Color::operator = (const Color& c) {
	if (this == &c)
		return *this;
	Erase();
	Clone(c);
	return *this;
}

 wstyle::Color wstyle::Color::operator !() const {
	Color c(PenRef, BrushRef, PenStyle, PenWidth);
	return c;
}

 wstyle::Color& wstyle::Color::operator+=(const Color& c) {
	BrushRef = RGB((Get.BrushRValue() + c.Get.BrushRValue()) / 2, (Get.BrushGValue() + c.Get.BrushGValue()) / 2, (Get.BrushBValue() + c.Get.BrushBValue()) / 2);
	PenRef = RGB((Get.PenRValue() + c.Get.PenRValue()) / 2, (Get.PenGValue() + c.Get.PenGValue()) / 2, (Get.PenBValue() + c.Get.PenBValue()) / 2);
	Restore();
	return *this;
}

 wstyle::Color wstyle::Color::operator+(const Color& c) const {
	Color temp(*this);
	temp += c;
	return temp;
}

 wstyle::Color& wstyle::Color::operator +=(int value) {

	int red = Get.BrushRValue();
	int green = Get.BrushGValue();
	int blue = Get.BrushBValue();

	if (red == 255 && green == 255 && blue == 255)
		return *this;

	(red + value <= 255) ? (red += value) : (red = 255);
	(green + value <= 255) ? (green += value) : (green = 255);
	(blue + value <= 255) ? (blue += value) : (blue = 255);

	BrushRef = RGB(red, green, blue);
	Restore();
	return *this;
}

 wstyle::Color wstyle::Color::operator + (int value) const {
	Color temp(*this);
	temp += value;
	return temp;
}

 wstyle::Color& wstyle::Color::operator -=(int value) {

	int red = Get.BrushRValue();
	int green = Get.BrushGValue();
	int blue = Get.BrushBValue();

	if (red == 0 && green == 0 && blue == 0)
		return *this;

	((red - value >= 0) ? (red -= value) : (red = 0));
	((green - value >= 0) ? (green -= value) : (green = 0));
	((blue - value >= 0) ? (blue -= value) : (blue = 0));

	BrushRef = RGB(red, green, blue);
	Restore();
	return *this;
}

 wstyle::Color wstyle::Color::operator - (int value) const {
	Color temp(*this);
	temp -= value;
	return temp;
}

 wstyle::Color& wstyle::Color::operator ++ (void) {

	int red = Get.PenRValue();
	int green = Get.PenGValue();
	int blue = Get.PenBValue();

	if (red == 255 && green == 255 && blue == 255)
		return *this;

	(red <= 254) ? (red++) : (red = 255);
	(green <= 254) ? (green++) : (green = 255);
	(blue <= 254) ? (blue++) : (blue = 255);

	PenRef = RGB(red, green, blue);
	Restore();
	return *this;
}

 wstyle::Color& wstyle::Color::operator ++ (int) {
	*this += 1;
	return *this;
}

 wstyle::Color& wstyle::Color::operator -- (void) {

	int red = Get.PenRValue();
	int green = Get.PenGValue();
	int blue = Get.PenBValue();

	if (red == 0 && green == 0 && blue == 0)
		return *this;

	(red >= 1) ? (red--) : (red = 0);
	(green >= 1) ? (green--) : (green = 0);
	(blue >= 1) ? (blue--) : (blue = 0);

	PenRef = RGB(red, green, blue);
	Restore();
	return *this;
}

 wstyle::Color& wstyle::Color::operator -- (int) {
	*this -= 1;
	return *this;
}

 wstyle::Color wstyle::Color::Default() {
	BrushRef = RGB(255, 255, 255);
	PenRef = RGB(0, 0, 0);
	PenWidth = 1;
	PenStyle = PS_SOLID;
	Restore();
	return *this;
}

 void wstyle::Color::Erase() {
	DeleteBrush(Brush);
	DeletePen(Pen);
	Brush = nullptr;
	Pen = nullptr;
}

 void wstyle::Color::Restore() {
	DeleteBrush(Brush);
	DeletePen(Pen);
	Brush = CreateSolidBrush(BrushRef);
	Pen = CreatePen(PenStyle, PenWidth, PenRef);
}