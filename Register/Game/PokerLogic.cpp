#include "stdafx.h"
#include "PokerLogic.h"
#include <algorithm>
#include "GameDlg.h"
typedef std::vector<Poker> MyPoker;
CPokerLogic * CPokerLogic::self_instance=nullptr;
CPokerLogic & CPokerLogic::GetInstance()
{
	if(!self_instance)
	{
		lock.lock();
		if (!self_instance)
		{
			self_instance=new CPokerLogic;
		}
		lock.unlock();
	}
	return *self_instance;
}
CPokerLogic::CPokerLogic(void)
	:card_interval(25),card_up(20),
	card_size(Size(57*1.4,80*1.4)),  //牌的长宽
	self_poker_center(GAME_DLG_WIDTH/2-card_size.Width/2,GAME_DLG_HEIGHT-240) //中间手牌位置
{
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);  //行列切割
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




unsigned char CPokerLogic::CalArrPoint(const MyPoker & cards,const ArrayType type) const
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
		return Rect(Point(190,height*0.35-size*card_up/2),card_size);
	case Right:
		return Rect(Point(width-190-card_size.Width,height*0.35-size*card_up/2),card_size);
	default:
		ASSERT(0);
	}
}



Rect CPokerLogic::GetSelfFirstCardRect(const int size) const 
{
	auto p=self_poker_center;
	p.X-=size*card_interval*0.5;
	return Rect(p,card_size);
}

Rect CPokerLogic::GetSelfLastCardRect() const
{
	const auto size=hand_poker[Self].size();
	auto rect=GetSelfFirstCardRect(size);
	rect.X+=(hand_poker[Self].size()-1)*card_interval;
	return rect;
}



std::array<Rect,3> CPokerLogic::GetLastRoundCardsFirstRect() const
{
	std::array<Rect,3> rect;
	rect[Self]=GetSelfFirstCardRect(last_round_poker[Self].size());
	rect[Self].Y-=card_size.Height+20;

	rect[Right]=GetMateCardRect(Right,last_round_poker[Right].size());
	rect[Right].X-=card_size.Width+20;

	rect[Left]=GetMateCardRect(Left,last_round_poker[Left].size());
	rect[Left].X+=card_size.Width+20;
	return rect;
}

Rect CPokerLogic::GetHandCardRect(const PlayerPosition pos) const
{
	if(pos==Self)
	{
		auto && left_rect=GetSelfFirstCardRect(hand_poker[Self].size());
		auto && width=GetSelfLastCardRect().GetRight()-left_rect.GetLeft();
		return Rect(left_rect.GetLeft(),left_rect.GetTop()-card_up,width,left_rect.Height+card_up);
	}
	else
	{
		auto && top_rect=GetMateCardRect(pos,hand_poker[pos].size());
		auto  height = hand_poker[pos].size()*card_up;
		return Rect(top_rect.GetLeft(),top_rect.GetTop(),card_size.Width,height);
	}
	
}

void CPokerLogic::DelCheckedCards()
{
	auto & self_poker=hand_poker[Self];
	auto & last_self_poker=last_round_poker[Self];

	RemoveAndCopy(self_poker,last_self_poker,[](Poker & m)->bool {return m.check;});

	if (self_poker.empty())
	{
		//游戏胜利
		AfxGetMainWnd()->PostMessageW(WM_GAME_WIN);
	}
}

void CPokerLogic::MatePlayCards(const CardArray & card_arr,const PlayerPosition pos)
{
	last_round_poker[pos].clear();
	auto & last_poker=last_round_poker[pos];
	if (card_arr.IsEmpty())
	{
		return;
	}
	const auto cards=card_arr.toVecChar();
	per_player_cards=card_arr;
	auto & vec_temp=hand_poker[pos];
	bool buf[54]={false};
	for (const auto i:cards)
	{
		buf[i]=true;
	}
	RemoveAndCopy(vec_temp,last_poker,[&buf](Poker & m){return buf[m.toNum()];});
	RepaintLastRoundCards(pos);
}

void CPokerLogic::SetPlayerPoker(const vector<char> & cards,const char self_num)
{
	ASSERT(self_num>=0&&self_num<3);
	MyPoker * poker_arr[3];
	for (auto & i:hand_poker)
	{
		i.clear();
		i.reserve(20);
	}
	for (int i=0;i<3;i++)
	{
		int cur=theApp.game_action.SerialNum2Pos(i);
		bool hide_flag=cur==Self?false:true;
		for (int j=0;j<17;j++)
		{
			hand_poker[cur].push_back(cards.at(i*17+j));
			hand_poker[cur].back().hide=hide_flag;
		}
	}
	for (auto i=cards.rbegin();i<cards.rbegin()+3;i++)	//地主牌
	{
		poker_landlord.push_back(*i);
		poker_landlord.back().check=true;
		poker_landlord.back().hide=true;
	}
}



void CPokerLogic::SetPlayerPoker(const PokerGroup & cards,const char self_num)
{
	const char * temp=&cards[0];
	SetPlayerPoker(vector<char>(temp,temp+cards.size()),self_num);
}

int CPokerLogic::SelectPoker(const CPoint & point)
{
	const GameState game_state=theApp.game_action.GetGameState();
	if (game_state!=GameState::OurPlay && game_state!=GameState::OtherPlay )
	{
		return -1;
	}
	const auto rect=Rect2CRect(GetHandCardRect());  //是否有选中牌
	if (!rect.PtInRect(point))
	{
		return -1;
	}
	const auto right_rect=Rect2CRect(GetSelfLastCardRect());
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
	const GameState game_state=theApp.game_action.GetGameState();
	if (game_state!=GameState::OurPlay && game_state!=GameState::OtherPlay )
	{
		return false;
	}
	const auto hand_rect=GetHandCardRect();
	if (!region.IntersectsWith(hand_rect))
	{
		for (auto & i:hand_poker[Self])
		{
			i.select=false;
		}
		return false;
	}
	auto rect=GetSelfFirstCardRect(hand_poker[Self].size());
	for(auto & i:hand_poker[Self])
	{
		auto temp=Rect(rect.GetLeft()+card_interval*0.3,rect.GetTop()-card_up*i.check+card_interval,
			card_size.Width*0.3,card_size.Height*0.5);//牌能够被选到的范围比实际小点
		if (temp.IntersectsWith(region))
		{
			if(i.select!=true)
			{
				i.select=true;
				AfxGetMainWnd()->InvalidateRect(Rect2CRect(rect));
			}
		}
		else if(i.select!=false)
		{
			AfxGetMainWnd()->InvalidateRect(Rect2CRect(rect));
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
	auto rect=GetSelfFirstCardRect(hand_poker[Self].size());
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
	auto rect=GetSelfFirstCardRect(size);
	const auto & back_img=poker_img[54];
	
	for(int i=0;i<size;i++)
	{
		const auto & img=timer>18
			?back_img
			:poker_img[hand_poker[Self][i].toNum()];
		g->DrawImage(img,rect);
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
	const Size size(card_size.Width*0.9,card_size.Height*0.9);
	Rect rect(Point(GAME_DLG_WIDTH/2-size.Width*1.5-8,60),size);
	const auto back_img=poker_img.back();
	for (const auto & i:poker_landlord)
	{
		g->DrawImage(hide?back_img:poker_img[i.toNum()],rect);
		rect.X+=size.Width+8;
	}
}

void CPokerLogic::ShowLastRoundPoker(Graphics * const g) const
{
	auto rect=GetLastRoundCardsFirstRect();
	for(int i=Self;i<=Left;i++)
	{
		const int dx=i==Self?card_interval:0;
		const int dy=i==Self?0:card_up;
		for (const auto & j:last_round_poker[i])
		{
			g->DrawImage(poker_img[j.toNum()],rect[i]);
			rect[i].Offset(dx,dy);
		}
	}
}

void CPokerLogic::RepaintCardRegion() const
{
	for (int i=Self;i<=Left;i++)
	{
		AfxGetMainWnd()->InvalidateRect(Rect2CRect(GetHandCardRect(PlayerPosition(i))),FALSE);
	}
}

void CPokerLogic::RepaintLastRoundCards(const PlayerPosition pos) const
{
	auto rect=GetLastRoundCardsFirstRect();
	int size=last_round_poker[pos].size();
	if (pos==Self)
	{
		rect[Self].Width=rect[Self].Width+(size-1)*card_interval;
	}
	else
	{
		rect[pos].Height=rect[pos].Height+(size-1)*card_up;
	}
	AfxGetMainWnd()->InvalidateRect(Rect2CRect(rect[pos]));
	
}

ArrayType CPokerLogic::IsLegalOutput() const
{
	ArrayType arrtype;
	IsLegalOutput(GetCheckedCards(),arrtype);
	return arrtype;
}

bool CPokerLogic::IsLegalOutput(MyPoker & cd,ArrayType & arrtype) const
{
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

void CPokerLogic::RemoveAndCopy(MyPoker & input,MyPoker & output,std::function<bool(Poker & m)> fun)
{
	output.clear();
	input.erase(remove_if(input.begin(),input.end(),
		[&output,&fun](Poker & m)
	{
		return fun(m)?output.push_back(m),true:false;
	}),input.end()); 
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
	const auto && checked_poker = GetCheckedCards();
	const auto arrtype=IsLegalOutput();
	auto arr_point = CalArrPoint(checked_poker,arrtype);
	return CardArray(checked_poker,arrtype,arr_point);
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
	auto temp=poker_landlord;
	sort(temp.begin(),temp.end(),
		[](Poker & a,Poker & b){return a.GetPointVal()>b.GetPointVal();});
	MergeSortedVec(hand_poker[pos],temp);
}



CardArray CPokerLogic::OurPlayCards()
{
	CardArray && our_cards=GetCardsNeedSend();
	if (our_cards.type!=无 && IsGreater(our_cards,per_player_cards))
	{
		//合法的出牌	
		DelCheckedCards();
		per_player_cards.Clear();	//清除上一手牌
		AfxGetMainWnd()->InvalidateRect(Rect2CRect(GetHandCardRect()));
		//重绘出牌
		RepaintLastRoundCards(Self);

		//发送牌数据包
		//TRACE("出牌类型:%d\n",our_cards.type);
		return our_cards;
	}
	else
	{
		throw "invalid play";
	}
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
	if (per.IsEmpty())
	{
		return true;
	}
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
	vec1.resize(i1+i2+2);
	int icur=vec1.size()-1;
	while (i1>=0&&i2>=0)
	{
		vec1[icur--]=vec1[i1].GetPointVal()<=vec2[i2].GetPointVal()?vec1[i1--]:vec2[i2--];
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
			GameState st=theApp.game_action.GetCurActPlayerPos()==Self
				?GameState::CallLandLord
				:GameState::OtherCall;
			theApp.game_action.SetGameState(st);		//发牌完毕
		}
		RepaintCardRegion();
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
	case GameState::CallLandLord:
	case GameState::RobLandlord:
	case GameState::OtherCall:
		ShowHandPoker(g);
		ShowLandlordCards(g);
		break;
	case GameState::OurPlay:
	case GameState::OtherPlay:
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

void CPokerLogic::OnGameStateChange(const GameState game_state)
{
	const auto act_pos=theApp.game_action.GetCurActPlayerPos();
	switch (game_state)
	{
	case GameState::OurPlay:
	case GameState::OtherPlay:
		last_round_poker[act_pos].clear();
		break;
	default:
		break;
	}
	return;
}

