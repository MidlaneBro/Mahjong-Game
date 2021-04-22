#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(){
	_position=0;
}

Player::Player(int position,MJtile* t):MJhand(t,16)
{
	_position=position;
}

Player::~Player(){
	
}

int Player::Get_Pos() const{
	return _position;
} 

void Player::strategy(int position, MJtile t, int &actiontype, int &actionparameter){
	if(actiontype==0&&stage()==1){
		if(canhu(_tiles[_total_len])){
			cout<<_tiles[_total_len];
			bool flag;
			cout<<"您可以自摸，您要自摸嗎?(0=不要,1=要)"<<endl;
			while(1){
				cin>>flag;
				if(flag==0){
					return ;
				}
				if(flag==1){
					actiontype=7;
					return ;	
				}
				else{
					cout<<"無效的輸入，請再輸入一次:";
				}
			}
		}
		for(int i=_faceup_len;i<_total_len;i++){
			if(canangone(_tiles[i])){
				bool flag;
				cout<<"您可以暗槓的牌:"<<endl;
				cout<<_tiles[i];
				cout<<"您要暗槓嗎?(0=不要,1=要)"<<endl;
				while(1){
					cin>>flag;
					if(flag==0){
						return ;
					}
					if(flag==1){
						actiontype=4;
						actionparameter=i-_faceup_len+1;
						return ;	
					}
					else{
						cout<<"無效的輸入，請再輸入一次:";
					}
				}
			}
		}
		if(canbugone(_tiles[_total_len])){
			bool flag;
			cout<<"您可以補槓的牌:"<<endl;
			cout<<_tiles[_total_len];
			cout<<"您要補槓嗎?(0=不要,1=要)"<<endl;
			while(1){
				cin>>flag;
				if(flag==0){
					return ;
				}
				if(flag==1){
					actiontype=5;
					actionparameter=_total_len-_faceup_len+1;
					return ;	
				}
				else{
					cout<<"無效的輸入，請再輸入一次:";
				}
			}
		}
	}
	if(actiontype==8){
		while(1){
			cin>>actionparameter;
			if(actionparameter>0&&actionparameter<total_len()-faceup_len()+2){
				break;
			}
			else{
				cout<<"無效的輸入，請再輸入一次:";
			}
		}
	}
	if(actiontype==0&&stage()==0){
		cout<<"請輸入欲採取的行動(不做事=0";
		if(caneat(t)&&((position==Get_Pos()-1)||(position==4&&Get_Pos()==1))){
		cout<<" 吃=1";
		}
		if(canpong(t)){
			cout<<" 碰=2";
		}
		if(canminggone(t)&&(position!=Get_Pos()-1&&(position!=4||Get_Pos()!=1))){
			cout<<" 明槓=3";
		}
		if(canhu(t)){
			cout<<" 胡=7";
		}
		cout<<"):";
		while(1){
			cin>>actiontype;
			if(actiontype==0){
				return;
			}
			if(actiontype==1&&((position==Get_Pos()-1)||(position==4&&Get_Pos()==1))){
				if(caneat(t)==1){
					actionparameter=1;
					return ;
				}
				if(caneat(t)==2){
					actionparameter=2;
					return ;
				}
				if(caneat(t)==4){
					actionparameter=3;
					return ;
				}
				if(caneat(t)!=0&&caneat(t)!=1&&caneat(t)!=2&&caneat(t)!=4){
					while(1){
						cout<<"請輸入吃的方式(001=1,010=2,100=3):";
						cin>>actionparameter;
						if(actionparameter==1&&((caneat(t)==3)||(caneat(t)==7))){
							return;
						}
						if(actionparameter==2&&((caneat(t)==3)||(caneat(t)==6)||(caneat(t)==7))){
							return;
						}
						if(actionparameter==3&&((caneat(t)==6)||(caneat(t)==7))){
							return;
						} 
						else{
							cout<<"無效的輸入，請再輸入一次吃法:";
						}
					}
					return;
				}
				else{
					cout<<"無效的輸入，請再輸入一次行動:";
				}
			}
			if(actiontype==2){
				if(canpong(t)){
					return;
				}
				else{
					cout<<"無效的輸入，請再輸入一次行動:";
				}
			}
			if(actiontype==3&&(position!=Get_Pos()-1&&(position!=4||Get_Pos()!=1))){
				if(canminggone(t)){
					return;
				}
				else{
					cout<<"無效的輸入，請再輸入一次行動:";
				}
			}
			if(actiontype==7){
				if(canhu(t)){
					return;
				}
				else{
					cout<<"無效的輸入，請再輸入一次行動:";
				}
			}
			else{
				cout<<"無效的輸入，請再輸入一次行動:";
			}
		}
	}
}

void Player::getinfo(int position,int type,MJtile* ts,int tiles_num){
	
}
