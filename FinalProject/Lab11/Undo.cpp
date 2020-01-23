#include "Undo.h"

UndoAdd::UndoAdd(Product p, Repository *r)
{
	this->prod = p;
	this->repo = r;
}

void UndoAdd::doUndo()
{
	this->repo->remove(prod.get_name(), prod.get_type(), prod.get_producer());
}

UndoRemove::UndoRemove(Product p, Repository *r)
{
	this->prod = p;
	this->repo = r;
}

void UndoRemove::doUndo()
{
	this->repo->add(prod);
}

UndoUpdate::UndoUpdate(Product p, Repository *r)
{
	this->prod = p;
	this->repo = r;
}

void UndoUpdate::doUndo()
{
	this->repo->update(prod);
}

UndoAction::UndoAction()
{
}
