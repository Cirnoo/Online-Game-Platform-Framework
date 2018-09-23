#include "stdafx.h"
#include "Sys.h"

#define LODE(a,b) a=ReSizeImg(Gdiplus::Image::FromFile(_T(b))) 
#define INIT_RES(x) pImage x=NULL; 

//全局对象
Global sys;
using namespace std;


Global::Global()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	LODE(back,"res\\bk.bmp");
	LODE(mask,"res\\mask.png");
	LODE(bt_min,"res\\BT_MIN.png");
	vec_bt_min=GetImageGroup(L"res\\BT_MIN.png",1,4);
	vec_bt_close=GetImageGroup(L"res\\BT_CLOSE.png",1,4);
}

Global::~Global()
{
	GdiplusShutdown(gdiplusToken);
}



void DrawImage(CDC dc,pImage img,int x,int y)
{
	Graphics graphics(dc);
	graphics.DrawImage(img,x,y);
	return ;
}

pImage ReSizeImg(pImage img) //缩放
{
	pImage newImg=img->GetThumbnailImage(img->GetWidth()*RESOLUTION,img->GetHeight()*RESOLUTION);
	delete img;
	return newImg;
}

std::vector<pImage> GetImageGroup(pImage img,int row,int col) //行列切割
{
	vector<pImage> vec;
	int Height=img->GetHeight()/row;
	int Width=img->GetWidth()/col;
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<col;j++)
		{
			vec.push_back(CutImage(img,Width*j,Height*i,Width,Height));
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

pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height)
{
	
	Bitmap *bmPhoto = new Bitmap(Width, Height);
	bmPhoto->SetResolution(imgSrc->GetHorizontalResolution(), imgSrc->GetVerticalResolution());
	Graphics grPhoto(bmPhoto);
	grPhoto.Clear((ARGB)Color::Transparent);
	grPhoto.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	grPhoto.DrawImage(imgSrc, 0, 0, x,y, Width,Height, UnitPixel);//关键代码，实现裁剪
	bmPhoto->GetWidth();
	bmPhoto->GetHeight();
	return bmPhoto;
}
