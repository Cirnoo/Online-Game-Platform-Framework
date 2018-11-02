#pragma once
#include "Packdef.h"
namespace Player
{
	enum PlayerPosition
	{
		Self,Right,Left
	};
}

using namespace Player;

typedef std::vector<Poker> MyPoker;
class CPokerLogic
{
public:
	CPokerLogic(void);
	~CPokerLogic(void);
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void ShowHandPoker(Gdiplus::Graphics *  g);
	vector<pImage> poker_img;
	bool IsLegalOutput();
	MyPoker GetCheckedCards();
	CardArray GetCardsNeedSend();
	Rect GetHandCardRect();
	void DelCheckedCards();	//我方出牌
	void DelMateCards(const vector<char> & cards,const PlayerPosition pos);	//对方出牌
	void SetPlayerPoker(const vector<char> & cards,const char self_num);	//分配扑克
	MyPoker & GetSelfPoker();
private:
	MyPoker hand_poker[3],poker_master;
	unsigned char CalArrPoint(const MyPoker & cards,const ArrayType type );
	Rect GetMateCardRect(PlayerPosition pos);
	Rect GetFirstCardRect();
	Rect GetLastCardRect();
	ArrayType arrtype;
	void SortHand();
	const Size card_size;
	const int card_interval;
	const int card_up;
	const Point self_poker_center;
	bool IsBomb(const MyPoker & cards);
	bool Is3with1(const MyPoker & cards);
	bool Is3with2(const MyPoker & cards);
	bool Is4with2(const MyPoker & cards);
	bool IsStraight(const MyPoker & cards);
	bool IsDoubleStraight(const MyPoker & cards);
	bool IsTripleStraight(const MyPoker & cards);
	bool IsPlane(const MyPoker & cards);
	bool IsGreater(const CardArray & self, const CardArray & per );
	int  GetCardFormCount(const MyPoker & cards,int count);
};

