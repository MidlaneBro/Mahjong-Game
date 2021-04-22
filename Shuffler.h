#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MJtile.h"

using namespace std;

class Shuffler{
public:
	void init();
	void fill(MJtile[]);
private:
	int id[144];
};

void Shuffler::init(){
	int a,b;
	for(int i=0;i<144;i++){
		id[i]=i+1;
	}
	for(int i=0;i<10000;i++){
		a=rand()%144;
		b=rand()%144;
		swap(id[a],id[b]);
	}
}

void Shuffler::fill(MJtile tile[]){
	for(int i=0;i<144;i++){
		MJtile m(id[i]);
		tile[i]=m;
	}
}
