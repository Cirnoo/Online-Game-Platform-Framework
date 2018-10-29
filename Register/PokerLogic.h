#pragma once

typedef std::vector<Poker> MyPoker;
class CPokerLogic
{
public:
	CPokerLogic(void);
	~CPokerLogic(void);
	MyPoker poker_in_hand;
	Rect GetFirstCardRect();
	Rect GetLastCardRect();
	Rect GetHandCardRect();
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void DrawHandPoker(Gdiplus::Graphics *  g);
	vector<pImage> vec_poker;
	bool IsLegalOutput();
private:
	void SortHand();
	Size card_size;
	const int card_interval;
	const int card_up;
	Point poker_center;
	bool IsBomb(const MyPoker & cards);
	bool Is3with1(const MyPoker & cards);
	bool Is3with2(const MyPoker & cards);
	bool IsStraight(const MyPoker & cards);
	bool IsDoubleStraight(const MyPoker & cards);
	bool IsTripleStraight(const MyPoker & cards);
};

