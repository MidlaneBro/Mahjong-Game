#ifndef PLAYER 
#define PLAYER
#include <iostream>
#include "MJhand.h"

using namespace std;

class Player:public MJhand{
	public :
		Player();
		Player(int ,MJtile* );
		~Player();
		virtual int Get_Pos() const;
		virtual void strategy(int ,MJtile ,int& ,int& );
		virtual void getinfo(int ,int ,MJtile* ,int );
		//type: eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 play=8
	private :
		int _position;//east = 1 ,south = 2 , west = 3 , north = 4 
};
#endif
