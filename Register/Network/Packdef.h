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

enum class MS_TYPE :unsigned char
{
	REGISTE_RQ,
	REGISTE_RE_T,
	REGISTE_RE_F,
	LOGIN_RQ,
	LOGIN_RE_T,
	LOGIN_RE_F,
	MAX_VAL,
};
using std::string;
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
	void operator=(const USER_BUF & u )
	{
		memcpy(buf,u.buf,USER_LENGTH);
	}
	void operator=(const wstring & str)
	{
		str.copy(buf, str.size(), 0);
	}
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
};

struct DATA_PACKAGE
{
	MS_TYPE ms_type;
	USER_INFO user;
	DATA_PACKAGE(MS_TYPE type,USER_BUF name, USER_BUF password)
	{
		ms_type=type;
		user.name=name;
		user.password=password;
	}
	DATA_PACKAGE(MS_TYPE type,string name, string password)
	{
		ms_type=type;
		user.name=name;
		user.password=password;
	}
	DATA_PACKAGE()
	{
		this->DATA_PACKAGE::DATA_PACKAGE(MS_TYPE::MAX_VAL,string(),string());
	}
};


