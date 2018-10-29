#include "stdafx.h"
#include "PokerLogic.h"
#include <algorithm>

CPokerLogic::CPokerLogic(void):card_interval(25),card_up(20)
{
	auto m_width=720*1.4;
	auto m_height=540*1.4;
	card_size=Size(57,80);  //牌的长宽
	poker_center=Point(m_width/2-57,m_height-250); //中间手牌位置
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);  //行列切割
	vec_poker.resize(55);
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<13;j++)
		{
			vec_poker[13*i+j]=temp[14*i+j];
		}
	}
	for (int i=0;i<2;i++)
	{
		vec_poker[52+i]=temp[13+14*i];
	}
	vec_poker.back()=temp[13+14*2];  //背面牌
	for (int i=0;i<13;i++)
	{
		poker_in_hand.push_back(i);
	}
	poker_in_hand.push_back(52);
	poker_in_hand.push_back(53);
	SortHand();
}


CPokerLogic::~CPokerLogic(void)
{
}

Rect CPokerLogic::GetFirstCardRect()
{
	auto p=poker_center;
	p.X-=poker_in_hand.size()/2*card_interval;
	return Rect(p,card_size);
}

Rect CPokerLogic::GetLastCardRect()
{
	auto p=poker_center;
	p.X+=(poker_in_hand.size()-poker_in_hand.size()/2-1)*card_interval;
	return Rect(p,card_size);
}

Rect CPokerLogic::GetHandCardRect()
{
	auto left_rect=GetFirstCardRect();
	auto width=GetLastCardRect().GetRight()-left_rect.GetLeft();
	return Rect(left_rect.GetLeft(),left_rect.GetTop()-card_up,width,left_rect.Height+card_up);

}

int CPokerLogic::SelectPoker(const CPoint & point)
{
	const auto rect=Rect2CRect(GetHandCardRect());  //是否有选中牌
	if (!rect.PtInRect(point))
	{
		return -1;
	}
	const auto right_rect=Rect2CRect(GetLastCardRect());
	int cnt=0;
	for (auto i=poker_in_hand.rbegin();i!=poker_in_hand.rend();cnt++,i++)
	{
		auto temp_rect=right_rect;
		temp_rect.OffsetRect(-card_interval*cnt,0);
		temp_rect.OffsetRect(0,-card_up*i->check);
		if (temp_rect.PtInRect(point))
		{
			i->check=!i->check;
			TRACE("选中了第%d张牌",poker_in_hand.size()-cnt);
			break;
		}
	}
	return poker_in_hand.size()-cnt;
}

bool CPokerLogic::SelectMutiPoker(const Rect & region)
{
	const auto hand_rect=GetHandCardRect();
	if (!region.IntersectsWith(hand_rect))
	{
		return false;
	}
	auto rect=GetFirstCardRect();
	for(auto & i:poker_in_hand)
	{
		auto temp=Rect(rect.GetLeft()+card_interval/3,rect.GetTop()-card_up*i.check-card_interval/3,
			card_size.Width/3,card_size.Height*2/3);//牌能够被选到的范围比实际小点
		if (temp.IntersectsWith(region))
		{
			i.select=true;
		}
		else
		{
			i.select=false;
		}
		rect.Offset(card_interval,0);
	}
	return true;
}

void CPokerLogic::DrawHandPoker(Gdiplus::Graphics * g)
{
	auto rect=GetFirstCardRect();
	for(auto i:poker_in_hand)
	{
		auto temp=Rect(rect.GetLeft(),rect.GetTop()-card_up*i.check,card_size.Width,card_size.Height);
		g->DrawImage(vec_poker[i.toNum()],temp);
		if (i.select)
		{
			SolidBrush brush(Color(100,46,156,209));
			g->FillRectangle(&brush,temp);
		}
		rect.Offset(card_interval,0);
	}
}

bool CPokerLogic::IsLegalOutput()
{
	MyPoker cd;
	for (const auto & i:poker_in_hand)
	{
		if (i.check)
		{
			cd.push_back(i);
		}
	}
	switch (cd.size())
	{
	case 0:
	case 1: //单牌
		return true;
	case 2: //对子 王炸
		return cd.front()==cd.back() ||
			cd[0].c_type==CardType::Joker&&cd[1].c_type==CardType::Joker;

	case 3: //三张
		return cd.front()==cd.back();
	case 4: //炸弹 三带一
		return IsBomb(cd)||Is3with1(cd);
	case 5: //三带对 顺子
		return Is3with2(cd)||IsStraight(cd);
	case 6: //顺子 双顺 三顺

	default:
		return true;
	}
	
}

void CPokerLogic::SortHand()
{
	sort(poker_in_hand.begin(),poker_in_hand.end(),
		[](Poker a, Poker b)->bool 
	{
		return a.point>b.point;     
		//每种花色13张，52和53分别为小王大王
	});
}

bool CPokerLogic::IsBomb(const MyPoker & cards)
{
	return cards.front()==cards.back();
}

bool CPokerLogic::Is3with1(const MyPoker & cards)
{
	return cards[0]==cards[2]||cards[1]==cards[3];
}

bool CPokerLogic::Is3with2(const MyPoker & cards)
{
	return (cards[0]==cards[2]&&cards[3]==cards[4]) //对子在后
		||
		(cards[2]==cards[4]&&cards[0]==cards[1]); //对子在前
}

bool CPokerLogic::IsStraight(const MyPoker & cards)
{
	auto first_card=cards.front();
	if ((char)cards.front().point>=(char)PokerPoints::Two)
	{
		return false;  //顺子不能有2和王
	}
	return cards.back()-cards.front()==cards.size()-1;
}

bool CPokerLogic::IsDoubleStraight(const MyPoker & cards)
{
	MyPoker vec1,vec2;
	bool flag=true;
	for (const auto & i:cards)
	{
		(flag?vec1:vec2).push_back(i);
		flag=!flag;
	}
	return vec1==vec2&& IsStraight(vec1) && IsStraight(vec2);
}

bool CPokerLogic::IsTripleStraight(const MyPoker & cards)
{
	MyPoker vec[3];
	for (int i=0;i<cards.size();i++)
	{
		vec[i%3].push_back(cards[i]);
	}
	if (vec[0]==vec[1]&&vec[0]==vec[2])
	{
		for (const auto & i:vec)
		{
			if (!IsStraight(i))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
