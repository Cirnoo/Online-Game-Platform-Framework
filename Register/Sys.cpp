#include "stdafx.h"
#include "Sys.h"
#include "resource.h"
#include "Packdef.h"



#define INIT_RES(x) pImage x=NULL; 



Global & Global::GetInstance()
{
	return *Global::sys;
}
Global::Global()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	LoadImg();
	InitSockAddr();
	fontfamily=new Gdiplus::FontFamily(L"宋体");
	font=new Gdiplus::Font(fontfamily,14,FontStyleRegular,UnitPixel);
	cfont=new CFont;
	cfont->CreateFont(
		16,							// 字体的高度  
		8,							// 字体的宽度  
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
	client_info.player_name=L"沙包";
	client_info.password=L"";
}

Global::~Global()
{
	
	delete cfont;
	delete font;
	delete fontfamily;
	GdiplusShutdown(gdiplusToken);
}


void Global::LoadImg()
{
	LoadImg(back,IDB_BK);
	LoadImg(mask,IDB_MASK);
	LoadImg(cirno,IDB_9);
	LoadImg(head_bk,IDB_HEAD_BK);
	LoadImg(game_tool,IDB_GAME_TOOL,false);
	game_tool=ResizeImg(game_tool,0.9);
	vec_bt_min=GetImageGroup(IDB_BT_MIN,1,4);
	vec_bt_close=GetImageGroup(IDB_BT_CLOSE,1,4);
	vec_bt_default=GetImageGroup(IDB_BT_DEFAULT,1,4);
	vec_edit=GetImageGroup(IDB_EDIT,1,2);
	vec_checkbox=GetImageGroup(IDB_CHECK_BOX,1,6);
}


void Global::LoadImg(pImage & img,int nId,bool resize/*=true*/)
{
	if (resize)
	{
		img=ResizeImg(LoadPNGFormResource(nId));
	}
	else
	{
		img=LoadPNGFormResource(nId);
	}
}

void Global::InitSockAddr()
{
	auto & addrServer=client_info.addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr(_SERVER_IP);
	addrServer.sin_port = htons(_DEF_SERVERPORT);
}



pImage ResizeImg(pImage img,double scale) //缩放
{
	pImage newImg=img->GetThumbnailImage(img->GetWidth()*scale,img->GetHeight()*scale);
	delete img;
	return newImg;
}

std::vector<pImage> GetImageGroup(pImage img,int row,int col) //行列切割
{
	ASSERT(row>0&&col>0);
	vector<pImage> vec;
	vec.reserve(row*col);
	const int Height=img->GetHeight()/row;
	const int Width=img->GetWidth()/col;
	for (int i=0;i<row;i++)
	{
		for (int j=0;j<col;j++)
		{
			vec.push_back(CutImage(img,Width*j,Height*i,Width,Height));
		}
	}
	//delete img;  //这里不能delete img资源是可能需要复用的
	return vec;
}

std::vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col)
{
	pImage temp=Gdiplus::Image::FromFile(img_path);
	vector<pImage> vec=GetImageGroup(temp,row,col);
	delete temp;
	return vec;
}


vector<pImage> GetImageGroup(int nID,int row,int col)
{
	pImage temp=LoadPNGFormResource(nID);
	vector<pImage> vec=GetImageGroup(temp,row,col);
	delete temp;
	return vec;
}

pImage CutImage(const pImage imgSrc,int x,int y, int Width, int Height)
{
	Bitmap *bmPhoto = new Bitmap(Width, Height);
	bmPhoto->SetResolution(imgSrc->GetHorizontalResolution(), imgSrc->GetVerticalResolution());
	Graphics grPhoto(bmPhoto);
	grPhoto.Clear((ARGB)Color::Transparent);
	grPhoto.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	grPhoto.DrawImage(imgSrc, 0, 0, x,y, Width,Height, UnitPixel);//关键代码，实现裁剪
	return bmPhoto;
}


pImage CutImage(const pImage imgSrc,const CRgn & region)
{
	Rect img_rect(0,0,imgSrc->GetWidth(),imgSrc->GetHeight());
	Bitmap * bit_temp=new Bitmap(img_rect.Width,img_rect.Height);
	Graphics gr_temp(bit_temp);
	CRgn crgn;
	crgn.CreateRectRgn(0,0,imgSrc->GetWidth(),imgSrc->GetHeight());
	crgn.CombineRgn(&crgn,&region,RGN_DIFF);
	gr_temp.DrawImage(imgSrc,img_rect);
	gr_temp.FillRegion(&SolidBrush(Color::White),&Region(crgn));
	

	Bitmap * bit_region=new Bitmap(img_rect.Width,img_rect.Height);
	Graphics gr_region(bit_region);
	gr_region.FillRegion(&SolidBrush(Color::White),&Region(region));
	ImageAttributes imgAttributes;
	imgAttributes.SetColorKey(Color(255,255,255,255),Color(255,255,255,255),
		ColorAdjustTypeBitmap);
	gr_region.DrawImage(bit_temp,img_rect,0,0,img_rect.Width,img_rect.Height,UnitPixel,&imgAttributes);
	//感觉mfc好麻烦啊。。
	delete bit_temp;
	return bit_region;
}

CRect Rect2CRect(Rect rect)
{
	return CRect(rect.GetLeft(),rect.GetTop(),rect.GetLeft()+rect.Width,rect.GetTop()+rect.Height);
}

RectF Rect2RectF(Rect rect)
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
	
	HINSTANCE hInst = GetModuleHandle(NULL);  
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

bool ShowError()
{
	int error=GetLastError();
	if (!error)
	{
		return false;
	}
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox(NULL,(LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONWARNING |MB_SYSTEMMODAL );
	// Free the buffer.
	LocalFree( lpMsgBuf );
	return error;
}

void InvalidateRect(int x, int y, int width, int height)
{
	AfxGetMainWnd()->InvalidateRect(CRect(x,y,x+width,y+height));
}


