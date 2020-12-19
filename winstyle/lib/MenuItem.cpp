#include "..\include\MenuItem.h"
#include "..\include\MenuBar.h"
#include "..\include\Menu.h"
#include "..\include\AbstractAction.h"
#include "..\include\Control.h"

wstyle::MenuItem::MenuItem(): hMenu(nullptr), owner(nullptr),title(TEXT("MenuItem")),enabled(true),action(nullptr)
{
	hMenu = CreateMenu();
	id = Control::controlID++;
}

wstyle::MenuItem::MenuItem(PCTCH title) : MenuItem()
{
	this->title = title;
}

void wstyle::MenuItem::SetText(PCTCH text)
{
	title = text;
}

_tstring wstyle::MenuItem::GetText()
{
	return title.c_str();
}

bool wstyle::MenuItem::SetEnabled(bool enabled)
{
	if (owner && hMenu) {
		this->enabled = enabled;
		if (enabled)
			EnableMenuItem(owner->hMenu, id, MF_ENABLED);
		else
			EnableMenuItem(owner->hMenu, id, MF_DISABLED);
		return true;
	}
	this->enabled = enabled;
	return false;
}

void wstyle::MenuItem::addActionListener(const AbstractAction* aa)
{
	this->action = aa;
}

void wstyle::MenuItem::Delete()
{
	if (owner) {
		if (typeid(owner) == typeid(MenuBar*)) {
			MenuBar* mb = dynamic_cast<MenuBar*>(owner);
			mb->menus.erase(std::find(mb->menus.begin(), mb->menus.end(), this));
		}
		else
			owner->items.erase(std::find(owner->items.begin(), owner->items.end(), this));
		RemoveMenu(owner->hMenu, id, MF_DELETE);
	}
	DestroyMenu(hMenu);
	if (action && action->willBeDeleted())
		delete action;
}

wstyle::MenuItem::~MenuItem()
{
	Delete();
}

