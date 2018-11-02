#include "stdafx.h"
#include "PokerLogic.h"
#include <algorithm>


CPokerLogic::CPokerLogic(void)
	:card_interval(25),card_up(20),
	card_size(Size(57*1.4,80*1.4)),  //�Ƶĳ���
	self_poker_center(GAME_DLG_WIDTH/2-card_size.Width/2,GAME_DLG_HEIGHT-300) //�м�����λ��
{
	auto temp=GetImageGroup(IDB_POKER_CARDS,4,14);  //�����и�
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
	poker_img.back()=temp[13+14*2];  //������

	
	for (int i=0;i<18;i++)
	{
		hand_poker[Left].push_back(rand()%50);
		hand_poker[Left].back().hide=true;
	}
	hand_poker[Left].push_back(52);
	hand_poker[Left].push_back(53);
	SortHand();
}


CPokerLogic::~CPokerLogic(void)
{
	for (auto i:poker_img)
	{
		delete i;
	}
}


unsigned char CPokerLogic::CalArrPoint(const MyPoker & cards,ArrayType type)
{
	if (cards.empty()||type==��)
	{
		return 0;
	}
	switch (type)
	{
	case ����   :
	case ����   :
	case ����   :
	case ˳��   :
	case ˫˳   :
	case ��˳   :
		return cards.front().GetPointVal();		//ֱ�ӱȽ���ǰ���ƴ�С
	case ����һ :
	case ������ :
	case �ɻ�   :
		return GetCardFormCount(cards,3);
	case �Ĵ��� :
	case ը��   :
		return GetCardFormCount(cards,4);
	case ��ը   :
		return UCHAR_MAX;
	default:
		break;
	}
	return 0;
}

Rect CPokerLogic::GetMateCardRect(PlayerPosition pos)
{
	int width=GAME_DLG_WIDTH;
	int height=GAME_DLG_HEIGHT;
	switch(pos)
	{
	case Left:
		return Rect(Point(150,height*0.4-hand_poker[Left].size()*card_up/3),card_size);
	case Right:
		return Rect(Point(width-150,height*0.4-hand_poker[Right].size()*card_up/3),card_size);
	default:
		ASSERT(0);
	}
}



Rect CPokerLogic::GetFirstCardRect()
{
	auto p=self_poker_center;
	p.X-=hand_poker[Self].size()/2*card_interval;
	return Rect(p,card_size);
}

Rect CPokerLogic::GetLastCardRect()
{
	auto p=self_poker_center;
	p.X+=(hand_poker[Self].size()-hand_poker[Self].size()/2-1)*card_interval;
	return Rect(p,card_size);
}



Rect CPokerLogic::GetHandCardRect()
{
	auto left_rect=GetFirstCardRect();
	auto width=GetLastCardRect().GetRight()-left_rect.GetLeft();
	return Rect(left_rect.GetLeft(),left_rect.GetTop()-card_up,width,left_rect.Height+card_up);

}

void CPokerLogic::DelCheckedCards()
{
	for (auto i=hand_poker[Self].begin();i!=hand_poker[Self].end();)
	{
		if (i->check)
		{
			i=hand_poker[Self].erase(i);
		}
		else
		{
			i++;
		}
	}
}

void CPokerLogic::DelMateCards(const vector<char> & cards,const PlayerPosition pos)
{
	auto & vec_temp=hand_poker[pos];
	bool buf[54]={false};
	for (const auto i:cards)
	{
		buf[i]=true;
	}
	for (auto i=vec_temp.begin();i!=vec_temp.end();)
	{
		if (buf[i->toNum()])
		{
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
	ASSERT(self_num<0||self_num>=3);
	MyPoker * poker_arr[3];
	MyPoker * temp_arr[4]={&hand_poker[Self],&hand_poker[Right],&hand_poker[Left],&poker_master};
	for (auto i:temp_arr)
	{
		i->clear();
		i->reserve(20);
	}
	const char temp[]={0,1,2,0,1};
	int flag=self_num;
	for (int i=0;i<3;i++)
	{
		poker_arr[flag++]=temp_arr[i];
	}
	for (int i=0;i<3;i++)
	{
		bool hide_flag=i==0?false:true;
		for (int j=0;j<17;j++)
		{
			poker_arr[i]->push_back(cards.at(i));
			poker_arr[i]->back().hide=hide_flag;
		}
	}
	for (auto i=cards.rbegin();i<cards.rbegin()+3;i++)	//������
	{
		poker_master.push_back(*i);
	}
}

MyPoker & CPokerLogic::GetSelfPoker()
{
	return hand_poker[Self];
}

int CPokerLogic::SelectPoker(const CPoint & point)
{
	const auto rect=Rect2CRect(GetHandCardRect());  //�Ƿ���ѡ����
	if (!rect.PtInRect(point))
	{
		return -1;
	}
	const auto right_rect=Rect2CRect(GetLastCardRect());
	int cnt=0;
	for (auto i=hand_poker[Self].rbegin();i!=hand_poker[Self].rend();cnt++,i++)
	{
		auto temp_rect=right_rect;
		temp_rect.OffsetRect(-card_interval*cnt,0);
		temp_rect.OffsetRect(0,-card_up*i->check);
		if (temp_rect.PtInRect(point))
		{
			i->check=!i->check;
			//TRACE("ѡ���˵�%d����",poker_in_hand.size()-cnt);
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
	auto rect=GetFirstCardRect();
	for(auto & i:hand_poker[Self])
	{
		auto temp=Rect(rect.GetLeft()+card_interval*0.3,rect.GetTop()-card_up*i.check+card_interval,
			card_size.Width*0.3,card_size.Height*0.5);//���ܹ���ѡ���ķ�Χ��ʵ��С��
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

void CPokerLogic::ShowHandPoker(Gdiplus::Graphics * g)
{
	//�Լ�������
	auto rect=GetFirstCardRect();
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

	//���˵�����
	MyPoker * mate_poker[3];
	mate_poker[Left]=&hand_poker[Left];
	mate_poker[Right]=&hand_poker[Right];
	const int interval = card_up*2/3;
	const char back_img=54;
	for (int i=Right;i<=Left;i++)
	{
		rect=GetMateCardRect((PlayerPosition)i);
		for (const auto & j:*mate_poker[i])
		{
			g->DrawImage(poker_img[j.hide?back_img:j.toNum()],rect);
			rect.Y+=interval;
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
	case 1: //����
		arrtype=����;
		return true;
	case 2: //���� ��ը
		return (arrtype=����, cd.front()==cd.back() )||
			(arrtype=��ը,cd[0].c_type==CardType::Joker&&cd[1].c_type==CardType::Joker);

	case 3: //����
		return (arrtype=����, cd.front()==cd.back());
	case 4: //ը�� ����һ
		return (arrtype=ը��, IsBomb(cd)) || (arrtype=����һ, Is3with1(cd) );
	case 5: //������ ˳��
		return (arrtype=������, Is3with2(cd) )||(arrtype=˳��, IsStraight(cd) );
	case 6: //˳�� ˫˳ ��˳ �Ĵ���
	default: //˳�� ˫˳ ��˳ �Ĵ��� �ɻ� 
		return (arrtype=˳��, IsStraight(cd) ) 
			|| (arrtype=˫˳, IsDoubleStraight(cd) )
			|| (arrtype=��˳, IsTripleStraight(cd) )
			|| (arrtype=�Ĵ���, Is4with2(cd) )
			|| (arrtype=�ɻ�, IsPlane(cd) );
		return true;
	}
	arrtype=��;
	return false;
}

MyPoker CPokerLogic::GetCheckedCards()
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

CardArray CPokerLogic::GetCardsNeedSend()
{
	return CardArray(GetCheckedCards(),arrtype,1);
}

void CPokerLogic::SortHand()
{
	for (int i=Self;i<=Left;i++)
	{
		sort(hand_poker[Self].begin(),hand_poker[Self].end(),
			[](Poker a, Poker b)->bool 
		{
			return a.point>b.point;     
			//ÿ�ֻ�ɫ13�ţ�52��53�ֱ�ΪС������
		});
	}
	
}

bool CPokerLogic::IsBomb(const MyPoker & cards)
{
	return cards.front()==cards.back()&&cards.size()==4;
}

bool CPokerLogic::Is3with1(const MyPoker & cards)
{
	return cards[0]==cards[2]||cards[1]==cards[3];
}

bool CPokerLogic::Is3with2(const MyPoker & cards)
{
	return (cards[0]==cards[2]&&cards[3]==cards[4]) //�����ں�
		||
		(cards[2]==cards[4]&&cards[0]==cards[1]); //������ǰ
}

bool CPokerLogic::Is4with2(const MyPoker & cards)
{
	for (int l=0,r=l+3;r<cards.size();l++,r++)
	{
		if (cards[l]==cards[r])  //l��r֮��Ϊը
		{
			if (cards.size()==6)  //4��2����
			{
				return true;
			}
			else if (cards.size()==8) //4��2��
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

bool CPokerLogic::IsStraight(const MyPoker & cards)
{
	if (cards.front().GetPointVal()>=(char)PokerPoints::Two)
	{
		return false;  //˳�Ӳ�����2����
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

bool CPokerLogic::IsDoubleStraight(const MyPoker & cards)
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

bool CPokerLogic::IsTripleStraight(const MyPoker & cards)
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

bool CPokerLogic::IsPlane(const MyPoker & cards)
{
	char temp[15]={0};
	for (const auto i:cards)
	{
		temp[i.GetPointVal()]++;
	}
	vector<char> plane;
	vector<char> wing;  //�ɻ������
	for (const auto i:temp)
	{
		(i==3?plane:wing).push_back(i);
	}
	const auto wing_size=cards.size()-plane.size()*3;
	if (plane.size()==wing.size()&&		//�ɻ��ͳ�������ͬ
		(wing.size()==wing_size		    //���Ķ��ǵ���
		||wing.size()*2==wing_size))		//���Ƕ���
	{
		return true;
	}
	return false;
}

bool CPokerLogic::IsGreater(const CardArray & self, const CardArray & per)
{
	if (per.type==��ը)
	{
		return false;
	}
	else if (per.type==self.type)		//������ͬ �ȴ�С ������
	{
		return per.num==self.num && self.point>per.point;
	}
	else
	{
		return self.type==ը��||self.type==��ը;
	}
}

int CPokerLogic::GetCardFormCount(const MyPoker & cards,int count)
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
