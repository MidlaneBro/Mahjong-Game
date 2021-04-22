#include <iostream>
#include <iomanip>
#include <string>
#include "MJtile.h"
 
using namespace std;
 
string rank_to_word(int n){
	if(n==1){
		return "�@";
	}
	if(n==2){
		return "�G";
	}
	if(n==3){
		return "�T";
	}
	if(n==4){
		return "�|";
	}
	if(n==5){
		return "��";
	}
	if(n==6){
		return "��";
	}
	if(n==7){
		return "�C";
	}
	if(n==8){
		return "�K";
	}
	if(n==9){
		return "�E";
	}
}
 
/*ostream &operator << (ostream &output, const MJtile &tile){
    switch(tile.suit()){
        case 1:
            output<<" __ "<<'\n'<<"| "<<tile.rank()<<"|"<<'\n'<<"| O|"<<'\n'<<" -- "<<'\n';
            return output;
        case 2:
            output<<" __ "<<'\n'<<"| "<<tile.rank()<<"|"<<'\n'<<"| I|"<<'\n'<<" -- "<<'\n';
            return output;
        case 3:
            output<<" __ "<<'\n'<<"| "<<tile.rank()<<"|"<<'\n'<<"| W|"<<'\n'<<" -- "<<'\n';
            return output;
        case 4:
            switch(tile.rank()){
                case 1:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|Ea|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 2:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|So|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 3:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|We|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 4:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|No|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 5:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|Mi|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 6:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|Fa|"<<'\n'<<" -- "<<'\n';
                    return output;
                case 7:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|  |"<<'\n'<<" -- "<<'\n';
                    return output;
                case 8:
                    switch(tile.flower()){
                        case 1:
                            output<<" __ "<<'\n'<<"| 1|"<<'\n'<<"|Me|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 2:
                            output<<" __ "<<'\n'<<"| 2|"<<'\n'<<"|La|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 3:
                            output<<" __ "<<'\n'<<"| 3|"<<'\n'<<"|Zu|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 4:
                            output<<" __ "<<'\n'<<"| 4|"<<'\n'<<"|Ju|"<<'\n'<<" -- "<<'\n';
                            return output;
                    }
                case 9:
                    switch(tile.flower()){
                        case 1:
                            output<<" __ "<<'\n'<<"| 1|"<<'\n'<<"|Sp|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 2:
                            output<<" __ "<<'\n'<<"| 2|"<<'\n'<<"|Su|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 3:
                            output<<" __ "<<'\n'<<"| 3|"<<'\n'<<"|Au|"<<'\n'<<" -- "<<'\n';
                            return output;
                        case 4:
                            output<<" __ "<<'\n'<<"| 4|"<<'\n'<<"|Wi|"<<'\n'<<" -- "<<'\n';
                            return output;
                    }
            }
    }
    return output;
}*/

ostream &operator << (ostream &output, const MJtile &tile){
    switch(tile.suit()){
        case 1:
            output<<" __ "<<'\n'<<"|"<<rank_to_word(tile.rank())<<"|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
            return output;
        case 2:
            output<<" __ "<<'\n'<<"|"<<rank_to_word(tile.rank())<<"|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
            return output;
        case 3:
            output<<" __ "<<'\n'<<"|"<<rank_to_word(tile.rank())<<"|"<<'\n'<<"|�U|"<<'\n'<<" �� "<<'\n';
            return output;
        case 4:
            switch(tile.rank()){
                case 1:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|�F|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 2:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|�n|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 3:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 4:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|�_|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 5:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 6:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|�o|"<<'\n'<<" �� "<<'\n';
                    return output;
                case 7:
                    output<<" __ "<<'\n'<<"|  |"<<'\n'<<"|  |"<<'\n'<<" �� "<<'\n';
                    return output;
                case 8:
                    switch(tile.flower()){
                        case 1:
                            output<<" __ "<<'\n'<<"|�@|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 2:
                            output<<" __ "<<'\n'<<"|�G|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 3:
                            output<<" __ "<<'\n'<<"|�T|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 4:
                            output<<" __ "<<'\n'<<"|�||"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                            return output;
                    }
                case 9:
                    switch(tile.flower()){
                        case 1:
                            output<<" __ "<<'\n'<<"|�@|"<<'\n'<<"|�K|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 2:
                            output<<" __ "<<'\n'<<"|�G|"<<'\n'<<"|�L|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 3:
                            output<<" __ "<<'\n'<<"|�T|"<<'\n'<<"|��|"<<'\n'<<" �� "<<'\n';
                            return output;
                        case 4:
                            output<<" __ "<<'\n'<<"|�||"<<'\n'<<"|�V|"<<'\n'<<" �� "<<'\n';
                            return output;
                    }
            }
    }
    return output;
}
 
MJtile::MJtile(){
    _tileId=_rank=_suit=0;
	_flowernum=0;
}
 
MJtile::MJtile(int id){
    _tileId=id;
    _rank=(id-1)/16+1;
    _suit=((id-1)%16)/4+1;
    _flowernum=((_rank>=8)&&(_suit==4))?((id-1)%16-11):0;
}
 
MJtile::~MJtile(){
 
}

void MJtile::setfromId(int id){
	_tileId=id;
    _rank=(id-1)/16+1;
    _suit=((id-1)%16)/4+1;
    _flowernum=((_rank>=8)&&(_suit==4))?((id-1)%16-11):0;
}

int MJtile::suit() const{
    return _suit;
}
 
int MJtile::rank() const{
    return _rank;
}
 
int MJtile::flower() const{
    return _flowernum;
}
 
int MJtile::getTileId() const{
    return _tileId;
}
 
bool MJtile::operator == (const MJtile &tile) const{
    if((this->suit()==tile.suit())&&(this->rank()==tile.rank())){
        return true;
    }
    else{
        return false;
    }
}
 
bool MJtile::operator != (const MJtile &tile) const{
    if((this->suit()==tile.suit())&&(this->rank()==tile.rank())){
        return false;
    }
    else{
        return true;
    }
}
 
bool MJtile::fromsuitrank(int suit, int rank) const{
    if((this->suit()==suit)&&(this->rank()==rank)){
        return true;
    }
    else{
        return false;
    }
}

