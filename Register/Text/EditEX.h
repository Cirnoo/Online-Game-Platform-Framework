#pragma once
#include "PNGButton.h"
// CEditEX

class CEditEX : public CEdit
{
	DECLARE_DYNAMIC(CEditEX)

public:
	CEditEX();
	virtual ~CEditEX();
	void Show(Graphics* & g);
	BOOL CreateEditEx(Rect rect,CWnd * pParentWnd,UINT nID,
		std::vector<Image*> &,bool password=false);
	void SetDefaultText(CStringW str);
	wstring GetEditText();
	bool IsEmpty();
private:
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_empty;
	void ControlRepaint();
	CBrush m_brush ;
	CStringW default_str;
protected:
	DECLARE_MESSAGE_MAP()
	bool is_password;
	void DrawEdit(Graphics* & g,std::vector<Image*> img);
	std::vector<std::vector<Image *>> vec_cut;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


