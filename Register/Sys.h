#pragma once
#include <memory>
#include <vector>

//全局常量
const double RESOLUTION = 1.1;

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
const int IDC_LINK_2		 =	  ID_BASE+11;
const int IDC_LINK_3		 =	  ID_BASE+13;
typedef  Image* pImage;
using std::vector;
class Global
{
public:
	Global();
	~Global();
	
	pImage back,mask,cirno,head_bk;
	std::vector<pImage> vec_bt_min,vec_bt_close,vec_bt_default,vec_edit,vec_checkbox;
	Gdiplus::FontFamily * fontfamily;
	Gdiplus::Font *font;
	CFont * cfont;
	unsigned long  gdiplusToken;
private:
	std::vector<pImage> res;
	void LoadImgFromFile();
	void LoadImgFromRes();
};



void DrawImage(CDC ,pImage ,int,int);
pImage LoadPNGFormResource(int nId);
pImage ResizeImg(pImage img);
vector<pImage> GetImageGroup(pImage img,int row,int col);
vector<pImage> GetImageGroup(int nID,int row,int col);
vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col);

pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height);

CRect RectTransform(Rect rect);
RectF RectFTransform(Rect rect);

void ResizeRect(Rect& rec,int val);

WCHAR * multiByteToWideChar(const CString pKey);
extern Global sys;
