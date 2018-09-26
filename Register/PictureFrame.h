#pragma once
#include "Sys.h"
#include "BaseControl.h"
// CPictureFrame

class CPictureFrame : public CBaseControl
{
	DECLARE_DYNAMIC(CPictureFrame)

public:
	CPictureFrame();
	virtual ~CPictureFrame();
	BOOL Create(Rect rc,CWnd * pParentWnd,UINT ControlID,pImage _img);
	virtual void Show(Graphics* & g);
protected:
	DECLARE_MESSAGE_MAP()
private:
	pImage mImg;
};


