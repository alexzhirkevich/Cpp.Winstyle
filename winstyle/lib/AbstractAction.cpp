#include "../include/AbstractAction.h"

wstyle::AbstractAction::AbstractAction() : deleteWithControl(false), onActionPerfomed(nullptr), async(false) {
}

wstyle::AbstractAction::AbstractAction(const std::function<void()> onActionPerfomed, bool deleteWithControl,bool async) : AbstractAction() {
	this->deleteWithControl = deleteWithControl;
	this->async = async;
	setOnActionPerfomed(onActionPerfomed);
}

void wstyle::AbstractAction::setOnActionPerfomed(const std::function<void()> onActionPerfomed){
	this->onActionPerfomed = onActionPerfomed;
}

void wstyle::AbstractAction::setAsync(bool async)
{
	this->async = async;
}

void wstyle::AbstractAction::setDeleteWithControl(bool destroy)
{
	this->deleteWithControl = destroy;
}

void wstyle::AbstractAction::execute() const
{
	onActionPerfomed();
}

bool wstyle::AbstractAction::willBeDeleted() const
{
	return deleteWithControl;
}

bool wstyle::AbstractAction::isAsync() const
{
	return async;
}
