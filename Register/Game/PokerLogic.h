#pragma once
#include <list>
#include "Packdef.h"
#include "GameInterface.h"
#include <functional>

using namespace Player;
class CPokerLogic:public CGameInterface
{
	typedef std::vector<Poker> MyPoker;
public:
	static CPokerLogic & GetInstance();
	~CPokerLogic(void);
	int  SelectPoker(const CPoint & point);
	bool SelectMutiPoker(const Rect & region);
	void FinishMutiSelect();
	std::array<pImage,55> poker_img;
	Rect GetHandCardRect(const PlayerPosition pos=Self) const ;
	CardArray OurPlayCards();		//我方出牌
	void MatePlayCards(const CardArray & card_arr,const PlayerPosition pos);	//对方出牌
	void SetPlayerPoker(const vector<char> & cards,const char self_num);	//分配扑克
	void SetPlayerPoker(const PokerGroup & cards,const char self_num);	//分配扑克
	void SetLandlord(const PlayerPosition pos);
private:
	void RemoveAndCopy(MyPoker & input,MyPoker & output,std::function<bool(Poker & m)> fun);
	MyPoker GetCheckedCards() const;
	CardArray GetCardsNeedSend() const ;
	void DelCheckedCards();	//删除选中的卡片
	void SortHand();
	ArrayType IsLegalOutput() const;
	bool IsLegalOutput(MyPoker & poker,ArrayType & arrtype) const;
	unsigned char CalArrPoint(const MyPoker & cards,const ArrayType type ) const;
	Rect GetMateCardRect(const PlayerPosition pos,const int size) const;
	Rect GetSelfFirstCardRect(const int size) const;
	Rect GetSelfLastCardRect() const;
	std::array<Rect,3> GetLastRoundCardsFirstRect() const;
	bool IsBomb(const MyPoker & cards) const;
	bool Is3with1(const MyPoker & cards) const;
	bool Is3with2(const MyPoker & cards) const;
	bool Is4with2(const MyPoker & cards) const;
	bool IsStraight(const MyPoker & cards) const;
	bool IsDoubleStraight(const MyPoker & cards) const;
	bool IsTripleStraight(const MyPoker & cards) const;
	bool IsPlane(const MyPoker & cards) const;
	bool IsGreater(const CardArray & self, const CardArray & per ) const;
	int  GetCardFormCount(const MyPoker & cards,int count) const;//获得的数量为count的牌最大点数
	void MergeSortedVec(MyPoker & vec1,MyPoker & vec2);
	void ShowHandPoker(Graphics * const g) const ;
	void ShowDealingCardsEffect(Graphics * const g,const int timer) const;	//发牌效果
	void ShowLandlordCards(Graphics * const g,bool hide=true) const ;
	void ShowLastRoundPoker(Graphics * const g) const;
	void RepaintCardRegion() const;
	void RepaintLastRoundCards(const PlayerPosition pos) const;
private:
	const Size card_size;
	const int card_interval;
	const int card_up;
	const Point self_poker_center;
	static CPokerLogic * self_instance;
	CPokerLogic(void);
	MyPoker hand_poker[3],poker_landlord;
	MyPoker last_round_poker[3]; //上一手牌
	CardArray per_player_cards;
private:
	void OnFrame() override;
	void OnPaint(Gdiplus::Graphics * const g) const override;
	void OnGameStateChange(const GameState game_state) override;
};

