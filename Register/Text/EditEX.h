#pragma once
#include "PNGButton.h"
#include "Text.h"
// CEditEX

class CEditEX : public CEdit
{
	DECLARE_DYNAMIC(CEditEX)

public:
	CEditEX();
	virtual ~CEditEX();
public:
	void Show(Graphics* & g);
	BOOL CreateEditEx(Rect rect,CWnd * pParentWnd,UINT nID,
		std::vector<Image*> &);
protected:
	DECLARE_MESSAGE_MAP()
	bool is_password;
	void DrawEdit(Graphics* & g,std::vector<Image*> img);
	std::vector<std::vector<Image *>> vec_cut;
private:
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	void ControlRepaint();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


