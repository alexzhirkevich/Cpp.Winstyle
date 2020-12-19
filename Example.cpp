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
	Chart* chart = new Chart(_T("Which car do you use?"));
	MenuBar* menuBar = new MenuBar();
	Menu* menu = new Menu(TEXT("File"));
	MenuItem* menuItem = new MenuItem(TEXT("Quit"));

	LRESULT OnCreate(WPARAM wParam, LPARAM lParam) override {		
		// Func called on window create. Can be replaced with cunstructor
		
		menuItem->addActionListener(new AbstractAction(	
			[] { PostQuitMessage(EXIT_SUCCESS); }, true));	 // Exit app on Quit menu strip;
		menu->add(menuItem);		// Add Quit strip to File menu;
		menuBar->add(menu);			// add File menu to menu bar;	
		menuBar->set(this);			// add menu bar to window;

		btn->SetText(TEXT("Build diagram"));	
		btn->SetBounds(Get.Width() / 2 - 150, Get.Height() / 2 - 50, 150, 50);
		btn->addActionListener(new AbstractAction(				// Show chart on bnt click
			[&]() { btn->SetVisible(false); chart->Visible = true;  Update(); }, true)); 

		chart->Background.Color = Color(CLR_SKYBLUE, PS_SOLID, 5);		// Chart background color
		chart->Text.Title.Font = Font(30, 800, TEXT("Times"));			// Chart title font
		chart->Text.Title.Color = GetPenColor(CLR_RED);					// Chart title color
		chart->Text.Items.Font = Font(20, 400, TEXT("Times"));			// Chart items font
		chart->Text.Items.Color = GetPenColor(CLR_WHITE);				// Chart items color
		chart->AddValue(TEXT("Toyota"), 800, Color(CLR_RED, PS_SOLID, 5));		
		chart->AddValue(TEXT("Mazda"), 966, Color(CLR_YELLOW, PS_SOLID, 5));
		chart->AddValue(TEXT("Ford"), 1024, Color(CLR_BROWN, PS_SOLID, 5));		// Add elements for chart
		chart->AddValue(TEXT("BMW"), 321, Color(CLR_GREEN, PS_SOLID, 5));
		chart->AddValue(TEXT("Peugeout"), 166, Color(CLR_INDIGO, PS_SOLID, 5));
		chart->Sort([](wstyle::Chart::ChartItem a, Chart::ChartItem b) {
			return a.Value > b.Value; });			// Sort chart elements
		chart->Visible = false;			// Make chart invisible;
		return 0;
	};

	LRESULT OnPaint(WPARAM wParam, LPARAM lParam) override {		
		// Func called on every window update

		chart->SetDrawRect(Get.ClientRect());
		chart->Paint(this); // !!! Paint funcs can be called only from Window::OnPaint;
		return 0;
	}

public:
	~Form() { delete chart; delete btn; delete menuBar; delete menu; delete menuItem; }
};

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) {

	Form* f = new Form();
	f->Run();

	delete f;

	return 0;
}