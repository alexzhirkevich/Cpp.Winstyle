#include "../include/MenuBar.h"
#include "../include/Menu.h"
#include "../include/Window.h"

wstyle::MenuBar::MenuBar() : hMenu(nullptr), owner(nullptr)
{
	hMenu = CreateMenu();
}

bool wstyle::MenuBar::add(MenuItem* menu)
{
	if (menu) {
		menu->owner = this;
		AppendMenu(hMenu, MF_STRING, menu->id, menu->GetText().c_str());
		menuItems.push_back(menu);
		menu->SetEnabled(menu->enabled);
		if (owner && owner->menuBar == this)
			SetMenu(owner->hWnd, hMenu);
		return true;
	}
	return false;
}

bool wstyle::MenuBar::add(Menu* menu)
{
	if (menu) {
		menu->owner = this;
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)menu->hMenu, menu->GetText().c_str());
		menus.push_back(menu);
		menu->SetEnabled(menu->enabled);
		if (owner && owner->menuBar == this)
			SetMenu(owner->hWnd, hMenu);
		return true;
	}
	return false;
}

bool wstyle::MenuBar::set(Window* owner)
{
	if (owner && hMenu) {
		this->owner = owner;
		owner->menuBar = this;
		SetMenu(owner->hWnd, hMenu);
		return true;
	}
	return false;
}
