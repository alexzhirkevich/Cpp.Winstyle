#include "../include/Chart.h"

#if defined _MSC_VER && _MSC_VER >=1200
#pragma warning(push)
#endif

#pragma warning(disable:4267)


wstyle::Chart::ChartItem::ChartItem() : owner(nullptr) {
	Color.RandUnstable();
	Value = 0;
	Title = TEXT("Unknown");
}

wstyle::Chart::ChartItem::ChartItem(PCTCH _title, double _val, Chart* _owner) {
	owner = _owner;
	Value = _val;
	Title = _title;
}

wstyle::Chart::ChartItem::ChartItem(PCTCH _title, double _val, Chart* _owner, wstyle::Color _clr) {
	owner = _owner;
	Color = _clr;
	Value = _val;
	Title = _title;
}

void wstyle::Chart::ChartItem::Clone(const ChartItem& ci) {
	owner = ci.owner;
	Color = ci.Color;
	Value = ci.Value;
	Title = ci.Title;
}

void wstyle::Chart::ChartItem::Erase() {
	Title = TEXT("Unknown");
}

wstyle::Chart::ChartItem& wstyle::Chart::ChartItem::operator =(const ChartItem& ci) {
	if (this == &ci)
		return *this;
	Erase();
	Clone(ci);
	return *this;
}

bool wstyle::Chart::ChartItem::RemoveFromChart() {
	return owner->DeleteValue(Title.c_str());
}

wstyle::Chart::Chart() : Visible(true), ShowPercent(true), ShowValues(false), maxValue(0), sumValue(0) {
	title = TEXT("Chart");
	DrawRect.left = DrawRect.top = DrawRect.right = DrawRect.bottom = 0;
}

wstyle::Chart::Chart(PCTCH _title) : Chart() {
	title = _title;
}

wstyle::Chart::Chart(PCTCH _title, RECT _drawRect) : Chart(_title) {
	DrawRect = _drawRect;
}

size_t wstyle::Chart::Size() const { return Values.size(); }

void wstyle::Chart::Clone(const Chart& c) {
	SetTitle(c.title.c_str());
	for (size_t i = 0; i < c.Values.size(); i++)
		AddValue(c.Values[i].Title.c_str(), c.Values[i].Value, c.Values[i].Color);
	Visible = c.Visible;
	ShowPercent = c.ShowPercent;
	ShowValues = c.ShowValues;
	Text = c.Text;
	Background = c.Background;
	DrawRect = c.DrawRect;
}

wstyle::Chart& wstyle::Chart::operator=(const Chart& c) {
	if (this == &c)
		return *this;
	Erase();
	Clone(c);
	return *this;
}

void wstyle::Chart::SetTitle(PCTCH _title) {
	title = _title;
}

void wstyle::Chart::SetDrawRect(RECT _drawRect) {
	DrawRect = _drawRect;
}

void wstyle::Chart::AddValue(PCTCH title, double value) {
	Values.push_back(ChartItem(title, value, this));
	sumValue += value;
	if (value > maxValue)
		maxValue = value;
}

void wstyle::Chart::AddValue(PCTCH title, double value, const Color& clr) {
	Values.push_back(ChartItem(title, value, this, clr));
	sumValue += value;
	if (value > maxValue)
		maxValue = value;
}

wstyle::Chart::ChartItem& wstyle::Chart::operator [](int index) {
	if (index >= (int)Values.size() || index < 0)
		throw WstyleException(TEXT("Chart error: operator[] - invalid index"));
	return Values[index];
}

wstyle::Chart::cIt wstyle::Chart::Find(PCTCH tit) {
	for (cIt i = Values.begin(); i != Values.end(); i++)
		if (i->Title == tit) {
			return i;
		}
	return Values.end();
}

bool wstyle::Chart::DeleteValue(PCTCH _title) {
	cIt delIt = Find(_title);
	if (delIt != Values.end()) {
		if (delIt->Value == maxValue && Size() > 1) {
			maxValue = (this->operator[](0)).Value;
			delIt->Value = maxValue;
			for (size_t i = 0; i < Size(); i++) {
				if (this->operator[](i).Value > maxValue)
					maxValue = this->operator[](i).Value;
			}
		}
		Values.erase(delIt);
		return true;
	}
	return false;
}

bool wstyle::Chart::Paint(HDC hdc) {
	if (!Visible)
		return true;
	if (!hdc || (DrawRect.top == 0 && DrawRect.left == 0 && DrawRect.right == 0 && DrawRect.bottom == 0))
		return false;


	HFONT hPrevFont = Text.Title.Font.SetOnDC(hdc);
	std::pair<HBRUSH, HPEN> obj = Background.Color.SetOnDC(hdc);
	HBRUSH hPrevBrush = obj.first;
	HPEN hPrevPen = obj.second;
	int prevBkMode = SetBkMode(hdc, Background.Mode);
	COLORREF prevTextColor = SetTextColor(hdc, Text.Title.Color);
	if (Background.SetVisible)
		Rectangle(hdc, DrawRect.left, DrawRect.top, DrawRect.right, DrawRect.bottom);
	if (Text.Items.Font.Get.Height() + Text.Title.Font.Get.Height() + 2 * Background.Color.Get.PenWidth() < DrawRect.bottom - DrawRect.top) {
		if (Text.Title.SetVisible)
			DrawText(hdc, title.c_str(), title.length() + 1, &DrawRect, DT_CENTER | DT_TOP | DT_SINGLELINE);
	}
	else
	{
		SetTextColor(hdc, prevTextColor);
		SelectFont(hdc, hPrevFont);
		SelectBrush(hdc, hPrevBrush);
		SelectPen(hdc, hPrevPen);
		DrawText(hdc, TEXT("Not enough space"), _tcslen(TEXT("Not enough space")) + 1, &DrawRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return false;
	}
	if (Values.size() > 0)
	{
		SetTextColor(hdc, Text.Items.Color);
		Text.Items.Font.SetOnDC(hdc);
		double step = (((double)DrawRect.right - (double)DrawRect.left) * 0.96) / (2.0 * (double)Values.size() - 1.0);
		for (size_t i = 0; i < Values.size(); i++) {
			Values[i].Color.SetOnDC(hdc);

			RECT tRect;
			tRect.bottom = DrawRect.bottom - abs(Text.Items.Font.Get.Height()) - Background.Color.Get.PenWidth();
			tRect.top = (LONG)((tRect.bottom - abs(Text.Title.Font.Get.Height())) * (1 - Values[i].Value / maxValue) + abs(Text.Title.Font.Get.Height()));
			tRect.left = (LONG)((((double)DrawRect.right - (double)DrawRect.left) * 0.02) + DrawRect.left + step * (2.0 * (double)i));
			tRect.right = tRect.left + (LONG)step;
			Rectangle(hdc, tRect.left, tRect.top, tRect.right, tRect.bottom);
			if (ShowPercent && !ShowValues) {
				_tstring s = to_tstring((int)(Values[i].Value / sumValue * 100.0)).append("%");
				DrawText(hdc, s.c_str(), s.size() + 1, &tRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			}
			else
				if (!ShowPercent && ShowValues) {
					_tstring str = to_tstring((int)Values[i].Value);
					DrawText(hdc, str.c_str(), str.size() + 1, &tRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
					if (ShowPercent && ShowValues) {
						_tstring str = to_tstring((int)Values[i].Value);
						tRect.top -= Text.Items.Font.Get.Height();
						DrawText(hdc, str.c_str(), str.length() + 1, &tRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						tRect.top += 2 * Text.Items.Font.Get.Height();
						str = to_tstring((int)(Values[i].Value / sumValue * 100.0)).append(TEXT("%"));
						DrawText(hdc, str.c_str(), str.size() + 1, &tRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
			tRect.left -= (LONG)(step / 2);
			tRect.right += (LONG)(step / 2);
			tRect.bottom = DrawRect.bottom - Background.Color.Get.PenWidth();
			tRect.top = DrawRect.top;
			DrawText(hdc, Values[i].Title.c_str(), Values[i].Title.length(), &tRect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
		}
	}
	SetTextColor(hdc, prevTextColor);
	SelectFont(hdc, hPrevFont);
	SelectBrush(hdc, hPrevBrush);
	SelectPen(hdc, hPrevPen);
	SetBkMode(hdc, prevBkMode);
	return true;
}

void wstyle::Chart::Erase() {
	Values.clear();
}

void wstyle::Chart::Sort(bool (*Pred)(ChartItem first, ChartItem second)) {
	std::sort(Values.begin(), Values.end(), Pred);
}

void wstyle::Chart::Sort(BOOL(*Pred)(ChartItem first, ChartItem second)) {
	std::sort(Values.begin(), Values.end(), Pred);
}

#if defined _MSC_VER && _MSC_VER >=1200
#pragma warning(pop)
#endif