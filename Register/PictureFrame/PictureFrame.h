#pragma once
#include "BaseControl.h"
// CPictureFrame

class CPictureFrame : public CBaseControl
{
	DECLARE_DYNAMIC(CPictureFrame)

public:
	CPictureFrame();
	virtual ~CPictureFrame();
public:
	BOOL Create(const Rect rc,CWnd * const pParentWnd,
		const UINT ControlID,pImage const _img);
	BOOL Create(const Region region,const CWnd * const pParentWnd,
		const UINT ControlID,pImage const _img);
	virtual void Show(Graphics* const g);
protected:
	DECLARE_MESSAGE_MAP()

private:
	pImage mImg;
};


