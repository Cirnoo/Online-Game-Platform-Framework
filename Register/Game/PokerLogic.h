#pragma once
#include <list>
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
	static CPokerLogic & GetInstance();
	~CPokerLogic(void);
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void FinishSelect();
	void ShowHandPoker(Gdiplus::Graphics *  g) const ;
	void ShowDealingCardsEffect(Gdiplus::Graphics *  g,const int timer) const;
	void ShowFinalThreeCards(Gdiplus::Graphics *  g) const ;
	void ShowLastRoundPoker(Gdiplus::Graphics *  g) const;
	vector<pImage> poker_img;
	bool IsLegalOutput();
	MyPoker GetCheckedCards() const;
	CardArray GetCardsNeedSend() const ;
	Rect GetHandCardRect() const ;
	void DelCheckedCards();	//�ҷ�����
	void DelMateCards(const vector<char> & cards,const PlayerPosition pos);	//�Է�����
	void SetPlayerPoker(const vector<char> & cards,const char self_num);	//�����˿�
	void SortHand();
	void SetLandlord(const PlayerPosition pos);
private:
	static CPokerLogic * self_instance;
	CPokerLogic(void);
	MyPoker hand_poker[3],poker_landlord;
	MyPoker last_round_poker[3]; //��һ����
	unsigned char CalArrPoint(const MyPoker & cards,const ArrayType type );
	Rect GetMateCardRect(PlayerPosition pos,const int size) const;
	Rect GetFirstCardRect(const int size) const;
	Rect GetLastCardRect() const;
	ArrayType arrtype;
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

