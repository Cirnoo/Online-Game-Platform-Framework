#pragma once

class CBaseControl;
class CEditEX;
#include "MySocket.h"
class Mediator
{
public:
	Mediator();
	~Mediator();
	void InitControl(CWnd * pParentWnd);
	void ShowControl(Graphics* &);
	bool GetTask();
	USER_INFO GetUserInfo();
	void OnLogin();
private:
	bool task_flag;
	std::vector<CBaseControl *> vec_control;
	std::vector<CEditEX *> vec_edit;
	CEditEX * GetEditCtl(int nID);
	
};

