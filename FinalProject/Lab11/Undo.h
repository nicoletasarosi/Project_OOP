#pragma once
//#include "Product.h"
#include "Repository.h"

class UndoAction
{
	
public:
	UndoAction();
	virtual ~UndoAction() {}
	virtual void doUndo() = 0;
};

class UndoAdd : public UndoAction
{
private:
	Product prod;
	Repository *repo;
public:
	UndoAdd(Product p, Repository *r);
	void doUndo() override;
};

class UndoRemove : public UndoAction
{
private:
	Product prod;
	Repository *repo;
public:
	UndoRemove(Product p, Repository *r);
	void doUndo() override;
};

class UndoUpdate : public UndoAction
{
private:
	Product prod;
	Repository *repo;
public: 
	UndoUpdate(Product p, Repository *r);
	void doUndo() override;
};