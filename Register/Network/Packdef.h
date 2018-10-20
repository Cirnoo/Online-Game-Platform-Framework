#pragma once
#include <string>
#include <iostream>

#define PRINT(a) std::cout<<a<<"\n";

#define _DEF_PORT 1234
#define _SERVER_IP "127.0.0.1"
#define _DEF_CLIENTPORT 2000
#define _DEF_SERVERPORT 10086
#define _DEF_SIZE 64
#define _DEF_ROOMBUFFERSIZE 550*1000
#define _DEF_NUM 10
#define _DEF_SQLLEN 100
#define USER_LENGTH 20
using std::wstring;
using std::string;

enum class MS_TYPE :unsigned char
{
	REGISTER_RQ,
	REGISTER_RE_T,
	REGISTER_RE_F,
	LOGIN_RQ,
	LOGIN_RE_T,
	LOGIN_RE_F,
	ADD_ROOM,
	GET_ROOM_LIST,
	HEARTBEAT,//ÐÄÌø°ü
};

struct USER_BUF
{
	wchar_t buf[USER_LENGTH];
	USER_BUF()
	{
		for(int i=0;i<USER_LENGTH;i++)
		{
			buf[i]=0;
		}
	}

	USER_BUF(const wstring & str)
	{
		this->USER_BUF::USER_BUF();
		str.copy(buf, str.size(), 0);
	}
	USER_BUF(const string & str)
	{
		wstring t=s2ws(str);
		this->USER_BUF::USER_BUF(t);
	}
	/*void operator=(const USER_BUF & u )
	{
		memcpy(buf,u.buf,USER_LENGTH);
	}
	void operator=(const wstring & str)
	{
		str.copy(buf, str.size(), 0);
	}*/
	wstring GetStr()
	{
		wstring str=wstring(buf);
		return str;
	}
	wstring s2ws(const string & str)
	{
		int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
		wchar_t *wide = new wchar_t[num];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
		std::wstring w_str(wide);
		delete[] wide;
		return w_str;
	}
};


struct USER_INFO
{
	USER_BUF name;
	USER_BUF password;
	USER_INFO()
	{
		name=L"";
		password=L"";
	}
	USER_INFO(USER_BUF n,USER_BUF p)
	{
		name=n;password=p;
	}
};
struct ROOM_INFO
{
	USER_BUF master,name;
	unsigned char num;
};
const int MAX_BUF_SIZE=sizeof(ROOM_INFO);
struct DATA_BUF
{
	char buf[MAX_BUF_SIZE];
	DATA_BUF()
	{
		memset(buf,MAX_BUF_SIZE,0);
	}
	template  <class T>
	DATA_BUF(const T & u)
	{
		for(int i=0;i<sizeof(u);i++)
		{
			buf[i]=(*((char *)&u+i));
		}
	}
	/*template  <class T>
	void operator=(const T & u )
	{
		for(int i=0;i<sizeof(u);i++)
		{
			buf[i]=(*((char *)&u+i));
		}
	}*/
};
struct DATA_PACKAGE
{
	MS_TYPE ms_type;
	DATA_BUF buf;
	template  <class T>
	DATA_PACKAGE(MS_TYPE type,T & u)
	{
		ms_type=type;
		buf=u;
	}
	DATA_PACKAGE()
	{
		this->DATA_PACKAGE::DATA_PACKAGE(MS_TYPE::HEARTBEAT,USER_INFO());
	}
};



