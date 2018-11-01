#pragma once
#include "Packdef.h"
typedef std::vector<Poker> MyPoker;
class CPokerLogic
{
public:
	CPokerLogic(void);
	~CPokerLogic(void);
	MyPoker poker_in_hand;
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void ShowHandPoker(Gdiplus::Graphics *  g);
	vector<pImage> poker_img;
	bool IsLegalOutput();
	MyPoker GetCheckedCards();
	CardArray GetCardsNeedSend();
	Rect GetHandCardRect();
	void DelCheckedCards();
private:
	unsigned char CalArrPoint(const MyPoker & cards,ArrayType type );
	Rect GetFirstCardRect();
	Rect GetLastCardRect();
	ArrayType arrtype;
	void SortHand();
	Size card_size;
	const int card_interval;
	const int card_up;
	Point poker_center;
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

