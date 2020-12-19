#include "winstyle/include/Window.h"
#include "winstyle/include/Button.h"
#include "winstyle/include/AbstractAction.h"
#include "winstyle/include/EditText.h"
#include "winstyle/include/Color.h"
#include "winstyle/include/Chart.h"
#include "winstyle/include/MenuBar.h"
#include "winstyle/include/Menu.h"
#include "winstyle/include/MenuItem.h"


using namespace wstyle;

class Form : public Window {

	Button* btn = new Button(this);
	Chart* chart = new Chart(_T("Автомобиль какой фирмы вы используете?"));
	MenuBar* menuBar = new MenuBar();
	Menu* menu = new Menu(TEXT("File"));

	MenuItem* menuItem = new MenuItem(TEXT("Quit"));


	bool draw = false;

	LRESULT OnCreate(WPARAM wParam, LPARAM lParam) override {
		
		menuItem->addActionListener(new AbstractAction([] { PostQuitMessage(EXIT_SUCCESS); }, true));
	//	menuItem->SetEnabled(false);
		menu->add(menuItem);
		menuBar->add(menu);
		menuBar->set(this);
	

		btn->SetText(TEXT("Построить диаграмму"));
		btn->SetBounds(Get.Width() / 2 - 150, Get.Height() / 2 - 50, 150, 50);
		btn->addActionListener(new AbstractAction([&]() { btn->SetVisible(false); draw = true; Update(); },true));

		chart->Background.Color = Color(CLR_SKYBLUE, PS_SOLID, 5);
		chart->Text.Title.Font = Font(30, 800, TEXT("Times"));
		chart->Text.Title.Color = GetPenColor(CLR_RED);
		chart->Text.Items.Font = Font(20, 400, TEXT("Times"));
		chart->Text.Items.Color = GetPenColor(CLR_WHITE);
		chart->AddValue(TEXT("Toyota"), 800, Color(CLR_RED, PS_SOLID, 5));
		chart->AddValue(TEXT("Mazda"), 966, Color(CLR_YELLOW, PS_SOLID, 5));
		chart->AddValue(TEXT("Ford"), 1024, Color(CLR_BROWN, PS_SOLID, 5));
		chart->AddValue(TEXT("ВАЗ"), 321, Color(CLR_GREEN, PS_SOLID, 5));
		chart->AddValue(TEXT("Другой"), 166, Color(CLR_INDIGO, PS_SOLID, 5));
		chart->Sort([](wstyle::Chart::ChartItem a, Chart::ChartItem b) { return a.Value > b.Value; });

		return 0;
	};

	LRESULT OnPaint(WPARAM wParam, LPARAM lParam) override {
		if (draw) {
			chart->SetDrawRect(Get.ClientRect());
			chart->Paint(GetPaintDC());
		}
		return 0;
	}
	
	~Form() { delete chart; }
};

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {

	Form* f = new Form();
	f->Run();

	return 0;
}