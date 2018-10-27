#pragma once
#include <vector>
#include "Tool.h"
#include "Packdef.h"
//全局常量
const double RESOLUTION = 1.1;

const int CMD_MINSIZE = 1;
const int CMD_CLOSE   = 2;

const int ID_BASE				 =	  10000;
const int IDC_MIN				 =	  ID_BASE+1;
const int IDC_CLOSE				 =	  ID_BASE+2;
const int IDC_PIC				 =	  ID_BASE+3;
const int ID_HEAD_BK				 =	  ID_BASE+4;
const int IDC_REGISTER			 =	  ID_BASE+5;
const int IDC_EDIT_USER			 =	  ID_BASE+6;
const int IDC_EDIT_KEY			 =	  ID_BASE+7;
const int IDC_CHECK_1			 =    ID_BASE+8;
const int IDC_NET				 =    ID_BASE+9;
const int IDC_LINK_1				 =	  ID_BASE+10;
const int IDC_LINK_2				 =	  ID_BASE+11;
const int IDC_LINK_3				 =	  ID_BASE+13;
const int IDC_EDIT_LOGIN_USER	 =	  ID_BASE+14;
const int IDC_EDIT_LOGIN_KEY		 =	  ID_BASE+15;
const int WM_LOGIN				 =    WM_USER+10;//登录消息
const int WM_REGISETR		     =    WM_USER+11;//注册消息
const int WM_ADD_ROOM		     =    WM_USER+12;
const int WM_UPDATE_ROOM		     =    WM_USER+13;
#define Warning(x) ::MessageBox(NULL,_T(x),_T(""), MB_OK|MB_SYSTEMMODAL|MB_ICONEXCLAMATION  );
typedef  Image* pImage;
using std::vector;
class Global
{
public:
	static Global & GetInstance();
	~Global();
	Global();
	pImage back,mask,cirno,head_bk,game_bg;
	std::vector<pImage> vec_bt_min,vec_bt_close,vec_bt_default,vec_edit,vec_checkbox;
	Gdiplus::FontFamily * fontfamily;
	Gdiplus::Font *font;
	CFont * cfont;
	unsigned long  gdiplusToken;
	sockaddr_in  addrServer;
	USER_INFO  user;
private:
	static Global * sys;
	std::vector<pImage> res;
	void LoadImg();
	void LoadImg(pImage & img,int nId,bool resize=true);
	void InitSockAddr();
};

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

bool ShowError();

unsigned char GetBufSize(MS_TYPE type);