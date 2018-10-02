// PictureFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "Register.h"
#include "PictureFrame.h"


// CPictureFrame

IMPLEMENT_DYNAMIC(CPictureFrame, CWnd)

CPictureFrame::CPictureFrame()
{

}

CPictureFrame::~CPictureFrame()
{
}


BOOL CPictureFrame::Create(Rect rc,CWnd * pParentWnd,UINT ControlID,pImage _img)
{
	LPCTSTR lpszClassName=AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW ,  AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(TRANSPARENT), NULL) ;   
	mImg=_img;
	mRect=rc;
	BOOL OK=CWnd::Create(NULL,NULL,WS_CHILDWINDOW|WS_VISIBLE,Rect2CRect(mRect),pParentWnd, ControlID, NULL);
	ModifyStyleEx(0, WS_EX_TRANSPARENT); 
	
	return OK;
}

void CPictureFrame::Show(Graphics* & g)
{
	g->DrawImage(mImg,mRect);
	
}


BEGIN_MESSAGE_MAP(CPictureFrame, CWnd)
END_MESSAGE_MAP()



// CPictureFrame 消息处理程序

