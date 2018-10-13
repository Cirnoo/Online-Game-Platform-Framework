#include "stdafx.h"
#include "Sys.h"
#include "resource.h"
#define ResFromResource TRUE
#if ResFromResource == TRUE
	#define LODE(a,b) a=ResizeImg(LoadPNGFormResource(b)); res.push_back(a); 
#else
	#define LODE(a,b) a=ResizeImg(Gdiplus::Image::FromFile(_T(b))); res.push_back(a);
#endif

#define INIT_RES(x) pImage x=NULL; 

//ȫ�ֶ���
Global sys;
using std::vector;
Global::Global()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	if (ResFromResource == TRUE)
	{
		LoadImgFromRes();
	}
	else
	{
		LoadImgFromFile();
	}
	fontfamily=new Gdiplus::FontFamily(L"����");
	font=new Gdiplus::Font(fontfamily,14,FontStyleRegular,UnitPixel);
	cfont=new CFont;
	cfont->CreateFont(
		16,							// ����ĸ߶�  
		8,							// ����Ŀ��  
		0,							// ������ʾ�ĽǶ�
		0,							// ����ĽǶ�
		FW_DONTCARE,				// ����İ���
		FALSE,						// б������
		FALSE,						// ���»��ߵ�����
		0,							// ��ɾ���ߵ�����
		GB2312_CHARSET,				// ������ַ���
		OUT_DEFAULT_PRECIS,			// ����ľ���
		CLIP_DEFAULT_PRECIS,		// �ü��ľ���
		DEFAULT_QUALITY,			// �߼�����������豸��ʵ��
		DEFAULT_PITCH | FF_SWISS,	// ����������弯
		L"����");					// ��������
}

Global::~Global()
{
	for (auto i:res)
	{
		delete i;
	}
	delete cfont;
	delete font;
	delete fontfamily;
	GdiplusShutdown(gdiplusToken);
}



void Global::LoadImgFromFile()
{
#if ResFromResource == FALSE
	LODE(back,"res\\bk.bmp");
	LODE(mask,"res\\mask.png");
	LODE(cirno,"res\\9.png");
	LODE(head_bk,"res\\head_bk.png");
	vec_bt_min=GetImageGroup(L"res\\BT_MIN.png",1,4);
	vec_bt_close=GetImageGroup(L"res\\BT_CLOSE.png",1,4);
	vec_bt_default=GetImageGroup(L"res\\BT_DEFAULT.png",1,4);
	vec_edit=GetImageGroup(L"res\\EDIT.png",1,2);
	vec_checkbox=GetImageGroup(L"res\\CHECK_BOX.png",1,6);
#endif
}


void Global::LoadImgFromRes()
{
	LODE(back,IDB_BK);
	LODE(mask,IDB_MASK);
	LODE(cirno,IDB_9);
	LODE(head_bk,IDB_HEAD_BK);
	vec_bt_min=GetImageGroup(IDB_BT_MIN,1,4);
	vec_bt_close=GetImageGroup(IDB_BT_CLOSE,1,4);
	vec_bt_default=GetImageGroup(IDB_BT_DEFAULT,1,4);
	vec_edit=GetImageGroup(IDB_EDIT,1,2);
	vec_checkbox=GetImageGroup(IDB_CHECK_BOX,1,6);
}

void DrawImage(CDC dc,pImage img,int x,int y)
{
	Graphics graphics(dc);
	graphics.DrawImage(img,x,y);
	return ;
}

pImage ResizeImg(pImage img) //����
{
	pImage newImg=img->GetThumbnailImage(img->GetWidth()*RESOLUTION,img->GetHeight()*RESOLUTION);
	delete img;
	return newImg;
}

std::vector<pImage> GetImageGroup(pImage img,int row,int col) //�����и�
{
	vector<pImage> vec;
	int Height=img->GetHeight()/row;
	int Width=img->GetWidth()/col;
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<col;j++)
		{
			vec.push_back(ResizeImg(CutImage(img,Width*j,Height*i,Width,Height)));
		}
	}
	return vec;
}

std::vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col)
{
	pImage temp=Gdiplus::Image::FromFile(img_path);
	vector<pImage> vec;
	vec=GetImageGroup(temp,row,col);
	delete temp;
	return vec;
}


vector<pImage> GetImageGroup(int nID,int row,int col)
{
	pImage temp=LoadPNGFormResource(nID);
	vector<pImage> vec;
	vec=GetImageGroup(temp,row,col);
	delete temp;
	return vec;
}

pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height)
{
	
	Bitmap *bmPhoto = new Bitmap(Width, Height);
	bmPhoto->SetResolution(imgSrc->GetHorizontalResolution(), imgSrc->GetVerticalResolution());
	Graphics grPhoto(bmPhoto);
	grPhoto.Clear((ARGB)Color::Transparent);
	grPhoto.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	grPhoto.DrawImage(imgSrc, 0, 0, x,y, Width,Height, UnitPixel);//�ؼ����룬ʵ�ֲü�
	bmPhoto->GetWidth();
	bmPhoto->GetHeight();
	return bmPhoto;
}

CRect RectTransform(Rect rect)
{
	return CRect(rect.GetLeft(),rect.GetTop(),rect.GetLeft()+rect.Width,rect.GetTop()+rect.Height);
}

RectF RectFTransform(Rect rect)
{
	return RectF(rect.GetLeft(),rect.GetTop(),rect.Width,rect.Height);
}




void ResizeRect(Rect& rec,int val)
{
	rec.X-=val;rec.Y-=val;
	rec.Height+=val;rec.Width+=val;
	
}

pImage LoadPNGFormResource(int nID)
{
	HINSTANCE hInst = AfxGetResourceHandle();  
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),_T("png")); // type  
	if (!hRsrc)  
		return FALSE;  
	// load resource into memory  
	DWORD len = SizeofResource(hInst, hRsrc);  
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
	if (!lpRsrc)  
		return FALSE;  
	// Allocate global memory on which to create stream  
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);  
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
	memcpy(pmem,lpRsrc,len);  
	IStream* pstm;  
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);  
	// load from stream  
	auto pImg=Gdiplus::Image::FromStream(pstm);  
	// free/release stuff  
	GlobalUnlock(m_hMem);  
	pstm->Release();  
	FreeResource(lpRsrc);  
	return pImg;  
}

