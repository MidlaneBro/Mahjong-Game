/****************************************************************************** 
   FileName  [MJgame.h]
   Author    [HsuehYa Huang]
   Synopsis  [define a game] 
******************************************************************************/ 
#ifndef MJGAME
#define MJGAME 

#include <iostream> 
#include <vector>
#include <string>
#include <time.h>
#include <iomanip> 
#include <conio.h>

#include "Shuffler.h"
#include "MJtile.h"
#include "MJcollection.h"
#include "Player.h"
#include "AIplayer.h"

using namespace std;

class MJgame{
	//friend ostream& operator << (ostream&, const MJhand&);
public:
	MJgame();
	~MJgame();
	
	void setting();
	void start();
	void print_all();
	int position_to_player(int );
	int MJstage(int ,int* ,int ,int );
	void end();

private:
	int players;//玩家數 
	MJhand* p[4];
	int all[2][4];//第一列是position資訊，第二列是money資訊 
	int rounds;//圈數 一個風為一圈 
	int valueofpoints;//一台多少錢 
}; 

MJgame::MJgame(){
	cout<<endl;
	cout<<"************************************"<<endl;
	cout<<"******Welcome to Taiwan Mahjong*****"<<endl;
	cout<<"************************************"<<endl;
	cout<<endl;
}
MJgame::~MJgame(){
}

void MJgame::setting() { 
	int money;
	cout<<"玩家人數(0~4):";
	cin>>players;
	cout<<"初始賭資:";
	cin>>money;
	for(int i=0;i<4;i++){
		all[1][i]=money;
	}
	cout<<"想打幾風呢:";
	cin>>rounds;
	cout<<"一台多少錢:";
	cin>>valueofpoints;
	system("cls");
}

string place(int position){
	if(position==1){
		return "東";
	}
	if(position==2){
		return "南";
	} 
	if(position==3){
		return "西";
	}
	if(position==4){
		return "北";
	}
}

void MJgame::print_all(){
	cout<<endl;
	cout<<"**********資訊總覽**********"<<endl;
	cout<<"名稱"<<" "; 
	for(int i=0;i<4;i++){
		if(i<players){
			cout<<"玩家"<<i+1<<" "; 
		}
		else{
			cout<<"電腦"<<i+1<<" ";
		}
	}
	cout<<endl;
	cout<<"位置"<<" ";
	for(int i=0;i<4;i++){
		cout<<setw(5)<<place(all[0][i])<<" ";
	}
	cout<<endl;
	cout<<"賭資"<<" ";
	for(int i=0;i<4;i++){
		cout<<setw(5)<<all[1][i]<<" ";
	} 
	cout<<endl;
	cout<<"****************************"<<endl;
	cout<<endl;
}

void MJgame::start() {
	int position[4]={1,2,3,4},dealer;
	for(int i=0;i<rounds;i++){
		if(i%2==0){//每兩個風換一次位置 
			for(int j=0;j<100;j++){
				swap(position[rand()%4],position[rand()%4]);
			}
		}
		cout<<"請擲骰決定起莊者"<<endl;
		getch();
		int dice;
		dice=rand()%16+3;
		cout<<"骰子點數合計為"<<dice<<endl;
		dealer=dice%4+1;
		cout<<"起莊者為"<<place(dealer)<<"家"<<endl;
		getch();
		system("cls"); 
		for(int j=0;j<4;j++){
			int winner,conti=0;
			do{
				cout<<"-----"<<place((i+1)%4)<<"風圈-----"<<endl;
				cout<<"一局("<<place(dealer)<<"家莊)開始"<<endl;
				winner=MJstage(dealer,position,conti,((i+1)%4));
				if(winner==dealer){
					cout<<place(dealer)<<"家連莊"<<endl; 
					conti++;
				}
				cout<<"一局("<<place(dealer)<<"家莊)結束"<<endl;
				cout<<"輸入任意鍵開始下局"<<endl;
				getch();
				system("cls");
			}while(winner==dealer);
			dealer++;
			if(dealer>4){
				dealer=1;
			}
		}
		cout<<"---"<<place((i+1)%4)<<"風圈結束---"<<endl;
	}
}

int MJgame::position_to_player(int n){
	for(int i=0;i<4;i++){
		if(all[0][i]==n){
			return i;
		}
	}
}

int MJgame::MJstage(int dealer,int position[4],int conti,int round){
	Shuffler a;
	a.init();
	MJtile b[144];
	a.fill(b);
	MJcollection c(b);
	int point=1;
	for(int i=0;i<4;i++){
		MJtile d[16];
		for(int j=0;j<16;j++){
			d[j]=c.drawfronttile();
		}
		all[0][i]=position[i];
		if(i<players){
			p[i]=new Player(position[i],d);
		}
		if(i>=players){
			p[i]=new AIplayer(position[i],d);
		}
	}
	print_all();
	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){
			if(p[i]->Get_Pos()>p[j]->Get_Pos()){
				swap(p[i],p[j]);
			}
		}
	}
	cout<<"系統自動發牌+補花+理牌"<<endl;
	getch();
	for(int i=0;i<4;i++){
		p[i]->initial(c);
	}
	p[dealer-1]->draw(c);
	p[dealer-1]->arrange();
	int now=dealer-1,count=0;
	while(c.size()>16){
		count++;
		int type[4]={},parameter[4]={};
		MJtile t;
		system("cls");
		print_all();
		cout<<"*"<<place(now+1)<<"家回合*"<<endl;
		if(position_to_player(now+1)<players){
			for(int i=0;i<4;i++){
				cout<<place(i+1)<<"家的牌:"<<endl;
				if(i==now){
					cout<<*p[i];
				}
				else{
					p[i]->showhandtoothers();
				} 
			}
		}
		int time=0;
		while(1){
			time++;
			type[now]=0;
			p[now]->strategy(now+1,t,type[now],parameter[now]);
			if(type[now]==4){
				p[now]->angone(parameter[now],c);
				cout<<place(now+1)<<"家暗槓"<<endl;
				if(position_to_player(now+1)<players){
					cout<<*p[now];
				}
			}
			if(type[now]==5){
				p[now]->bugone(parameter[now],c);
				cout<<place(now+1)<<"家補槓"<<endl;
				if(position_to_player(now+1)<players){
					cout<<*p[now];
				}
			}
			if(type[now]==7){
				int listen=p[now]->listen();
				p[now]->huown();
				cout<<place(now+1)<<"家自摸"<<endl;
				cout<<*p[now];
				cout<<"底台一台"<<endl;
				if(now==dealer-1){
					point+=2*conti+1;
					cout<<"連"<<conti<<"拉"<<conti<<endl; 
				}
				point++;
				cout<<"自摸加一台"<<endl; 
				if(p[now]->faceup_len()==0){
					point+=2; 
					cout<<"門清再加兩台"<<endl; 
				}
				if(listen==1){
					point++; 
					cout<<"單吊"<<endl;
				}
				if(count==1){
					if(now==dealer-1){
						point+=24; 
						cout<<"天胡"<<endl; 
					}
					else{
						point+=16; 
						cout<<"地胡"<<endl; 
					}
				}
				point+=p[now]->point();
				point+=p[now]->point7(time);
				if(c.size()==17){
					cout<<"海底撈月"<<endl;
					point++; 
				}
				if(round==1&&p[now]->point9(1)){
					cout<<"圈風台"<<endl; 
					point++;
				}
				if(p[now]->point9(p[now]->Get_Pos())){
					cout<<"門風台"<<endl; 
					point++;
				}
				cout<<"總共"<<point<<"台"<<endl; 
				
				for(int i=0;i<4;i++){
					if(all[0][i]==now+1){
						all[1][i]+=valueofpoints*point*3;
					}
					else{
						all[1][i]-=valueofpoints*point;
					}
				}
				return now+1;
			}
			if(type[now]==0){
				break;
			}
		}
		type[now]=8;
		cout<<"請"<<place(now+1)<<"家出牌:";
		p[now]->strategy(now+1,t,type[now],parameter[now]);
		t=p[now]->play(parameter[now]);
		cout<<t;
		getch();
		system("cls");
		print_all();
		type[now]=0;
		for(int i=0;i<4;i++){
			if(i!=now&&((p[i]->caneat(t)&&(now+1==p[i]->Get_Pos()-1||(now==3&&p[i]->Get_Pos()==1)))||p[i]->canpong(t)||(p[i]->canminggone(t)&&(now+1!=p[i]->Get_Pos()-1&&(now!=3||p[i]->Get_Pos()!=1)))||p[i]->canhu(t))){
				cout<<place(now+1)<<"家打出的牌是:"<<endl;
				cout<<t;
				if(position_to_player(i+1)<players){
					cout<<*p[i];
				}
				cout<<place(i+1)<<"家可以做事"<<endl;
				p[i]->strategy(now+1,t,type[i],parameter[i]);
			}
		}
		int priority=now;
		for(int i=1;i<=3;i++){
			if(type[(now+i)%4]>type[priority]){
				priority=(now+i)%4;
			}
		}
		if(type[priority]==1){
			p[priority]->eat(t,parameter[priority]);
			cout<<place(priority+1)<<"家吃牌"<<endl;
			getch();
			now=priority;
		}
		if(type[priority]==2){
			p[priority]->pong(t);
			cout<<place(priority+1)<<"家碰牌"<<endl;
			getch();
			now=priority;
		}
		if(type[priority]==3){
			p[priority]->minggone(t,c);
			cout<<place(priority+1)<<"家明槓"<<endl;
			getch();
			now=priority;
			p[now]->draw(c);
		}
		if(type[priority]==7){
			int listen=p[priority]->listen();
			p[priority]->huother(t);
			cout<<place(priority+1)<<"家胡牌"<<endl;
			cout<<place(now+1)<<"家放槍"<<endl;
			cout<<*p[priority];
			cout<<"底台一台"<<endl; 
			if(priority==dealer-1){
				point+=2*conti+1;
				cout<<"連"<<conti<<"拉"<<conti<<endl; 
			}
			if(now==dealer-1){
				point++; 
				cout<<"莊家放槍加一台"<<endl; 
			}
			if(p[now]->faceup_len()==0){
				point++;
				cout<<"門清"<<endl; 
			}
			
			if(count==1){
				point+=8; 
				cout<<"人胡"<<endl; 
			} 
			point+=p[priority]->point();
			point+=p[priority]->point5();
			point+=p[priority]->point6(listen);
			if(c.size()==17){
				cout<<"海底撈月"<<endl;
				point++; 
			}
			if(round==1&&p[priority]->point9(1)){
				cout<<"圈風台"<<endl; 
				point++;
			}
			if(p[priority]->point9(p[priority]->Get_Pos())){
				cout<<"門風台"<<endl; 
				point++;
			}
			cout<<"總共"<<point<<"台"<<endl;
			
			for(int i=0;i<4;i++){
				if(all[0][i]==priority+1){
					all[1][i]+=valueofpoints*point;
				}
				if(all[0][i]==now+1){
					all[1][i]-=valueofpoints*point;
				}
			}
			return priority+1;
		}
		if(type[priority]!=1&&type[priority]!=2&&type[priority]!=3&&type[priority]!=7){
			now++;
			if(now>3){
				now=0;
			}
			p[now]->draw(c);
		}
	}
	system("cls");
	print_all();
	cout<<"流局臭莊"<<endl; 
	return dealer;
}

void MJgame::end() {
	print_all();
	cout << "Game End." << endl;
	cout << "Press any button to exit.." << endl;
	cin.get();
}
#endif
