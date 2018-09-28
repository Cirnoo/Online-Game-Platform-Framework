#pragma once
#include "PNGButton.h"
#include <vector>
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
};


