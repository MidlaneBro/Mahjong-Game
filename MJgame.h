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
	int players;//���a�� 
	MJhand* p[4];
	int all[2][4];//�Ĥ@�C�Oposition��T�A�ĤG�C�Omoney��T 
	int rounds;//��� �@�ӭ����@�� 
	int valueofpoints;//�@�x�h�ֿ� 
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
	cout<<"���a�H��(0~4):";
	cin>>players;
	cout<<"��l���:";
	cin>>money;
	for(int i=0;i<4;i++){
		all[1][i]=money;
	}
	cout<<"�Q���X���O:";
	cin>>rounds;
	cout<<"�@�x�h�ֿ�:";
	cin>>valueofpoints;
	system("cls");
}

string place(int position){
	if(position==1){
		return "�F";
	}
	if(position==2){
		return "�n";
	} 
	if(position==3){
		return "��";
	}
	if(position==4){
		return "�_";
	}
}

void MJgame::print_all(){
	cout<<endl;
	cout<<"**********��T�`��**********"<<endl;
	cout<<"�W��"<<" "; 
	for(int i=0;i<4;i++){
		if(i<players){
			cout<<"���a"<<i+1<<" "; 
		}
		else{
			cout<<"�q��"<<i+1<<" ";
		}
	}
	cout<<endl;
	cout<<"��m"<<" ";
	for(int i=0;i<4;i++){
		cout<<setw(5)<<place(all[0][i])<<" ";
	}
	cout<<endl;
	cout<<"���"<<" ";
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
		if(i%2==0){//�C��ӭ����@����m 
			for(int j=0;j<100;j++){
				swap(position[rand()%4],position[rand()%4]);
			}
		}
		cout<<"���Y��M�w�_����"<<endl;
		getch();
		int dice;
		dice=rand()%16+3;
		cout<<"��l�I�ƦX�p��"<<dice<<endl;
		dealer=dice%4+1;
		cout<<"�_���̬�"<<place(dealer)<<"�a"<<endl;
		getch();
		system("cls"); 
		for(int j=0;j<4;j++){
			int winner,conti=0;
			do{
				cout<<"-----"<<place((i+1)%4)<<"����-----"<<endl;
				cout<<"�@��("<<place(dealer)<<"�a��)�}�l"<<endl;
				winner=MJstage(dealer,position,conti,((i+1)%4));
				if(winner==dealer){
					cout<<place(dealer)<<"�a�s��"<<endl; 
					conti++;
				}
				cout<<"�@��("<<place(dealer)<<"�a��)����"<<endl;
				cout<<"��J���N��}�l�U��"<<endl;
				getch();
				system("cls");
			}while(winner==dealer);
			dealer++;
			if(dealer>4){
				dealer=1;
			}
		}
		cout<<"---"<<place((i+1)%4)<<"���鵲��---"<<endl;
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
	cout<<"�t�Φ۰ʵo�P+�ɪ�+�z�P"<<endl;
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
		cout<<"*"<<place(now+1)<<"�a�^�X*"<<endl;
		if(position_to_player(now+1)<players){
			for(int i=0;i<4;i++){
				cout<<place(i+1)<<"�a���P:"<<endl;
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
				cout<<place(now+1)<<"�a�t�b"<<endl;
				if(position_to_player(now+1)<players){
					cout<<*p[now];
				}
			}
			if(type[now]==5){
				p[now]->bugone(parameter[now],c);
				cout<<place(now+1)<<"�a�ɺb"<<endl;
				if(position_to_player(now+1)<players){
					cout<<*p[now];
				}
			}
			if(type[now]==7){
				int listen=p[now]->listen();
				p[now]->huown();
				cout<<place(now+1)<<"�a�ۺN"<<endl;
				cout<<*p[now];
				cout<<"���x�@�x"<<endl;
				if(now==dealer-1){
					point+=2*conti+1;
					cout<<"�s"<<conti<<"��"<<conti<<endl; 
				}
				point++;
				cout<<"�ۺN�[�@�x"<<endl; 
				if(p[now]->faceup_len()==0){
					point+=2; 
					cout<<"���M�A�[��x"<<endl; 
				}
				if(listen==1){
					point++; 
					cout<<"��Q"<<endl;
				}
				if(count==1){
					if(now==dealer-1){
						point+=24; 
						cout<<"�ѭJ"<<endl; 
					}
					else{
						point+=16; 
						cout<<"�a�J"<<endl; 
					}
				}
				point+=p[now]->point();
				point+=p[now]->point7(time);
				if(c.size()==17){
					cout<<"��������"<<endl;
					point++; 
				}
				if(round==1&&p[now]->point9(1)){
					cout<<"�魷�x"<<endl; 
					point++;
				}
				if(p[now]->point9(p[now]->Get_Pos())){
					cout<<"�����x"<<endl; 
					point++;
				}
				cout<<"�`�@"<<point<<"�x"<<endl; 
				
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
		cout<<"��"<<place(now+1)<<"�a�X�P:";
		p[now]->strategy(now+1,t,type[now],parameter[now]);
		t=p[now]->play(parameter[now]);
		cout<<t;
		getch();
		system("cls");
		print_all();
		type[now]=0;
		for(int i=0;i<4;i++){
			if(i!=now&&((p[i]->caneat(t)&&(now+1==p[i]->Get_Pos()-1||(now==3&&p[i]->Get_Pos()==1)))||p[i]->canpong(t)||(p[i]->canminggone(t)&&(now+1!=p[i]->Get_Pos()-1&&(now!=3||p[i]->Get_Pos()!=1)))||p[i]->canhu(t))){
				cout<<place(now+1)<<"�a���X���P�O:"<<endl;
				cout<<t;
				if(position_to_player(i+1)<players){
					cout<<*p[i];
				}
				cout<<place(i+1)<<"�a�i�H����"<<endl;
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
			cout<<place(priority+1)<<"�a�Y�P"<<endl;
			getch();
			now=priority;
		}
		if(type[priority]==2){
			p[priority]->pong(t);
			cout<<place(priority+1)<<"�a�I�P"<<endl;
			getch();
			now=priority;
		}
		if(type[priority]==3){
			p[priority]->minggone(t,c);
			cout<<place(priority+1)<<"�a���b"<<endl;
			getch();
			now=priority;
			p[now]->draw(c);
		}
		if(type[priority]==7){
			int listen=p[priority]->listen();
			p[priority]->huother(t);
			cout<<place(priority+1)<<"�a�J�P"<<endl;
			cout<<place(now+1)<<"�a��j"<<endl;
			cout<<*p[priority];
			cout<<"���x�@�x"<<endl; 
			if(priority==dealer-1){
				point+=2*conti+1;
				cout<<"�s"<<conti<<"��"<<conti<<endl; 
			}
			if(now==dealer-1){
				point++; 
				cout<<"���a��j�[�@�x"<<endl; 
			}
			if(p[now]->faceup_len()==0){
				point++;
				cout<<"���M"<<endl; 
			}
			
			if(count==1){
				point+=8; 
				cout<<"�H�J"<<endl; 
			} 
			point+=p[priority]->point();
			point+=p[priority]->point5();
			point+=p[priority]->point6(listen);
			if(c.size()==17){
				cout<<"��������"<<endl;
				point++; 
			}
			if(round==1&&p[priority]->point9(1)){
				cout<<"�魷�x"<<endl; 
				point++;
			}
			if(p[priority]->point9(p[priority]->Get_Pos())){
				cout<<"�����x"<<endl; 
				point++;
			}
			cout<<"�`�@"<<point<<"�x"<<endl;
			
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
	cout<<"�y�����"<<endl; 
	return dealer;
}

void MJgame::end() {
	print_all();
	cout << "Game End." << endl;
	cout << "Press any button to exit.." << endl;
	cin.get();
}
#endif
