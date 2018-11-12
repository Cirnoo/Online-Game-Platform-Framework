#include "stdafx.h"
#include "PokerLogic.h"
#include <algorithm>
#include "GameDlg.h"
typedef std::vector<Poker> MyPoker;
CPokerLogic * CPokerLogic::self_instance=nullptr;
CPokerLogic & CPokerLogic::GetInstance()
{
	if (!self_instance)
	{
		self_instance=new CPokerLogic;
	}
	return *self_instance;
}
CPokerLogic::CPokerLogic(void)
	:card_interval(25),card_up(20),
	card_size(Size(57*1.4,80*1.4)),  //牌的长宽
	self_poker_center(GAME_DLG_WIDTH/2-card_size.Width/2,GAME_DLG_HEIGHT-250) //中间手牌位置
{
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);  //行列切割
	poker_img.resize(55);
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<13;j++)
		{
			poker_img[13*i+j]=temp[14*i+j];
		}
	}
	for (int i=0;i<2;i++)
	{
		poker_img[52+i]=temp[13+14*i];
	}
	poker_img.back()=temp[13+14*2];  //背面牌


}


CPokerLogic::~CPokerLogic(void)
{
	
	self_instance=nullptr;
}


unsigned char CPokerLogic::CalArrPoint(const MyPoker & cards,ArrayType type)
{
	if (cards.empty()||type==无)
	{
		return 0;
	}
	switch (type)
	{
	case 单牌   :
	case 对子   :
	case 三张   :
	case 顺子   :
	case 双顺   :
	case 三顺   :
		return cards.front().GetPointVal();		//直接比较最前的牌大小
	case 三带一 :
	case 三带对 :
	case 飞机   :
		return GetCardFormCount(cards,3);
	case 四带二 :
	case 炸弹   :
		return GetCardFormCount(cards,4);
	case 王炸   :
		return UCHAR_MAX;
	default:
		break;
	}
	return 0;
}

Rect CPokerLogic::GetMateCardRect(const PlayerPosition pos,const int size) const
{
	int width=GAME_DLG_WIDTH;
	int height=GAME_DLG_HEIGHT;
	switch(pos)
	{
	case Left:
		return Rect(Point(200,height*0.35-size*card_up/2),card_size);
	case Right:
		return Rect(Point(width-200-card_size.Width,height*0.35-size*card_up/2),card_size);
	default:
		ASSERT(0);
	}
}



Rect CPokerLogic::GetFirstCardRect(const int size) const 
{
	auto p=self_poker_center;
	p.X-=size*card_interval*0.5;
	return Rect(p,card_size);
}

Rect CPokerLogic::GetLastCardRect() const
{
	const auto size=hand_poker[Self].size();
	auto rect=GetFirstCardRect(size);
	rect.X+=(hand_poker[Self].size()-1)*card_interval;
	return rect;
}



Rect CPokerLogic::GetHandCardRect() const
{
	auto left_rect=GetFirstCardRect(hand_poker[Self].size());
	auto width=GetLastCardRect().GetRight()-left_rect.GetLeft();
	return Rect(left_rect.GetLeft(),left_rect.GetTop()-card_up,width,left_rect.Height+card_up);

}

void CPokerLogic::DelCheckedCards()
{
	auto self_poker=hand_poker[Self];
	last_round_poker[Self].clear();
	for (auto i=self_poker.begin();i!=self_poker.end();)
	{
		if (i->check)
		{
			last_round_poker[Self].push_back(*i);
			i=self_poker.erase(i);
		}
		else
		{
			i++;
		}
	}
	if (self_poker.empty())
	{
		//游戏胜利
		AfxGetMainWnd()->PostMessageW(WM_GAME_WIN);
	}
}

void CPokerLogic::DelMateCards(const vector<char> & cards,const PlayerPosition pos)
{
	auto & vec_temp=hand_poker[pos];
	last_round_poker[pos].clear();
	bool buf[54]={false};
	for (const auto i:cards)
	{
		buf[i]=true;
	}
	for (auto i=vec_temp.begin();i!=vec_temp.end();)
	{
		if (buf[i->toNum()])
		{
			last_round_poker[pos].push_back(*i);
			i=vec_temp.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void CPokerLogic::SetPlayerPoker(const vector<char> & cards,const char self_num)
{
	ASSERT(self_num>=0&&self_num<3);
	MyPoker * poker_arr[3];
	MyPoker * temp_arr[4]={&hand_poker[Self],&hand_poker[Right],&hand_poker[Left],&poker_landlord};
	for (auto  i:temp_arr)
	{
		i->clear();
		i->reserve(20);
	}
	const char temp[]={0,1,2,0,1};
	int flag=self_num;
	/*for (int i=0;i<3;i++)
	{
		poker_arr[temp[flag++]]=temp_arr[i];
	}*/
	for (int i=0;i<3;i++)
	{
		int cur=temp[flag+i];
		bool hide_flag=cur==Self?false:true;
		for (int j=0;j<17;j++)
		{
			temp_arr[cur]->push_back(cards.at(i*17+j));
			temp_arr[cur]->back().hide=hide_flag;
		}
	}
	for (auto i=cards.rbegin();i<cards.rbegin()+3;i++)	//地主牌
	{
		poker_landlord.push_back(*i);
		poker_landlord.back().check=true;
		poker_landlord.back().hide=true;
	}
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
	for (auto i=hand_poker[Self].rbegin();i!=hand_poker[Self].rend();cnt++,i++)
	{
		auto temp_rect=right_rect;
		temp_rect.OffsetRect(-card_interval*cnt,-card_up*i->check);
		if (temp_rect.PtInRect(point))
		{
			i->check=!i->check;
			//TRACE("选中了第%d张牌",poker_in_hand.size()-cnt);
			break;
		}
	}
	return hand_poker[Self].size()-cnt;
}

bool CPokerLogic::SelectMutiPoker(const Rect & region)
{
	const auto hand_rect=GetHandCardRect();
	if (!region.IntersectsWith(hand_rect))
	{
		for (auto & i:hand_poker[Self])
		{
			i.select=false;
		}
		return false;
	}
	auto rect=GetFirstCardRect(hand_poker[Self].size());
	for(auto & i:hand_poker[Self])
	{
		auto temp=Rect(rect.GetLeft()+card_interval*0.3,rect.GetTop()-card_up*i.check+card_interval,
			card_size.Width*0.3,card_size.Height*0.5);//牌能够被选到的范围比实际小点
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

void CPokerLogic::FinishMutiSelect()
{
	for (auto & i:hand_poker[Self])
	{
		if (i.select)
		{
			i.select=false;
			i.check=!i.check;
		}
	}
}

void CPokerLogic::ShowHandPoker(Graphics * const g) const
{
	//自己的手牌
	auto rect=GetFirstCardRect(hand_poker[Self].size());
	for(const auto & i:hand_poker[Self])
	{
		rect.Y-=card_up*i.check;
		g->DrawImage(poker_img[i.toNum()],rect);
		if (i.select)
		{
			SolidBrush brush(Color(100,46,156,209));
			g->FillRectangle(&brush,rect);
		}
		rect.Offset(card_interval,card_up*i.check);
	}


	const int interval = card_up;
	const auto & back_img=poker_img[54];
	for (int i=Right;i<=Left;i++)
	{
		const auto & hand=hand_poker[i];
		rect=GetMateCardRect((PlayerPosition)i,hand.size());
		for (const auto & j:hand)
		{
			g->DrawImage(j.hide?back_img:poker_img[j.toNum()],rect);
			rect.Y+=interval;
		}
	}
	
}

void CPokerLogic::ShowDealingCardsEffect(Graphics * const g,const int timer) const
{
	const int size=min(timer,17);
	auto rect=GetFirstCardRect(size);
	const auto & back_img=poker_img[54];
	for(int i=0;i<size;i++)
	{
		if (timer>18)
		{
			g->DrawImage(back_img,rect);
		}
		else
		{
			g->DrawImage(poker_img[hand_poker[Self][i].toNum()],rect);
		}
		rect.Offset(card_interval,0);
	}
	const int interval = card_up;
	
	for (int i=Right;i<=Left;i++)
	{
		rect=GetMateCardRect((PlayerPosition)i,size);
		for(int i=0;i<size;i++)
		{
			g->DrawImage(back_img,rect);
			rect.Y+=interval;
		}
	}
	
}

void CPokerLogic::ShowLandlordCards(Graphics * const  g,bool hide) const
{
	Rect rect(Point(GAME_DLG_WIDTH/2-card_size.Width*1.5-13,60),card_size);
	const auto back_img=poker_img.back();
	for (const auto & i:poker_landlord)
	{
		g->DrawImage(hide?back_img:poker_img[i.toNum()],rect);
		rect.X+=card_size.Width+5;
	}
}

void CPokerLogic::ShowLastRoundPoker(Graphics * const g) const
{
	Rect rect[3];
	rect[Self]=GetFirstCardRect(last_round_poker[Self].size());
	rect[Self].Y-=card_size.Height+20;

	rect[Right]=GetMateCardRect(Right,last_round_poker[Right].size());
	rect[Right].X+=card_size.Width+20;
	
	rect[Left]=GetMateCardRect(Left,last_round_poker[Left].size());
	rect[Left].Y-=card_size.Width+20;
	for(int i=Self;i<=Left;i++)
	{
		for (const auto & j:last_round_poker[i])
		{
			g->DrawImage(poker_img[j.toNum()],rect[i]);
		}
	}
}

bool CPokerLogic::IsLegalOutput()
{
	
	MyPoker cd=GetCheckedCards();
	switch (cd.size())
	{
	case 0:
		break;
	case 1: //单牌
		arrtype=单牌;
		return true;
	case 2: //对子 王炸
		return (arrtype=对子, cd.front()==cd.back() )||
			(arrtype=王炸,cd[0].c_type==CardType::Joker&&cd[1].c_type==CardType::Joker);

	case 3: //三张
		return (arrtype=三张, cd.front()==cd.back());
	case 4: //炸弹 三带一
		return (arrtype=炸弹, IsBomb(cd)) || (arrtype=三带一, Is3with1(cd) );
	case 5: //三带对 顺子
		return (arrtype=三带对, Is3with2(cd) )||(arrtype=顺子, IsStraight(cd) );
	case 6: //顺子 双顺 三顺 四带二
	default: //顺子 双顺 三顺 四带二 飞机 
		return (arrtype=顺子, IsStraight(cd) ) 
			|| (arrtype=双顺, IsDoubleStraight(cd) )
			|| (arrtype=三顺, IsTripleStraight(cd) )
			|| (arrtype=四带二, Is4with2(cd) )
			|| (arrtype=飞机, IsPlane(cd) );
		return true;
	}
	arrtype=无;
	return false;
}

MyPoker CPokerLogic::GetCheckedCards() const
{
	MyPoker cards;
	for (const auto & i:hand_poker[Self])
	{
		if (i.check)
		{
			cards.push_back(i);
		}
	}
	return cards;
}

CardArray CPokerLogic::GetCardsNeedSend() const
{
	return CardArray(GetCheckedCards(),arrtype,1);
}

void CPokerLogic::SortHand()
{
	for (int i=Self;i<=Left;i++)
	{
		sort(hand_poker[i].begin(),hand_poker[i].end(),
			[](Poker & a, Poker & b)->bool 
		{
			return a.point>b.point;     
			//每种花色13张，52和53分别为小王大王
		});
	}
}

void CPokerLogic::SetLandlord(const PlayerPosition pos)
{
	/*for (auto & i:poker_landlord)
	{
	hand_poker[pos].push_back(i);
	}
	poker_landlord.clear();
	sort(hand_poker[pos].begin(),hand_poker[pos].end(),
	[](Poker & a,Poker & b)->bool {return a.GetPointVal()>b.GetPointVal();});*/
	MergeSortedVec(hand_poker[pos],poker_landlord);
}



bool CPokerLogic::IsBomb(const MyPoker & cards)const
{
	return cards.front()==cards.back()&&cards.size()==4;
}

bool CPokerLogic::Is3with1(const MyPoker & cards) const
{
	return cards[0]==cards[2]||cards[1]==cards[3];
}

bool CPokerLogic::Is3with2(const MyPoker & cards) const
{
	return (cards[0]==cards[2]&&cards[3]==cards[4]) //对子在后
		||
		(cards[2]==cards[4]&&cards[0]==cards[1]); //对子在前
}

bool CPokerLogic::Is4with2(const MyPoker & cards) const
{
	for (int l=0,r=l+3;r<cards.size();l++,r++)
	{
		if (cards[l]==cards[r])  //l和r之间为炸
		{
			if (cards.size()==6)  //4带2单牌
			{
				return true;
			}
			else if (cards.size()==8) //4带2对
			{
				char temp=0;
				for (const auto & i:cards)
				{
					temp^=i.GetPointVal();
				}
				return temp==0;
			}
			break;
		}
	}
	return false;
	
}

bool CPokerLogic::IsStraight(const MyPoker & cards) const
{
	if (cards.front().GetPointVal()>=(char)PokerPoints::Two)
	{
		return false;  //顺子不能有2和王
	}
	for (auto i=cards.begin();i!=cards.end()-1;i++)
	{
		if (i->GetPointVal()-1!=(i+1)->GetPointVal())
		{
			return false;
		}
	}
	return true;
}

bool CPokerLogic::IsDoubleStraight(const MyPoker & cards) const
{
	if (cards.size()<6)
	{
		return false;
	}
	MyPoker vec1,vec2;
	bool flag=true;
	for (const auto & i:cards)
	{
		(flag?vec1:vec2).push_back(i);
		flag=!flag;
	}
	return vec1==vec2&& IsStraight(vec1) && IsStraight(vec2);
}

bool CPokerLogic::IsTripleStraight(const MyPoker & cards) const
{
	MyPoker vec[3];
	if (cards.size()%3!=0)
	{
		return false;
	}
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

bool CPokerLogic::IsPlane(const MyPoker & cards) const
{
	char temp[15]={0};
	for (const auto i:cards)
	{
		temp[i.GetPointVal()]++;
	}
	vector<char> plane;
	vector<char> wing;  //飞机带翅膀
	for (const auto i:temp)
	{
		(i==3?plane:wing).push_back(i);
	}
	const auto wing_size=cards.size()-plane.size()*3;
	if (plane.size()==wing.size()&&		//飞机和翅膀个数相同
		(wing.size()==wing_size		    //带的都是单牌
		||wing.size()*2==wing_size))		//都是对子
	{
		return true;
	}
	return false;
}

bool CPokerLogic::IsGreater(const CardArray & self, const CardArray & per) const
{
	if (per.type==王炸)
	{
		return false;
	}
	else if (per.type==self.type)		//牌型相同 比大小 和牌数
	{
		return per.num==self.num && self.point>per.point;
	}
	else
	{
		return self.type==炸弹||self.type==王炸;
	}
}

int CPokerLogic::GetCardFormCount(const MyPoker & cards,int count) const
{
	char temp[12]={0};
	for(const auto & i:cards)
	{
		if (++temp[i.GetPointVal()]==count)
		{
			return i.GetPointVal();
		}
	}
	ASSERT(0);
}

void CPokerLogic::MergeSortedVec(MyPoker & vec1,MyPoker & vec2)
{
	int i1=vec1.size()-1;
	int i2=vec2.size()-1;
	vec1.resize(i1+i2+1);
	int icur=i1+i2-1;
	while (i1>=0&&i2>=0)
	{
		vec1[icur--]=vec1[i1].GetPointVal()>=vec2[i2].GetPointVal()?vec1[i1--]:vec2[i2--];
	}
	while(i2>=0)
	{
		vec1[icur--]=vec2[i2--];
	}
}

void CPokerLogic::OnFrame()
{
	const auto game_state=theApp.game_action.GetGameState();
	switch (game_state)
	{
	case GameState::Wait:		
		timer=-1;
		return;
	case GameState::GetCards:		//发牌阶段
		if (timer>=3*21)
		{
			timer=0;
			SortHand();
			theApp.game_action.SetGameState(GameState::SelectLandLord);		//发牌完毕
		}
		break;
	default:
		break;
	}
}

void CPokerLogic::OnPaint(Gdiplus::Graphics * const g) const
{
	const auto game_state=theApp.game_action.GetGameState();
	const int deal_card_cnt=timer/3;
	switch (game_state)
	{
	case GameState::Wait:

		break;
	case GameState::GetCards:
		ASSERT(deal_card_cnt<=21);
		ShowDealingCardsEffect(g,deal_card_cnt);		//发牌效果
		break;
	case GameState::SelectLandLord:
		ShowHandPoker(g);
		ShowLandlordCards(g);
		break;
	case GameState::Gaming:
		ShowHandPoker(g);
		ShowLandlordCards(g,false);
		ShowLastRoundPoker(g);
		break;
	case GameState::Over:
		break;
	default:
		break;
	}
}
