#pragma once

class CBaseControl;
class CEditEX;
#include "MySocket.h"
class Mediator
{
public:
	Mediator();
	~Mediator();
	void InitControl(CWnd * const pParentWnd);
	void ShowControl(Graphics* const);
	bool GetTask() const;
	USER_INFO GetUserInfo() const;
	void OnLogin();
private:
	bool task_flag;
	std::vector<CBaseControl *> vec_control;
	std::vector<CEditEX *> vec_edit;
	CEditEX * GetEditCtl(int nID) const;
	
};

