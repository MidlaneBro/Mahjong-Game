/****************************************************************************** 
   FileName  [MJhand.h]
   Author    [HsuehYa Huang]
   Synopsis  [define a player's hand] 
******************************************************************************/ 
#ifndef MJHAND
#define MJHAND

#include <iostream> 
#include <vector>
using namespace std;

#include "MJtile.h" 
#include "MJcollection.h" 
class MJhand{
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJhand();
	MJhand(MJtile*, int);
	~MJhand();
	
	int total_len() const;
	int faceup_len() const;
	void set_faceup_len(int f);
	bool stage() const;
	void set_stage(bool s);
	
	int caneat(const MJtile&);
	bool canpong(const MJtile&);
	bool canminggone(const MJtile&);
	bool canangone(const MJtile&);
	bool canbugone(const MJtile&);
	bool canhu(const MJtile&);
	
	void arrange();
	void draw(MJcollection&);
	MJtile play(int);
	void faceup(int);
	void applique(int, MJcollection&);
	void initial(MJcollection&);
	
	void eat(const MJtile&, int);
	void pong(const MJtile&);
	void minggone(const MJtile&, MJcollection&);
	void angone(int, MJcollection&);
	void bugone(int, MJcollection&);
	void huother(const MJtile&);
	void huown();
	int listen();//回傳聽幾張牌 

	void showhandtoothers();
	int point1();//四喜/三元台
	int point2();//暗刻台 
	int point3();//清一色
	int point4();//碰碰胡 
	int point5();//全求人
	int point6(int );//平胡 
	int point7(int );//槓上開花 
	int point8();//花槓/搶槓 
	bool point9(int );//確認是否有某風刻子
	int point();//1+2+3+4
	
	virtual int Get_Pos() const=0;
	virtual void strategy(int ,MJtile ,int& ,int& )=0;
	virtual void getinfo(int ,int ,MJtile* ,int )=0;	
protected:
	int _total_len;
	int _faceup_len;
	int _stage;//0 normal stage, 1 draw stage
	MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5
	bool noreveal[30];
}; 
#endif
