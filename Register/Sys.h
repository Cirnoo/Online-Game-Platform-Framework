#pragma once
#include <memory>
#include <vector>

//全局常量
const double RESOLUTION = 1;

const int CMD_MINSIZE = 1;
const int CMD_CLOSE   = 2;

const int ID_BASE		 =	  10000;
const int IDC_MIN		 =	  ID_BASE+1;
const int IDC_CLOSE		 =	  ID_BASE+2;
const int IDC_PIC		 =	  ID_BASE+3;
const int ID_HEAD_BK		 =	  ID_BASE+4;
const int IDC_REGISTER   =	  ID_BASE+5;
const int IDC_EDIT_USER  =	  ID_BASE+6;
const int IDC_EDIT_KEY   =	  ID_BASE+7;
const int IDC_CHECK_1    =    ID_BASE+8;
const int IDC_NET		 =    ID_BASE+9;
const int IDC_LINK_1     =    ID_BASE+10;
typedef  Image* pImage;

class Global
{
public:
	Global();
	~Global();
	
	pImage back,mask,bt_min,cirno,head_bk;
	std::vector<pImage> vec_bt_min,vec_bt_close,vec_bt_default,vec_edit,vec_checkbox;
	Gdiplus::FontFamily * fontfamily;
	Gdiplus::Font *font;
	CFont * cfont;
	unsigned long  gdiplusToken;
private:
	std::vector<pImage> res;
};



void DrawImage(CDC ,pImage ,int,int);
pImage ResizeImg(pImage img);
std::vector<pImage> GetImageGroup(pImage img,int row,int col);
std::vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col);
pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height);

CRect RectTransform(Rect rect);
RectF RectFTransform(Rect rect);

void ResizeRect(Rect& rec,int val);

WCHAR * multiByteToWideChar(const CString pKey);
extern Global sys;
