#ifndef SHUFFLE
#define SHUFFLE

#include "MJtile.h"
#include <cstdlib>
#include <ctime>
 
class Shuffler {
public:
    Shuffler() {
        srand(1);
    }
    Shuffler(int s) {
        srand(s);
    }
    void init() {
        for (int i = 1; i <= tilesnum+1; i++) {
            Used[i] = false;
        }
    }
    void fill(MJtile* mjtiles) {
        // TODO: input an tile array with size 144 
        // fill in it with 144 different cards randomly    
        init();
        for (int i = 0; i < tilesnum; ++i) {
            int id = rand() % tilesnum + 1;
            while (Used[id]) {
                id = rand() % tilesnum + 1;
            }
            Used[id] = true;
            mjtiles[i] = MJtile(id);
        }
    }
private: 
	const int tilesnum = 144; 
    bool Used[145];
};
#endif
