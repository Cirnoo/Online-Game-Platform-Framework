#include "stdafx.h"
#include "Sys.h"

#define LODE(a,b) a=ReSizeImg(Gdiplus::Image::FromFile(_T(b))) 
#define INIT_RES(x) pImage x=NULL; 

//全局对象
Global sys;

using std::vector;
Global::Global()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	LODE(back,"res\\bk.bmp");
	LODE(mask,"res\\mask.png");
	LODE(bt_min,"res\\BT_MIN.png");
	LODE(cirno,"res\\9.png");
	LODE(head_bk,"res\\head_bk.png");
	
	vec_bt_min=GetImageGroup(L"res\\BT_MIN.png",1,4);
	vec_bt_close=GetImageGroup(L"res\\BT_CLOSE.png",1,4);
	vec_bt_default=GetImageGroup(L"res\\BT_DEFAULT.png",1,4);
	vec_edit=GetImageGroup(L"res\\EDIT.png",1,2);
	fontfamily=new Gdiplus::FontFamily(L"微软雅黑");
	font=new Gdiplus::Font(fontfamily,12,FontStyleRegular,UnitPixel);
	cfont=new CFont;
	cfont->CreateFont(
		16,							// 字体的高度  
		0,							// 字体的宽度  
		0,							// 字体显示的角度
		0,							// 字体的角度
		FW_DONTCARE,				// 字体的磅数
		FALSE,						// 斜体字体
		FALSE,						// 带下划线的字体
		0,							// 带删除线的字体
		GB2312_CHARSET,				// 所需的字符集
		OUT_DEFAULT_PRECIS,			// 输出的精度
		CLIP_DEFAULT_PRECIS,		// 裁减的精度
		DEFAULT_QUALITY,			// 逻辑字体与输出设备的实际
		DEFAULT_PITCH | FF_SWISS,	// 字体间距和字体集
		L"宋体");					// 字体名称
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


