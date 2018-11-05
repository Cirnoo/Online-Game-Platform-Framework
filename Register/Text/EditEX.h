#pragma once
#include "PNGButton.h"
// CEditEX

class CEditEX : public CEdit
{
	DECLARE_DYNAMIC(CEditEX)

public:
	CEditEX();
	virtual ~CEditEX();
	void Show(Graphics* const g);
	BOOL CreateEditEx(const Rect rect,CWnd * const pParentWnd,const UINT nID,
		const std::vector<Image*> &,const bool password=false);
	void SetDefaultText(const CStringW str);
	wstring GetEditText() const;
	bool IsEmpty() const;
private:
	Rect mRect;
	std::vector<Image *> vec_bg;
	bool is_tracked;
	bool is_empty;
	void ControlRepaint() const;
	CBrush m_brush ;
	CStringW default_str;
protected:
	DECLARE_MESSAGE_MAP()
	bool is_password;
	void DrawEdit(Graphics* const g,const std::vector<Image*>& img);
	std::vector<std::vector<Image *>> vec_cut;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};


