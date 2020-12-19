#include "..\include\Menu.h"
#include "..\include\MenuBar.h"
#include "..\include\MenuItem.h"
#include "..\include\Window.h"
#include "..\include\AbstractAction.h"

wstyle::Menu::~Menu()
{
	Delete();
}

wstyle::Menu::Menu() : owner(nullptr)
{
	hMenu = CreatePopupMenu();
	title = TEXT("Menu");
}

wstyle::Menu::Menu(PCTCH title) : Menu()
{
	this->title = title;
}

//bool wstyle::Menu::SetEnabled(bool enabled)
//{
//	if (hMenu && owner) {
//		if (enabled)
//			EnableMenuItem(owner->hMenu, (UINT)hMenu, MF_ENABLED);
//		else
//			EnableMenuItem(owner->hMenu, (UINT)hMenu, MF_DISABLED);
//		this->enabled = enabled;
//		return true;
//	}
//	else
//		this->enabled = enabled;
//		
//	return false;
//}
//
//void wstyle::Menu::SetText(PCTCH text)
//{
//	title = text;
//}
//
//_tstring wstyle::Menu::GetText()
//{
//	return title;
//}

bool wstyle::Menu::add(MenuItem* mi)
{
	if (hMenu) {
		mi->owner = this;
		AppendMenu(hMenu, MF_STRING, mi->id, mi->GetText().c_str());
		mi->SetEnabled(mi->enabled);
		items.push_back(mi);
		return true;
	}
	return false;
}

void wstyle::Menu::Delete()
{
	if (owner) {
		owner->menus.erase(std::find(owner->menus.begin(), owner->menus.end(), this));
		RemoveMenu(owner->hMenu, (UINT)hMenu, MF_DELETE);
		if (owner->owner)
			DrawMenuBar(owner->owner->hWnd);
	}
	DestroyMenu(hMenu);
	if (action)
		delete action;
}

