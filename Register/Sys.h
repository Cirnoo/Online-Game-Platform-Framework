#pragma once
#include <memory>
#include <vector>
const double RESOLUTION = 1;


const int CMD_MINSIZE = 1;
const int CMD_CLOSE   = 2;

const int IDC_MIN   = 10001;
const int IDC_CLOSE = 10002;

//#ifndef PMAINDLG
//#define PMAINDLG CRegisterDlg *
//#endif
typedef  Image* pImage;

class Global
{
public:
	Global();
	~Global();
	pImage back,mask,bt_min;
	std::vector<pImage> vec_bt_min,vec_bt_close;
	unsigned long  gdiplusToken;
};

extern Global sys;

void DrawImage(CDC ,pImage ,int,int);

pImage ReSizeImg(pImage img);

std::vector<pImage> GetImageGroup(pImage img,int row,int col);
std::vector<pImage> GetImageGroup(WCHAR * img_path,int row,int col);
pImage CutImage(pImage imgSrc,int x,int y, int Width, int Height);