//
// Chart.h
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

#ifndef _WINSTYLE_CHART_
#define _WINSTYLE_CHART_

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Init.h"
#include "Color.h"
#include "Font.h"
#include "WinstyleException.h"

namespace wstyle {

	class Chart
	{
	public:
		class ChartItem {
			friend class Chart;
		protected:
			Chart* owner;
			void Clone(const ChartItem& ci);
			void Erase();
		public:
			double Value;
			Color Color;
			_tstring Title;
			ChartItem();
			ChartItem(const ChartItem& ci) :ChartItem() { Clone(ci); }
			ChartItem(PCTCH _title, double _val, Chart* owner);
			ChartItem(PCTCH _title, double _val, Chart* owner, wstyle::Color _clr);
			bool RemoveFromChart();
			ChartItem& operator =(const ChartItem& ci);
			~ChartItem() { Erase(); }
		};
	protected:
		struct Background {
			int Mode;
			Color Color;
			bool Visible;
			Background() : Visible(true), Mode(TRANSPARENT) {};
		};
		struct Text {
			struct Title {
				COLORREF Color;
				Font Font;
				bool Visible;
				Title() : Visible(true), Color(RGB(0, 0, 0)) {};
			};
			struct Items {
				COLORREF Color;
				Font Font;
				bool Visible;
				Items() : Visible(true), Color(RGB(0, 0, 0)) {};
			};
			Title Title;
			Items Items;
		};

		typedef std::vector<ChartItem> cList;
		typedef cList::iterator cIt;

		_tstring title;
		double maxValue;
		double sumValue;
		cList Values;
		cIt Find(PCTCH tit);
		void Clone(const Chart& c);
	public:
		Background Background;
		RECT DrawRect;
		Text Text;
		bool Visible;
		bool ShowPercent;
		bool ShowValues;
		Chart();
		Chart(PCTCH title);
		Chart(PCTCH title, RECT drawRect);
		int Size() const { return Values.size(); }
		Chart(const Chart& c) :Chart() { Clone(c); }
		Chart& operator = (const Chart& c);
		void SetTitle(PCTCH title);
		void SetDrawRect(RECT drawRect);
		void AddValue(PCTCH title, double value);
		void AddValue(PCTCH title, double value, const Color& clr);
		bool DeleteValue(PCTCH title);
		bool Paint(HDC hdc);
		ChartItem& operator [](int index);
		void Erase();
		void Sort(bool (*Pred)(ChartItem first, ChartItem second));
		void Sort(BOOL(*Pred)(ChartItem first, ChartItem second));
		virtual ~Chart() { Erase(); }
	};

}

#endif // _WINSTYLE_CHART_