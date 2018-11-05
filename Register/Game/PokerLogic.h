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

class CPokerLogic
{
	typedef std::vector<Poker> MyPoker;
public:
	static CPokerLogic & GetInstance();
	~CPokerLogic(void);
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void FinishSelect();
	void ShowHandPoker(Graphics * const g) const ;
	void ShowDealingCardsEffect(Graphics * const g,const int timer) const;
	void ShowFinalThreeCards(Graphics * const g) const ;
	void ShowLastRoundPoker(Graphics * const g) const;
	vector<pImage> poker_img;
	bool IsLegalOutput();
	MyPoker GetCheckedCards() const;
	CardArray GetCardsNeedSend() const ;
	Rect GetHandCardRect() const ;
	void DelCheckedCards();	//我方出牌
	void DelMateCards(const vector<char> & cards,const PlayerPosition pos);	//对方出牌
	void SetPlayerPoker(const vector<char> & cards,const char self_num);	//分配扑克
	void SortHand();
	void SetLandlord(const PlayerPosition pos);
private:
	static CPokerLogic * self_instance;
	CPokerLogic(void);
	MyPoker hand_poker[3],poker_landlord;
	MyPoker last_round_poker[3]; //上一手牌
	unsigned char CalArrPoint(const MyPoker & cards,const ArrayType type );
	Rect GetMateCardRect(const PlayerPosition pos,const int size) const;
	Rect GetFirstCardRect(const int size) const;
	Rect GetLastCardRect() const;
	ArrayType arrtype;
	const Size card_size;
	const int card_interval;
	const int card_up;
	const Point self_poker_center;
	bool IsBomb(const MyPoker & cards) const;
	bool Is3with1(const MyPoker & cards) const;
	bool Is3with2(const MyPoker & cards) const;
	bool Is4with2(const MyPoker & cards) const;
	bool IsStraight(const MyPoker & cards) const;
	bool IsDoubleStraight(const MyPoker & cards) const;
	bool IsTripleStraight(const MyPoker & cards) const;
	bool IsPlane(const MyPoker & cards) const;
	bool IsGreater(const CardArray & self, const CardArray & per ) const;
	int  GetCardFormCount(const MyPoker & cards,int count) const;
};

