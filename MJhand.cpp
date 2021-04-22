#include <iostream> 
#include <algorithm>
#include <iomanip>
using namespace std;

#include "MJhand.h"
#include "MJcollection.h"

void swap(MJtile& a,MJtile& b){
	MJtile t;
	t=a;
	a=b;
	b=t;
}

bool MJcompare(MJtile a,MJtile b) {
	if(a.suit()<b.suit()){
		return true;
	}
	else if(a.suit()==b.suit()){
		if(a.rank()<b.rank()){
			return true;
		}
		else if(a.rank()==b.rank()){
			if(a.getTileId()<b.getTileId())
				return true;
		}	
	}
	return false;
}

MJhand::MJhand(){
	_total_len=0;
	_faceup_len=0;
	_stage=0;
	for(int i=0;i<30;i++){
		_tiles[i]=MJtile();
		noreveal[i]=true;
	}
}

MJhand::MJhand(MJtile* t, int n){
	_faceup_len=0;
	_total_len=n;
	_stage=0;
	for(int i=0;i<n;i++){
		_tiles[i]=t[i];
	}
	for(int i=0;i<30;i++){
		noreveal[i]=true;
	}
}

MJhand::~MJhand(){
}

int MJhand::total_len() const {
	return _total_len;
}

int MJhand::faceup_len() const {
	return _faceup_len;
}

void MJhand::set_faceup_len(int f){
	_faceup_len=f;
}

bool MJhand::stage() const {
	return _stage;
}

void MJhand::set_stage(bool s){
	_stage=s;
}

int MJhand::caneat(const MJtile& t){
	if(t.suit()==4){
		return 0;
	}
	int down1=0,down2=0,up1=0,up2=0,sum=0;
	for(int i=_faceup_len;i<_total_len;i++){
		if(_tiles[i].suit()==t.suit()){
			if(_tiles[i].rank()==t.rank()-1){
				down1++;
			}
			if(_tiles[i].rank()==t.rank()-2){
				down2++;
			}
			if(_tiles[i].rank()==t.rank()+1){
				up1++;
			}
			if(_tiles[i].rank()==t.rank()+2){
				up2++;
			}
		}
	}
	if(down2>0&&down1>0){
		sum+=1;
	}
	if(down1>0&&up1>0){
		sum+=2;
	}
	if(up1>0&&up2>0){
		sum+=4;
	}
	return sum;
}

bool MJhand::canpong(const MJtile& t){
	int sum=0;
	for(int i=_faceup_len;i<_total_len;i++){
		if(_tiles[i]==t){
			sum++;
		}
	}
	if(sum<2){
		return false;
	}
	else{
		return true;
	}
}

bool MJhand::canminggone(const MJtile& t){
	int sum=0;
	for(int i=_faceup_len;i<_total_len;i++){
		if(_tiles[i]==t){
			sum++;
		}
	}
	if(sum==3){
		return true;
	}
	else{
		return false;
	}
}

bool MJhand::canangone(const MJtile& t){
	int sum=0;
	for(int i=_faceup_len;i<=_total_len;i++){
		if(_tiles[i]==t){
			sum++;
		}
	}
	if(sum==4){
		return true;
	}
	else{
		return false;
	}
}

bool MJhand::canbugone(const MJtile& t){
	int sum=0;
	for(int i=0;i<_faceup_len;i++){
		if(_tiles[i]==t){
			sum++;
		}
	}
	if(sum==3){
		return true;
	}
	else{
		return false;
	}
}

bool MJhand::canhu(const MJtile& t){
	int sum,mod2=0;
	for(int i=1;i<=4;i++){
		sum=0;
		if(t.suit()==i){
			sum++;
		}
		for(int j=_faceup_len;j<_total_len;j++){
			if(_tiles[j].suit()==i){
				sum++;
			}
		}
		if(sum%3==0){
			int amount[9]={};
			if(t.suit()==i){
				amount[t.rank()-1]++;
			}
			for(int j=_faceup_len;j<_total_len;j++){
				if(_tiles[j].suit()==i){
					amount[_tiles[j].rank()-1]++;
				}
			}
			if(i!=4){
				for(int j=0;j<9;j++){
					while(((amount[j]==1)||(amount[j]==2))&&(amount[j+1]>0)&&(amount[j+2]>0)){
						amount[j]--;
						amount[j+1]--;
						amount[j+2]--;
					}
				}
			}
			for(int j=0;j<9;j++){
				if((amount[j]==1)||(amount[j]==2)){
					return false;
				}
			}
		}
		if(sum%3==1){
			return false;
		}
		if(sum%3==2){
			mod2++;
			if(mod2==2){
				return false;
			}
			int amount[9]={};
			int save[9];
			if(t.suit()==i){
				amount[t.rank()-1]++;
			}
			for(int j=_faceup_len;j<_total_len;j++){
				if(_tiles[j].suit()==i){
					amount[_tiles[j].rank()-1]++;
				}
			}
			for(int j=0;j<9;j++){
				save[j]=amount[j];
			}
			for(int test=0;test<9;test++){
				for(int j=0;j<9;j++){
					amount[j]=save[j];
				}
				if(amount[test]>=2){
					amount[test]-=2;
					if(i!=4){
						for(int j=0;j<9;j++){
							while(((amount[j]==1)||(amount[j]==2))&&(amount[j+1]>0)&&(amount[j+2]>0)){
								amount[j]--;
								amount[j+1]--;
								amount[j+2]--;
							}
						}
					}
				}
				int count=0;
				for(int j=0;j<9;j++){
					if((amount[j]==0)||(amount[j]==3)){
						count++;
					}
				}
				if(count==9){
					break;
				}
				if(test==8){
					return false;
				} 
			}
		}
	}
	return true;
}

void MJhand::arrange(){	
	sort(_tiles+_faceup_len,_tiles+_total_len,MJcompare);
}

void MJhand::draw(MJcollection& t){
	_tiles[_total_len]=t.drawfronttile();
	_stage=1;
	if(_tiles[_total_len].flower()!=0){
		applique(_total_len,t);
	}
}

MJtile MJhand::play(int index){
//index：第一張暗牌算1
	MJtile selected;
	if((index<1)||(index>_total_len-_faceup_len+1)){
		selected=MJtile(0);
	}
	else{
		selected=_tiles[_faceup_len+index-1];
	}
	for(int i=_faceup_len+index-1;i<=_total_len;i++){
		_tiles[i]=_tiles[i+1];
	}
	_stage=0;
	arrange();
	return selected;
}

void MJhand::faceup(int index){
//index：第一張暗牌算1
	MJtile t;
	t=_tiles[_faceup_len+index-1];
	for(int i=_faceup_len+index-1;i>_faceup_len;i--){
		_tiles[i]=_tiles[i-1];
	}
	_tiles[_faceup_len]=t;
	_faceup_len++;
	arrange();
}

void MJhand::applique(int index, MJcollection& t){
//index：第一張明牌算0
	if(_stage==0){
		noreveal[_faceup_len]=false;
		faceup(index-_faceup_len+1);
		_tiles[_total_len]=t.drawbacktile();
		_total_len++;
		if(_tiles[_total_len-1].flower()!=0){
			applique(_total_len-1,t);
		} 
	}
	if(_stage==1){
		noreveal[_faceup_len]=false;
		faceup(index-_faceup_len+1);
		_total_len++;
		_tiles[_total_len]=t.drawbacktile();
		if(_tiles[_total_len].flower()!=0){
			applique(_total_len,t);
		} 
	}
}

void MJhand::initial(MJcollection& t){
	_total_len=16;
	_faceup_len=0;
	_stage=0;
	for(int i=0;i<30;i++){
		noreveal[i]=true;
	}
	arrange();
	for(int i=0;i<_total_len;i++){
		if(_tiles[i].flower()!=0){
			applique(i,t);
		}
	}
	arrange();
}

void MJhand::eat(const MJtile& t,int method){
    if((caneat(t)==1)||(((caneat(t)==3)||(caneat(t)==5)||(caneat(t)==7))&&(method==1))){
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()-2)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        for(int j=_total_len;j>_faceup_len;j--){
            _tiles[j]=_tiles[j-1];
        }
        _tiles[_faceup_len]=t;
        noreveal[_faceup_len]=false;
        _faceup_len++;
        _total_len++;
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()-1)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        _total_len--;
        _stage=1;
    }
    if((caneat(t)==2)||(((caneat(t)==3)||(caneat(t)==6)||(caneat(t)==7))&&(method==2))){
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()-1)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        for(int j=_total_len;j>_faceup_len;j--){
            _tiles[j]=_tiles[j-1];
        }
        _tiles[_faceup_len]=t;
        noreveal[_faceup_len]=false;
        _faceup_len++;
        _total_len++;
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()+1)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        _total_len--;
        _stage=1;
    }
    if((caneat(t)==4)||(((caneat(t)==5)||(caneat(t)==6)||(caneat(t)==7))&&(method==3))){
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()+1)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        for(int j=_total_len;j>_faceup_len;j--){
            _tiles[j]=_tiles[j-1];
        }
        _tiles[_faceup_len]=t;
        noreveal[_faceup_len]=false;
        _faceup_len++;
        _total_len++;
        for(int i=_faceup_len;i<_total_len;i++){
            if((_tiles[i].suit()==t.suit())&&(_tiles[i].rank()==t.rank()+2)){
            	noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                break;
            }
        }
        _total_len--;
        _stage=1;
    }
}

void MJhand::pong(const MJtile& t){
	int count=0;
	if(canpong(t)){
		for(int i=_faceup_len;i<_total_len;i++){
			if(_tiles[i]==t){
				count++;
				noreveal[_faceup_len]=false;
				faceup(i-_faceup_len+1);
				if(count==1){
					for(int j=_total_len;j>_faceup_len;j--){
						_tiles[j]=_tiles[j-1];
					}
					_tiles[_faceup_len]=t;
					noreveal[_faceup_len]=false;
					_faceup_len++;
					_total_len++;
				}
				if(count==2){
					break;
				}
			}
		}
		arrange();
		_total_len--;
		_stage=1;
	}
}

void MJhand::minggone(const MJtile& t, MJcollection& mjc){
    int count=0;
    if(canminggone(t)){
        for(int i=_faceup_len;i<_total_len;i++){
            if(i<_faceup_len){
                i=_faceup_len;
            }
            if(_tiles[i]==t){
                count++;
                noreveal[_faceup_len]=false;
                faceup(i-_faceup_len+1);
                if(count==1){
                    for(int j=_total_len;j>_faceup_len;j--){
                        _tiles[j]=_tiles[j-1];
                    }
                    _tiles[_faceup_len]=t;
                    noreveal[_faceup_len]=false;
                    _faceup_len++;
                    _total_len++;
                }
                if(count==3){
                    break;
                }
            }
        }
        arrange();
        _tiles[_total_len]=mjc.drawbacktile();
        _stage=1;
        if(_tiles[_total_len].flower()!=0){
            applique(_total_len,mjc);
        }
    }
}

void MJhand::angone(int index, MJcollection& mjc){
//index：第一張暗牌算1
	MJtile t(_tiles[index+_faceup_len-1]);
    int count=0;
    if(canangone(t)){
        _total_len++;
        for(int i=_faceup_len;i<_total_len;i++){
            if(_tiles[i]==t){
                count++;
                faceup(i-_faceup_len+1);
                if(count==4){
                    break;
                }
            }
        }
        arrange();
        _tiles[_total_len]=mjc.drawbacktile();
        _stage=1;
        if(_tiles[_total_len].flower()!=0){
            applique(_total_len,mjc);
        }
    }
}

void MJhand::bugone(int index, MJcollection& mjc){
//index：第一張暗牌算1
	MJtile t(_tiles[_faceup_len+index-1]);
    if(canbugone(t)){
    	noreveal[_faceup_len]=false;
        faceup(index);
        _total_len++;
        arrange();
        _tiles[_total_len]=mjc.drawbacktile();
        _stage=1;
        if(_tiles[_total_len].flower()!=0){
            applique(_total_len,mjc);
        }
    }
}

void MJhand::huother(const MJtile& t){
	_tiles[_total_len]=t;
	_stage=0;
	_total_len++;
	arrange();
}

void MJhand::huown(){
	_stage=0;
	_total_len++;
	arrange();
}

int MJhand::listen(){
	int sum=0;
	for(int i=1;i<=144;i++){
		if(canhu(MJtile(i))){
			sum++;
		}
	}
	sum/=4;
	return sum;
}

int MJhand::point1(){
	int amount[9]={},sum=0;
	for(int i=0;i<_total_len;i++){
		 if(_tiles[i].suit()==4&&_tiles[i].flower()==0){
		 	amount[_tiles[i].rank()-1]++;
		 }
	} 
	int count3=0,count2=0;
	for(int i=0;i<4;i++){
		if(amount[i]==3){
			count3++;
		}
		if(amount[i]==2){
			count2++;
		} 
	}
	if(count3==4){
		sum+=16;
		cout<<"大四喜"<<endl;
	}
	if(count3==3&&count2==1){
		sum+=8;
		cout<<"小四喜"<<endl; 
	}
	count3=0;count2=0;
	for(int i=4;i<7;i++){
		if(amount[i]==3){
			count3++;
		}
		if(amount[i]==2){
			count2++;
		}
	}
	if(count3==3){
		sum+=8; 
		cout<<"大三元"<<endl; 
	}
	if(count3==2&&count2==1){
		sum+=4; 
		cout<<"小三元"<<endl; 
	}
	return sum;
}

int MJhand::point2(){
	int amount[4][9]={},count=0;
	for(int i=_faceup_len;i<_total_len;i++){
		if(_tiles[i].flower()==0){
			amount[_tiles[i].suit()-1][_tiles[i].rank()-1]++;
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<9;j++){
			if(amount[i][j]==3){
				count++;
			}
		}
	}
	if(count==5){
		cout<<"五暗刻"<<endl; 
		return 8;
	}
	if(count==4){
		return 5;
		cout<<"四暗刻"<<endl; 
	}
	if(count==3){
		cout<<"三暗刻"<<endl; 
		return 2;
	}
	else{
		return 0;
	}
}

int MJhand::point3(){
	int amount[4]={};
	for(int i=0;i<_total_len;i++){
		if(_tiles[i].flower()==0){
			amount[_tiles[i].suit()-1]++;
		}
	}
	if(amount[0]==0&&amount[1]==0&&amount[2]==0){
		cout<<"字一色"<<endl;
		return 16; 
	}
	if(amount[0]==0&&amount[1]==0&&amount[3]==0){
		cout<<"清一色"<<endl;
		return 8; 
	}
	if(amount[0]==0&&amount[2]==0&&amount[3]==0){
		cout<<"清一色"<<endl;
		return 8; 
	}
	if(amount[1]==0&&amount[2]==0&&amount[3]==0){
		cout<<"清一色"<<endl;
		return 8; 
	}
	if(amount[0]==0&&amount[1]==0){
		cout<<"混一色"<<endl;
		return 4; 
	}
	if(amount[0]==0&&amount[2]==0){
		cout<<"混一色"<<endl;
		return 4; 
	}
	if(amount[1]==0&&amount[2]==0){
		cout<<"混一色"<<endl;
		return 4; 
	}
	else{
		return 0;
	}
}

int MJhand::point4(){
	int amount[4][9]={};
	for(int i=0;i<_total_len;i++){
		if(_tiles[i].flower()==0){
			amount[_tiles[i].suit()-1][_tiles[i].rank()-1]++;
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<9;j++){
			if(amount[i][j]==1){
				return 0;
			}
		}
	}
	cout<<"碰碰胡"<<endl; 
	return 4; 
}

int MJhand::point5(){
	int amount[4][9]={};
	for(int i=0;i<_faceup_len;i++){
		if(_tiles[i].flower()==0){
			amount[_tiles[i].suit()-1][_tiles[i].rank()-1]++;
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<9;j++){
			if(amount[i][j]==4){
				return 0;
			}
		}
	}
	if(_total_len-_faceup_len==2){
		cout<<"全求人"<<endl;
		return 2;
	}
	return 0;
}

int MJhand::point6(int listen){
	int amount[4][9]={};
	for(int i=0;i<_total_len;i++){
		amount[_tiles[i].suit()-1][_tiles[i].rank()-1]++;
	}
	for(int i=0;i<9;i++){
		if(amount[3][i]!=0){
			return 0;
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<9;j++){
			if(amount[i][j]>=3){
				return 0;
			}
		}
	}
	if(listen==2){
		cout<<"平胡"<<endl; 
		return 2;
	}
	return 0;
}

int MJhand::point7(int time){
	int count=0;
	if(_tiles[_faceup_len-1].flower()!=0&&time>1){
		cout<<"槓上開花"<<endl;
		return 1;
	}
	for(int i=0;i<_faceup_len;i++){
		if(_tiles[i]==_tiles[_faceup_len-1]){
			count++;
		}
	}
	if(count==4&&time>1){
		cout<<"槓上開花"<<endl; 
		return 1;
	}
	return 0;
}

int MJhand::point8(){
	int amount[9]={};
	for(int i=0;i<_faceup_len;i++){
		if(_tiles[i].suit()==4){
			amount[_tiles[i].rank()-1]++;
		}
	}
	if(amount[7]==4&&amount[8]==4){
		cout<<"八仙過海"<<endl;
		return 8; 
	}
	if(amount[7]==4||amount[8]==4){
		cout<<"花槓"<<endl;
		return 1; 
	}
	else{
		return 0;
	}
}

bool MJhand::point9(int n){
	int sum=0;
	for(int i=0;i<_total_len;i++){
		if(_tiles[i].suit()==4&&_tiles[i].rank()==n){
			sum++;
		}
	}
	if(sum>=3){
		return true;
	}
	return false;
}

int MJhand::point(){
	int sum=0;
	sum+=point1();
	sum+=point2();
	sum+=point3();
	sum+=point4();
	sum+=point8();
	return sum;
}

string number_to_word(int n){
	if(n==1){
		return "一";
	}
	if(n==2){
		return "二";
	}
	if(n==3){
		return "三";
	}
	if(n==4){
		return "四";
	}
	if(n==5){
		return "五";
	}
	if(n==6){
		return "六";
	}
	if(n==7){
		return "七";
	}
	if(n==8){
		return "八";
	}
	if(n==9){
		return "九";
	}
}

void MJhand::showhandtoothers(){
	//part 1 " __ "
	for(int i=0;i<_faceup_len;i++){
		if(noreveal[i]==true){
			continue;
		}
		cout<<" __ ";
	}
	cout<<endl;
	
	//part 2 "| N|"
	for(int i=0;i<_faceup_len;i++){
		if(noreveal[i]==true){
			continue;
		}
		cout<<"|";
		if(_tiles[i].suit()==4){ 
			if(_tiles[i].flower())
				cout<<number_to_word(_tiles[i].flower());
			else 
				cout<<"  ";
		} 
		else{
			switch(_tiles[i].rank()){
				case 1:
					cout<<"一";
					break; 
				case 2:
					cout<<"二";
					break; 
				case 3:
					cout<<"三";
					break; 
				case 4:
					cout<<"四";
					break; 
				case 5:
					cout<<"五";
					break; 
				case 6:
					cout<<"六";
					break; 
				case 7:
					cout<<"七";
					break; 
				case 8:
					cout<<"八";
					break; 
				case 9:
					cout<<"九";
					break; 
				default:
					assert(false); 
			}
		} 
		cout<<"|";
	}
	cout<<endl;
	
	//part 3 "|XX|"
	for(int i=0;i<_faceup_len;i++){
		if(noreveal[i]==true){
			continue;
		}
		cout<<"|";
		if(_tiles[i].suit()==4)
			switch(_tiles[i].rank()){
				case 1:
					cout<<"東";
					break; 
				case 2:
					cout<<"南";
					break; 
				case 3:
					cout<<"西";
					break; 
				case 4:
					cout<<"北";
					break; 
				case 5:
					cout<<"中";
					break; 
				case 6:
					cout<<"發";
					break; 
				case 7:
					cout<<"  ";
					break; 
				case 8:
					switch(_tiles[i].flower()){
						case 1:
							cout<<"梅";
							break; 
						case 2:
							cout<<"蘭";
							break; 
						case 3:
							cout<<"竹";
							break; 
						case 4:
							cout<<"菊";
							break; 
						default:
							assert(false); 
					} 
					break; 
				case 9:
					switch(_tiles[i].flower()){
						case 1:
							cout<<"春";
							break; 
						case 2:
							cout<<"夏";
							break; 
						case 3:
							cout<<"秋";
							break; 
						case 4:
							cout<<"冬";
							break; 
						default:
							assert(false); 
					} 
					break; 
				default:
					assert(false); 
			}
		else{
			switch(_tiles[i].suit()){
				case 1:
					cout<<"筒";
					break; 
				case 2:
					cout<<"條";
					break; 
				case 3:
					cout<<"萬";
					break; 
				default:
					assert(false); 
			}
		} 
		cout<<"|";
	}
	cout<<endl;
	
	//part 4 " ￣ "
	for(int i=0;i<_faceup_len;i++){
		if(noreveal[i]==true){
			continue;
		}
		cout<<" ￣ ";
	}
	cout<<endl;
}

/*ostream& operator << (ostream& os, const MJhand& h){
	
	//part 1 " __ "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" __ ";
	}
	os<<endl;
	
	//part 2 "| N|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4){ 
			if(h._tiles[i].flower())
				os<<" "<<h._tiles[i].flower();
			else 
				os<<"  ";
		} 
		else{
			switch(h._tiles[i].rank()){
				case 1:
					os<<" 1";
					break; 
				case 2:
					os<<" 2";
					break; 
				case 3:
					os<<" 3";
					break; 
				case 4:
					os<<" 4";
					break; 
				case 5:
					os<<" 5";
					break; 
				case 6:
					os<<" 6";
					break; 
				case 7:
					os<<" 7";
					break; 
				case 8:
					os<<" 8";
					break; 
				case 9:
					os<<" 9";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 3 "|XX|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4)
			switch(h._tiles[i].rank()){
				case 1:
					os<<"Ea";
					break; 
				case 2:
					os<<"So";
					break; 
				case 3:
					os<<"We";
					break; 
				case 4:
					os<<"No";
					break; 
				case 5:
					os<<"Mi";
					break; 
				case 6:
					os<<"Fa";
					break; 
				case 7:
					os<<"  ";
					break; 
				case 8:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"Me";
							break; 
						case 2:
							os<<"La";
							break; 
						case 3:
							os<<"Zu";
							break; 
						case 4:
							os<<"Ju";
							break; 
						default:
							assert(false); 
					} 
					break; 
				case 9:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"Sp";
							break; 
						case 2:
							os<<"Su";
							break; 
						case 3:
							os<<"Au";
							break; 
						case 4:
							os<<"Wi";
							break; 
						default:
							assert(false); 
					} 
					break; 
				default:
					assert(false); 
			}
		else{
			switch(h._tiles[i].suit()){
				case 1:
					os<<" O";
					break; 
				case 2:
					os<<" I";
					break; 
				case 3:
					os<<" W";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 4 " -- "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" -- ";
	}
	os<<endl; 
	return os;
} */


ostream& operator << (ostream& os, const MJhand& h){
	
	//part 1 " __ "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" __ ";
	}
	os<<endl;
	
	//part 2 "| N|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4){ 
			if(h._tiles[i].flower())
				os<<number_to_word(h._tiles[i].flower());
			else 
				os<<"  ";
		} 
		else{
			switch(h._tiles[i].rank()){
				case 1:
					os<<"一";
					break; 
				case 2:
					os<<"二";
					break; 
				case 3:
					os<<"三";
					break; 
				case 4:
					os<<"四";
					break; 
				case 5:
					os<<"五";
					break; 
				case 6:
					os<<"六";
					break; 
				case 7:
					os<<"七";
					break; 
				case 8:
					os<<"八";
					break; 
				case 9:
					os<<"九";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 3 "|XX|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4)
			switch(h._tiles[i].rank()){
				case 1:
					os<<"東";
					break; 
				case 2:
					os<<"南";
					break; 
				case 3:
					os<<"西";
					break; 
				case 4:
					os<<"北";
					break; 
				case 5:
					os<<"中";
					break; 
				case 6:
					os<<"發";
					break; 
				case 7:
					os<<"  ";
					break; 
				case 8:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"梅";
							break; 
						case 2:
							os<<"蘭";
							break; 
						case 3:
							os<<"竹";
							break; 
						case 4:
							os<<"菊";
							break; 
						default:
							assert(false); 
					} 
					break; 
				case 9:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"春";
							break; 
						case 2:
							os<<"夏";
							break; 
						case 3:
							os<<"秋";
							break; 
						case 4:
							os<<"冬";
							break; 
						default:
							assert(false); 
					} 
					break; 
				default:
					assert(false); 
			}
		else{
			switch(h._tiles[i].suit()){
				case 1:
					os<<"筒";
					break; 
				case 2:
					os<<"條";
					break; 
				case 3:
					os<<"萬";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 4 " ￣ "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" ￣ ";
	}
	os<<endl; 
	
	//part 5
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"   ";//3 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		if(i<h.faceup_len()){
			os<<"    ";
		}
		if(i>=h.faceup_len()){
			os<<setw(4)<<i-h.faceup_len()+1;
		}
	}
	os<<endl; 
	return os;
} 
