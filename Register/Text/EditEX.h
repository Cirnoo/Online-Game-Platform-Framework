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
		std::vector<Image*> &,bool password=false);
	void SetDefaultText(CStringW str);
protected:
	DECLARE_MESSAGE_MAP()
	bool is_password;
	void DrawEdit(Graphics* & g,std::vector<Image*> img);
	std::vector<std::vector<Image *>> vec_cut;
private:
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_empty;
	void ControlRepaint();
	CBrush m_brush ;
	CStringW default_str;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


