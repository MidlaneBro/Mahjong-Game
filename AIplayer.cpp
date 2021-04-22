#include <iostream>
#include "AIplayer.h"
using namespace std;

AIplayer::AIplayer(){
	_position=0;
}

AIplayer::AIplayer(int position,MJtile* t):MJhand(t,16)
{
	_position=position;
}

AIplayer::~AIplayer(){
	
}

int AIplayer::Get_Pos() const{
	return _position;
} 

int lone(const int* amount){
	int a[9]={};
	for(int i=0; i<9; i++){
		if((amount[i]==3)&&(amount[i-1]==2)&&(amount[i+1]==2)) a[i]=amount[i];
		else a[i]=amount[i]%3; // eliminate triplets except x232x which works better with sequences
	}
	for(int j=0;j<9;j++){ //eliminate sequences
		while(((a[j]==1)||(a[j]==2))&&(a[j+1]>0)&&(a[j+2]>0)){
			a[j]--;
			a[j+1]--;
			a[j+2]--;
		}
	}
	int index=0;
	for(int i=0; i<9; i++){ 
		if(a[i]==2) index+=1; //破壞安寧 
		else if(a[i]==1){
			if((a[i-2]==0)&&(a[i-1]==0)&&(a[i+1]==0)&&(a[i+2]==0)) index+=4; //大孤張 
			else index+=2; //破壞安寧 
		}
		else if(a[i]==0){  //用caneat來贖罪 
			if(i==0){
				if((a[i+2]>0)&&(a[i+1]>0)) index-=1;
			}
			else if(i==1){
				if(((a[i+1]>0)&&(a[i-1]>0))||((a[i+2]>0)&&(a[i+1]>0))) index-=1;
			}
			else if(i==7){
				if(((a[i+1]>0)&&(a[i-1]>0))||((a[i-2]>0)&&(a[i-1]>0))) index-=1;
			}
			else if(i==8){
				if((a[i-2]>0)&&(a[i-1]>0)) index-=1;
			}
			else{
				if(((a[i-2]>0)&&(a[i-1]>0))||((a[i+1]>0)&&(a[i-1]>0))||((a[i+2]>0)&&(a[i+1]>0))) index-=1;
			}
		}
	}
	return index;
}

int lone_after_play(const int* amount){
	int a[9]={};
	for(int i=0; i<9; i++){
		if((amount[i]==3)&&(amount[i-1]==2)&&(amount[i+1]==2)) a[i]=amount[i];
		else a[i]=amount[i]%3; // eliminate triplets except x232x which works better with sequences
	}
	for(int j=0;j<9;j++){ //eliminate sequences
		while(((a[j]==1)||(a[j]==2))&&(a[j+1]>0)&&(a[j+2]>0)){
			a[j]--;
			a[j+1]--;
			a[j+2]--;
		}
	}
	for(int j=0;j<9;j++){
		if(a[j]==1){
			if(j==0){
				if(a[j+1]==0){
					a[j]--;
					break;
				}
			}
			if(j==8){
				if(a[j-1]==0){
					a[j]--;
					break;
				}
			}
			else{
				if(a[j-1]==0&&a[j+1]==0){
					a[j]--;
					break;
				}
			}
		}
		if(j==8){
			int r=rand()%9;
			while(a[r]==0) {r=rand()%9;}
			a[r]--;
		}
	}
	int index=0;
	for(int i=0; i<9; i++){ 
		if(a[i]==2) index+=1; //破壞安寧 
		else if(a[i]==1){
			if((a[i-2]==0)&&(a[i-1]==0)&&(a[i+1]==0)&&(a[i+2]==0)) index+=4; //大孤張 
			else index+=2; //破壞安寧 
		}
		else if(a[i]==0){  //用caneat來贖罪 
			if(i==0){
				if((a[i+2]>0)&&(a[i+1]>0)) index-=1;
			}
			else if(i==1){
				if(((a[i+1]>0)&&(a[i-1]>0))||((a[i+2]>0)&&(a[i+1]>0))) index-=1;
			}
			else if(i==7){
				if(((a[i+1]>0)&&(a[i-1]>0))||((a[i-2]>0)&&(a[i-1]>0))) index-=1;
			}
			else if(i==8){
				if((a[i-2]>0)&&(a[i-1]>0)) index-=1;
			}
			else{
				if(((a[i-2]>0)&&(a[i-1]>0))||((a[i+1]>0)&&(a[i-1]>0))||((a[i+2]>0)&&(a[i+1]>0))) index-=1;
			}
		}
	}
	return index;
}

int AIplayer::find_parameter(int i,int j){
	for(int k=faceup_len();k<=total_len();k++){
		if(_tiles[k].suit()==i+1&&_tiles[k].rank()==j+1){
			return k-faceup_len()+1;
		}
	}
}

void AIplayer::strategy(int position, MJtile t, int &actiontype, int &actionparameter){
	if(actiontype==0&&stage()==1){
		if(canhu(_tiles[_total_len])){
			actiontype=7;
			return ;
		}
		for(int i=_faceup_len;i<_total_len;i++){
			if(canangone(_tiles[i])){
				actiontype=4;
				actionparameter=i-_faceup_len+1;
				return ;	
			}
		}
		if(canbugone(_tiles[_total_len])){
			actiontype=5;
			actionparameter=_total_len-_faceup_len+1;
			return ;	
		}
		else{
			actiontype=0;
			return ;
		}
	}
	if(actiontype==8){
		cout<<endl;
		int amount[4][9]={},mod2=0;
		for(int i=faceup_len();i<=total_len();i++){
			amount[_tiles[i].suit()-1][_tiles[i].rank()-1]++;
		}
		//part1:處理suit=4的部分 
		for(int i=0;i<9;i++){
			if(amount[3][i]==1){
				actionparameter=find_parameter(3,i);
				return ;
			}
			if(amount[3][i]==2){
				mod2++;
			}
		}
		//part2:處理孤張的部分
		for(int i=0;i<3;i++){
			for(int j=0;j<9;j++){
				if(amount[i][j]==1){
					if(j==0){
						if(amount[i][j+1]==0){
							actionparameter=find_parameter(i,j);
							return ;
						}
					}
					if(j==8){
						if(amount[i][j-1]==0){
							actionparameter=find_parameter(i,j);
							return ;
						}
					}
					else{
						if(amount[i][j-1]==0&&amount[i][j+1]==0){
							actionparameter=find_parameter(i,j);
							return ;
						}
					}
				}
			}
		} 
		//part3:將牌湊成能胡的牌型 
		int sum[3];
		for(int i=0;i<3;i++){
			for(int j=0;j<9;j++){
				sum[i]+=amount[i][j];
			}
		}
		//優先處理sum%3=0或1的 
		for(int i=0;i<3;i++){
			if(sum[i]%3==0||sum[i]%3==1){
				for(int j=0;j<9;j++){
					while((amount[i][j]==1||amount[i][j]==2)&&amount[i][j+1]>0&&amount[i][j+2]>0){
						amount[i][j]--;
						amount[i][j+1]--;
						amount[i][j+2]--;
					}
				}
				for(int j=0;j<9;j++){
					if(amount[i][j]==3){
						amount[i][j]=0;
					}
				}
				for(int j=0;j<9;j++){
					if(amount[i][j]!=0){
						actionparameter=find_parameter(i,j);
						return ;
					}
				}
			}
		}
		//再處理sum%3=2的 
		for(int i=0;i<3;i++){
			if(sum[i]%3==2){
				for(int j=0;j<9;j++){
					while((amount[i][j]==1||amount[i][j]==2)&&amount[i][j+1]>0&&amount[i][j+2]>0){
						amount[i][j]--;
						amount[i][j+1]--;
						amount[i][j+2]--;
					}
				}
				for(int j=0;j<9;j++){
					if(amount[i][j]==3){
						amount[i][j]=0;
					}
				}
				for(int j=0;j<9;j++){
					if(amount[i][j]==1){
						actionparameter=find_parameter(i,j);
						return;
					}
					if(amount[i][j]==2){
						mod2++;
					}
				}
			}
		}
		//part4:將超過一個的對子打掉  
		if(mod2>1){
			for(int i=0;i<4;i++){
				for(int j=0;j<9;j++){
					if(amount[i][j]==2){
						actionparameter=find_parameter(i,j);
						return;
					}
				}
			}
		}
		actionparameter=total_len()-faceup_len()+1;
		return ;
	}
	if(actiontype==0&&stage()==0){
		if(canhu(t)){
			actiontype=7;
		}
		else if(canminggone(t)&&((position!=Get_Pos()-1)||(position!=4&&Get_Pos()==1))){
			actiontype=3;
		}
		else if(canpong(t)){
			if(t.suit()==4) actiontype=2;
			else{
				int amount[9]={};
				for(int j=_faceup_len;j<_total_len;j++){
					if(_tiles[j].suit()==t.suit()){
						amount[_tiles[j].rank()-1]++;
					}
				}
				int lone_void=lone(amount);
				amount[t.rank()]-=2;
				int lone_pong=lone_after_play(amount);
				if(lone_void<lone_pong) actiontype=0;
				else if(lone_void>lone_pong) actiontype=2;
				else actiontype=2*(rand()%2);
			}
		}
		else if((caneat(t)!=0)&&((position==Get_Pos()-1)||(position==4&&Get_Pos()==1))){
			int e=caneat(t);
			int amount[9]={};
			for(int j=_faceup_len;j<_total_len;j++){
				if(_tiles[j].suit()==t.suit()){
					amount[_tiles[j].rank()-1]++;
				}
			}
			int temp[9];
			for(int i=0; i<9; i++){ temp[i]=amount[i];}
			if(e==1){//001
				int lone_void=lone(temp);
				temp[t.rank()-2]--;
				temp[t.rank()-3]--;
				int lone_eat1=lone_after_play(temp);
				if(lone_void<lone_eat1) actiontype=0;
				else if(lone_void>lone_eat1){
					actiontype=1;
					actionparameter=1;
				} 
				else{
					actiontype=rand()%2;
					if(actiontype==1) actionparameter=1;
				} 
			}
			else if(e==2){//010
				int lone_void=lone(temp);
				temp[t.rank()-2]--;
				temp[t.rank()]--;
				int lone_eat2=lone_after_play(temp);
				if(lone_void<lone_eat2) actiontype=0;
				else if(lone_void>lone_eat2){
					actiontype=1;
					actionparameter=2;
				} 
				else{
					actiontype=rand()%2;
					if(actiontype==1) actionparameter=2;
				} 
			}
			else if(e==4){//100
				int lone_void=lone(temp);
				temp[t.rank()]--;
				temp[t.rank()+1]--;
				int lone_eat3=lone_after_play(temp);
				if(lone_void<lone_eat3) actiontype=0;
				else if(lone_void>lone_eat3){
					actiontype=1;
					actionparameter=3;
				} 
				else{
					actiontype=rand()%2;
					if(actiontype==1) actionparameter=3;
				} 
			}
			else if(e==3){//011
				int lone_void=lone(temp);
				temp[t.rank()-2]--;
				temp[t.rank()-3]--;
				int lone_eat1=lone_after_play(temp);
				for(int i=0; i<9; i++){ temp[i]=amount[i];}
				temp[t.rank()]--;
				temp[t.rank()-2]--;
				int lone_eat2=lone_after_play(temp);
				if(lone_void<lone_eat1){
					if(lone_void<lone_eat2) actiontype=0;
					else if(lone_void>lone_eat2){
						actiontype=1;
						actionparameter=2;
					}
					else if(lone_void==lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=2;
					}
				}
				else if(lone_void>lone_eat1){
					actiontype=1;
					if(lone_eat1<lone_eat2) actionparameter=1;
					else if(lone_eat1>lone_eat2) actionparameter=2;
					else actionparameter=(rand()%2)+1;
				} 
				else{
					if(lone_void<lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=1;
					}
					else if(lone_void>lone_eat2){
						actiontype=1;
						actionparameter=2;
					}
					else if(lone_void==lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=(rand()%2)+1;
					}
				} 
			}
			else if(e==6){//110
				int lone_void=lone(temp);
				temp[t.rank()]--;
				temp[t.rank()+1]--;
				int lone_eat3=lone_after_play(temp);
				for(int i=0; i<9; i++){ temp[i]=amount[i];}
				temp[t.rank()]--;
				temp[t.rank()-2]--;
				int lone_eat2=lone_after_play(temp);
				if(lone_void<lone_eat3){
					if(lone_void<lone_eat2) actiontype=0;
					else if(lone_void>lone_eat2){
						actiontype=1;
						actionparameter=2;
					}
					else if(lone_void==lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=2;
					}
				}
				else if(lone_void>lone_eat3){
					actiontype=1;
					if(lone_eat3<lone_eat2) actionparameter=3;
					else if(lone_eat3>lone_eat2) actionparameter=2;
					else actionparameter=(rand()%2)+2;
				} 
				else{
					if(lone_void<lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=3;
					}
					else if(lone_void>lone_eat2){
						actiontype=1;
						actionparameter=2;
					}
					else if(lone_void==lone_eat2){
						actiontype=rand()%2;
						if(actiontype==1) actionparameter=(rand()%2)+2;
					}
				} 
			}
			else if(e==7){
				int lone_void=lone(temp);
				temp[t.rank()-2]--;
				temp[t.rank()-3]--;
				int lone_eat1=lone_after_play(temp);
				for(int i=0; i<9; i++){ temp[i]=amount[i];}
				temp[t.rank()]--;
				temp[t.rank()-2]--;
				int lone_eat2=lone_after_play(temp);
				for(int i=0; i<9; i++){ temp[i]=amount[i];}
				temp[t.rank()]--;
				temp[t.rank()+1]--;
				int lone_eat3=lone_after_play(temp);
				if((lone_void<=lone_eat1)&&(lone_void<=lone_eat2)&&(lone_void<=lone_eat3)) actiontype=0;
				else{
					actiontype=1;
					actionparameter=2*(rand()%2)+1;
				}
			}
		}
	}
}

void AIplayer::getinfo(int position, int type, MJtile* ts, int tiles_num){
	for(int i=0;i<tiles_num;i++){
		faceup[position].push_back(*(ts+i));
	}
}
