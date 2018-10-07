#pragma once
#include "PNGButton.h"
#include "Text.h"
// CEditEX

class CEditEX : public CPNGButton
{
	DECLARE_DYNAMIC(CEditEX)

public:
	CEditEX();
	virtual ~CEditEX();
public:
	void Show(Graphics* & g);
	virtual BOOL Create(Rect rect,CWnd * pParentWnd,UINT nID,
		std::vector<Image*> &);
protected:
	DECLARE_MESSAGE_MAP()
	void ShowEditCursor();
	void HideEditCursor();
	bool is_password;
	static CEdit * mEdit;
	CText mText;
	void DrawEdit(Graphics* & g,std::vector<Image*> img);
	std::vector<std::vector<Image *>> vec_cut;
	virtual void ClickCmd();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


