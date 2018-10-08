#pragma once

class CBaseControl;
class Mediator:public CWnd
{
	DECLARE_DYNAMIC(Mediator)
public:
	Mediator();
	~Mediator();
	void InitControl(CWnd * pParentWnd);
	void ShowControl(Graphics* &);
	bool GetTask();
	BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID);
protected:
	DECLARE_MESSAGE_MAP()
private:
	bool task_flag;
	std::vector<CBaseControl *> vec_control;
	
public:
	afx_msg void OnPaint();
};

