#pragma once

class CBaseControl;

class Mediator
{
public:
	Mediator();
	~Mediator();
	void InitControl(CWnd * pParentWnd);
	void ShowControl(Graphics* &);
	bool GetTask();
private:
	bool task_flag;
	std::vector<CBaseControl *> vec_control;
	
};

