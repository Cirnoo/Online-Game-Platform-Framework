#ifndef _PACKDEF_H
#define _PACKDEF_H

#define _DEF_PORT 1234
#define _SERVER_IP "127.0.0.1"
#define _DEF_CLIENTPORT 2000
//�ٽ�ֵ
#define _DEF_SIZE 64
#define _DEF_ROOMBUFFERSIZE 550*1000
#define _DEF_NUM 10
#define _DEF_SQLLEN 100

typedef char PackType;
#define BEGIN_PROTOCOLMAP const ProtocolMap m_ProtocolMapEntries[]= \
{

#define END_PROTOCOLMAP 	{0,0} \
};

#define PM(X,Y)  {X,Y},

//Э��
#define _DEF_PROTOCOL_BASE   100

#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2

#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4

#define _DEF_PROTOCOL_GETROOMLIST_RQ   _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_GETROOMLIST_RS   _DEF_PROTOCOL_BASE +6

#define _DEF_PROTOCOL_GETROOMINFO_RQ   _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_GETROOMINFO_RS   _DEF_PROTOCOL_BASE +8


#define _DEF_PROTOCOL_SELECTROOM_RQ   _DEF_PROTOCOL_BASE +9
#define _DEF_PROTOCOL_SELECTROOM_RS   _DEF_PROTOCOL_BASE +10

#define _DEF_PROTOCOL_STARTPLAY_RQ   _DEF_PROTOCOL_BASE +11
#define _DEF_PROTOCOL_STARTPLAY_RS   _DEF_PROTOCOL_BASE +12
 
#define _DEF_PROTOCOL_UPLOADOPREATION_RQ   _DEF_PROTOCOL_BASE +13
#define _DEF_PROTOCOL_UPLOADOPREATION_RS   _DEF_PROTOCOL_BASE +14

#define _DEF_PROTOCOL_CREATEROOM_RQ   _DEF_PROTOCOL_BASE +15
#define _DEF_PROTOCOL_CREATEROOM_RS   _DEF_PROTOCOL_BASE +16

#define _DEF_PROTOCOL_READYPLAY_RQ   _DEF_PROTOCOL_BASE +17
#define _DEF_PROTOCOL_READYPLAY_RS   _DEF_PROTOCOL_BASE +18


#define _DEF_PROTOCOL_GAMEOVERMSG_RQ   _DEF_PROTOCOL_BASE +19
#define _DEF_PROTOCOL_GAMEOVERMSG_RS   _DEF_PROTOCOL_BASE +20

#define _DEF_PROTOCOL_UPDATEROOMSTATE_RQ   _DEF_PROTOCOL_BASE +21
#define _DEF_PROTOCOL_UPDATEROOMSTATE_RS   _DEF_PROTOCOL_BASE +22

#define _DEF_PROTOCOL_GAMEGOING_RQ   _DEF_PROTOCOL_BASE +23
#define _DEF_PROTOCOL_GAMEGOING_RS   _DEF_PROTOCOL_BASE +24

#define _DEF_PROTOCOL_SENDCARDS_RQ   _DEF_PROTOCOL_BASE +25
#define _DEF_PROTOCOL_SENDCARDS_RS   _DEF_PROTOCOL_BASE +26

#define _DEF_PROTOCOL_EXITROOM_RQ   _DEF_PROTOCOL_BASE +27
#define _DEF_PROTOCOL_EXITROOM_RS   _DEF_PROTOCOL_BASE +28
//���
#define _register_username_exist    1
#define _register_success           2

#define _login_usename_noexist    0
#define _login_password_err       1
#define _login_success            2

#define _createroom_fail 0
#define _createroom_success 1

#define _selectroom_fail 0
#define _selectroom_success 1

#define _readyplay_wait 0
#define _readyplay_start 1
//��Ϣ
#define UM_LOGINMSG WM_USER +1
#define UM_REGISTERMsg WM_USER +2
#define UM_CREATEROOMMSG WM_USER +3
#define UM_GETROOMLISTMSG WM_USER +4
#define UM_STARTGAMEMSG WM_USER +5
#define UM_EXITROOMMSG WM_USER +6
#define UM_SELECTROOMMSG WM_USER +7
#define UM_UPDATEROOMSTATEMSG WM_USER +8

//��ʱ��ID
#define TIMER1 1
#define TIMER2 2
#define TIMER3 3

struct Card  
{
	int Num;//������Ŀ 2-10 J=11 Q=12 K=13 A=1 Jok(С)=14 Jok(��)=15 ����15��ʾ���Ʋ�����
	int Pow;//�Ƶ�ʵ�ʴ�С�����綷������2�ͱ�A��
			//3-10 J Q  K  A  2  JoС Jo��
			//1-8  9 10 11 12 13 14   15
	int Type;//�Ƶ����� ����=0 ����=1 ÷��=2 ����=3
	bool Click;//�����ѡ�ֵ��ƽ���true��û��ѡ����false
};
//������Ϣ
struct RoomState
{
	char m_szRoomName[_DEF_SIZE];
	long long m_roomid;

	char PlayName[3][_DEF_SIZE];
	Card PlayCards[3][20];//���20����
	int PlayerMain;//����
	Card OutCards[20];//�ߵ��ƣ�һ��Ҳ����20����
	int OutPlayer;//���Ƶ����
	Card Sendleft[3];//��¼ʣ�µ�3����
	int Game_State;
	int Power;//���㵱ǰ��Ϸ���ũ��ʤ����ÿ�˵õķ�
	int PlayerMaininfo;//��¼�м������ѡ��������� �������������Ϸ����

	int u_num;//��������
};

//Э���
struct STRU_REGISTERRQ
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
	char      m_szPassword[_DEF_SIZE];
};


typedef struct STRU_REGISTERRS
{
	PackType m_nType;
	char      m_bResult;
}STRU_LOGINRS;

//��¼
struct STRU_LOGINRQ
{
	PackType m_nType;
	char      m_szName[_DEF_SIZE];
	char      m_szPassword[_DEF_SIZE];
};


struct STRU_GETROOMINFORQ
{
	PackType m_nType; 
};


struct STRU_GETROOMINFORS
{
	PackType m_nType; 
	RoomState m_crs;
};



struct STRU_CREATEROOMINFORQ
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
	char      m_szRoomName[_DEF_SIZE];
};

struct STRU_CREATEROOMINFORS
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
	int       m_num;
	char      m_szResult;
};

struct RoomInfo
{
	int       m_RoomID;
	char      m_szName[_DEF_SIZE];    //������
	int       m_RoomNum;              //��������
};


struct STRU_GETROOMLISTRQ
{
	PackType m_nType; 
};

struct STRU_GETROOMLISTRS
{
	PackType m_nType; 
    RoomInfo m_RoomInfo[_DEF_NUM];
	int        m_nNum;               //������
};


typedef  struct STRU_SELECTROOMRQ
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
	long     long m_roomid;
}STRU_QUITAUTHORRQ;

typedef struct STRU_SELECTROOMRS
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
	int       m_num;
	char      m_szResult;
	RoomState m_crs;

}STRU_QUITAUTHORRS;

struct STRU_READYPLAYRQ
{
	PackType m_nType; 
	char      m_szName[_DEF_SIZE];
};

struct STRU_READYPLAYRS
{
	PackType m_nType; 
	char      m_szResult;
	char      m_szName[2][_DEF_SIZE];
};

//�Կ�������
struct STRU_SORTCARDRQ
{
	PackType m_nType; 
};

struct STRU_SORTCARDRS
{
	
	PackType m_nType; 
};

struct STRU_UPDATECARDRQ
{
	PackType m_nType;
	RoomState m_crs;
};

struct STRU_UPDATECARDRS
{
	PackType m_nType;

};




struct STRU_GAMEGOINGRQ
{
	PackType m_nType;
	int gamestate;
	int action;
	char tem1[22],tem2[22],tem3[22],tem0[22];
	char outcard[22];
	int nplaymain;
};

struct STRU_GAMEGOINGRS
{
	PackType m_nType;
	int gamestate;
	int action;
	char tem1[22],tem2[22],tem3[22],tem0[22];
	char outcard[22];
	int nplaymain;
};

struct STRU_EXITROOMRQ
{
	PackType m_nType;
	
};

struct STRU_EXITROOMRS
{
	PackType m_nType;
};

struct STRU_GAMEOVERRQ
{
	PackType m_nType;
	
};

struct STRU_GAMEOVERRS
{
	PackType m_nType;
	int Game_State;
	int PlayerMain;
};

struct STRU_SENDCARDSRQ
{
	PackType m_nType;
	int m_gamestate;
	int action;
	char outcard[22];
};

struct STRU_SENDCARDSRS
{
	PackType m_nType;
	int m_gamestate;
	int action;
	char outcard[22];
};

#endif