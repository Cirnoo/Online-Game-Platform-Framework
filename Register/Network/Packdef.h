#pragma once
#include <string>
#include <iostream>
#include <vector>
#define PRINT(a) std::cout<<a<<"\n";

#define _DEF_PORT 1234
#define _SERVER_IP "127.0.0.1"
#define _DEF_CLIENTPORT 2000
#define _DEF_SERVERPORT 10086
#define _DEF_SIZE 64
#define _DEF_ROOMBUFFERSIZE 550*1000
#define _DEF_NUM 10
#define _DEF_SQLLEN 100
#define USER_LENGTH 10
#define ERROR_SOCKET_ALREADE_CONNECT 10056
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
	CREATE_ROOM,
	CREATE_ROOM_RE_T,
	CREATE_ROOM_RE_F,
	ENTER_ROOM,
	ENTER_ROOM_RE_T,
	ENTER_ROOM_RE_F,
	MATE_INFO_UPDATE,
	LEAVE_ROOM,
	UPDATE_ROOM,
	GAME_START,
	ALLOC_POKER,
	GAME_WIN,
	WANT_LANDLORD,
	NOT_WANT_LANDLORD,
	GAME_OFFLINE,
	HEARTBEAT,//心跳包
};

enum class CardType : unsigned char
{
	Diamond		,
	Club		    ,
	Heart		,
	Spade		,
	Joker	    ,
};
enum class PokerPoints : unsigned char
{
	Three=0,Four,Five,Six,Seven,Eight,Nine,Ten,jack,Queen,King,Ace,Two,Black_Joker,Red_Joker,
	
};

struct Poker		//单张扑克
{
	CardType c_type;
	PokerPoints point;
	bool hide;  //是否背面
	bool check; //是否选中
	bool select; //是否被框选
	Poker(){InitVar();}
	Poker(char num)
	{
		InitVar();
		ASSERT(num>=0&&num<54);
		if (num<52)
		{
			c_type=CardType(num/13);
			point=PokerPoints(num%13);
		}
		else
		{
			c_type=CardType::Joker;
			point=PokerPoints(num-52+13);
		}
	}
	Poker(CardType t,PokerPoints p)
	{
		InitVar();
		c_type=t;
		point=p;
	}
	int operator-(const Poker & p) const
	{
		return p.GetPointVal()-this->GetPointVal();
	}
	bool operator==(const Poker & p) const
	{
		return point==p.point;
	}
	char toNum() const
	{
		return c_type==CardType::Joker?52-13+(char)point:13*(char)c_type+(char)point;
	}
	char GetPointVal() const
	{
		return static_cast<char> (point);
	}
private:
	void InitVar()
	{
		hide=false;check=false;select=false;
	}

};


enum ArrayType : unsigned char
{
	无,单牌,对子,三张,三带一,三带对,顺子,双顺,三顺,飞机,四带二,炸弹,王炸

	//英文无力,绝望了
};

struct CardArray		//需要打出的牌
{
	char cards[20]; //一次最多打20张牌
	ArrayType type;	//牌组类型
	unsigned char point; //计算出的大小点数
	unsigned char num;  //牌个数
	CardArray(const std::vector<Poker> & vec, ArrayType _type,unsigned char _point )
	{
		memset(cards,0,sizeof(cards));
		num=vec.size();
		type=_type;point=_point;
		for (int i=0;i<num;i++)
		{
			cards[i]=vec[i].toNum();
		}
	}
};
struct USER_BUF
{
	wchar_t buf[USER_LENGTH];
	USER_BUF()
	{
		Clear();
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
	USER_BUF& operator=(const USER_BUF & u )
	{
		memcpy(buf,u.buf,USER_LENGTH);
		return *this;
	}
	USER_BUF& operator=(const wstring & str)
	{
		str.copy(buf, str.size(), 0);
		return *this;
	}
	wstring GetStr() const
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
	void Clear()
	{
		memset(buf,0,sizeof(buf));
	}
};


struct USER_INFO
{
	USER_BUF name;
	USER_BUF password;
	USER_INFO()
	{
		name.Clear();
		password.Clear();
	}
	USER_INFO(USER_BUF n,USER_BUF p)
	{
		name=n;password=p;
	}
};


struct ROOM_LIST_INFO
{
	USER_BUF name;
	unsigned char num;
};

struct PLAYER_INFO
{
	USER_BUF name,room_name;
	char pos;
};

class QTcpSocket;
struct ENTER_ROOM_RE
{
	USER_BUF mate_name[3];
	char player_pos;
};
struct ROOM_INFO
{
	wstring mate_arr[3],name;
	char num;
	QTcpSocket * socket_arr[3];
	ROOM_INFO()
	{
		for(int i=0;i<3;i++)
		{
			socket_arr[i]=nullptr;
		}
		num=0;
	}
	bool AddPlayer( QTcpSocket * _socket,const PLAYER_INFO & info)
	{
		for(int i=0;i<3;i++)
		{
			if(socket_arr[i]==nullptr)
			{
				if(i==0)
				{
					name=info.room_name.GetStr();
					
				}
				++num;
				mate_arr[i]=info.name.GetStr();
				socket_arr[i]=_socket;
				return true;
			}
		}
		return false;
	}
};

const unsigned int MAX_BUF_SIZE=sizeof(ROOM_LIST_INFO)*3;


struct DATA_PACKAGE
{
	struct DATA_BUF
	{
		char buf[MAX_BUF_SIZE];
		DATA_BUF()
		{
			memset(buf,0,MAX_BUF_SIZE);
		}
		template  <class T>
		DATA_BUF(const T & u)
		{
			int i=0;
			for(i=0;i<sizeof(u);i++)
			{
				buf[i]=(*((char *)&u+i));
			}
			memset(buf+i,0,MAX_BUF_SIZE-i);
		}
		void Clear()
		{
			memset(buf,0,MAX_BUF_SIZE);
		}
	};
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
		ms_type=MS_TYPE::HEARTBEAT;
		buf.Clear();
	}
};

