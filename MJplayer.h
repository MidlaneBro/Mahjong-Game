#ifndef MJPLAYER 
#define MJPLAYER 
#include <iostream>
#include <vector>
#include "MJhand.h"
using namespace std;
class MJplayer:public MJhand{
	public :
		MJplayer();
		MJplayer(int ,int ,MJtile* );
		~MJplayer();
		int Get_Pos() const;
		virtual void strategy(int ,MJtile ,int& ,int& );
		void getinfo(int ,int ,MJtile* ,int );
		//type: eat=1 pong=2 minggone=3 angone=4 bugone=5 applique=6 hu=7 play=8
	private :
		int _position;//east = 1 ,south = 2 , west = 3 , north = 4 
		vector<MJtile> abandom[4];
		vector<MJtile> faceup[4];
};
#endif	
