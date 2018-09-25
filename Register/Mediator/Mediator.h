#pragma once
#include "BaseControl.h"
#include "Sys.h"
class Mediator
{
public:
	Mediator();
	~Mediator();
	void InitControl(CWnd * pParentWnd);
	void ShowControl(Graphics* &);
	void SwichControl(bool flag);
private:
	std::vector<CBaseControl *> vec_control;
	
};

