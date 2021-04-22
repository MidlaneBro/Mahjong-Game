#ifndef MJCOLLECTION
#define MJCOLLECTION
 
#include "MJtile.h" 
 
using namespace std;
 
class MJcollection{
public:
    MJcollection(){
        for(int i=0;i<144;i++){
            _t[i]=MJtile(i+1);
        }
        _frontind=0;
        _backind=143;
    }
    MJcollection(MJtile* mjs){
        for(int i=0;i<144;i++){
            _t[i]=mjs[i];
        }
        _frontind=0;
        _backind=143;
    }
    ~MJcollection(){ }
 
    int frontind() const{return _frontind;}
    int backind() const{return _backind;}
    int size() const{
        return _backind-_frontind+1;
        /*TODO: return number of remaining tiles*/
    }
    bool checkduplicate() const{
        for(int i=0;i<144;i++){
            for(int j=i+1;j<144;j++){
                if(_t[i].getTileId()==_t[j].getTileId()){
                    return false;
                }
            }
        }
        return true;
        /*TODO: if exists duplicate id's tiles, return false*/
    }
    MJtile drawfronttile() const{
        return _t[_frontind++];
        /*TODO: return the tile at frontind, and frontind++*/
    }
    MJtile drawbacktile() const{
        return _t[_backind--];
        /*TODO: return the tile at backind, and backind--*/
    }
 
private:
    MJtile _t[144];
    mutable int _frontind;
    mutable int _backind;
}; 
#endif

