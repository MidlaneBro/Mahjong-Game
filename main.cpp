#include <iostream>
#include <time.h>
#include "MJgame.h" 

using namespace std;

int main(){ 
	srand(time(NULL));
	MJgame a;
	a.setting();
	a.start();
	a.end();
	return 0;
} 
