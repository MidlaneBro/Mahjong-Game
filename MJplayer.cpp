#include <iostream>
#include "MJplayer.h"
using namespace std;

MJplayer::MJplayer(){
	_position=0;
}

MJplayer::MJplayer(int position,MJtile* t):MJhand(t,16)
{
	_position=position;
}

MJplayer::~MJplayer(){
	
}

int MJplayer::Get_Pos() const{
	return _position;
} 

void MJplayer::strategy(int position, MJtile t, int &actiontype, int &actionparameter){
	abandom[position].push_back(t);
	if(actiontype==8){
		cin>>actionparameter;
	}
	if(actiontype==0){
		cin>>actiontype;
		cin>>actionparameter;
	}
}

void MJplayer::getinfo(int position, int type, MJtile* ts, int tiles_num){
	for(int i=0;i<tiles_num;i++){
		faceup[position].push_back(*(ts+i));
	}
}
