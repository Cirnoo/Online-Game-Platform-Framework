#pragma once
#include <memory>
#include <vector>

//全局常量
const double RESOLUTION = 1;

const int CMD_MINSIZE = 1;
const int CMD_CLOSE   = 2;

const int IDC_MIN   = 10001;
const int IDC_CLOSE = 10002;
const int IDC_PIC   = 10003;
const int ID_HEAD_BK= 10004;
typedef  Image* pImage;

class Global
{
public:
	Global();
	~Global();
	pImage back,mask,bt_min,cirno,head_bk;
	std::vector<pImage> vec_bt_min,vec_bt_close;
	Gdiplus::FontFamily * fontfamily;
	Gdiplus::Font *font;
	StringFormat format;
	SolidBrush * blackBrush;
	unsigned long  gdiplusToken;
};



void DrawImage(CDC ,pImage ,int,int);
pImage ReSizeImg(pImage img);
std::vector<pImage> GetImageGroup(pImage img,int row,int col);
std::vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col);
pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height);

CRect RectTransform(Rect rect);
RectF RectFTransform(Rect rect);
void ResizeRect(Rect& rec,int val);
extern Global sys;
