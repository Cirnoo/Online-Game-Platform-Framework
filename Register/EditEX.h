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
	
protected:
	DECLARE_MESSAGE_MAP()
	void ShowEdit();
	void HideEdit();
	bool is_password;
	CEdit * mEdit;
	CText mText;
};


