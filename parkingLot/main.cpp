#include<bits/stdc++.h>
using namespace std;


class Vechile{
    public:
    int vchlNo;
    string vechType;
    Vechile(int no, string t){
        vchlNo=no;
        vechType=t;
    }
};
class Lot{
   int lotId;
   int capacity;
   vector<Vechile*> vechiles;
   public: Lot (int id,int cap){
      lotId=  id;
        capacity=cap;
    }
 bool hasSpace(){
    return (int)vechiles.size()<capacity;
 }
  void remove(Vechile *v){
    auto it=find(vechiles.begin(),vechiles.end(),v);
    if(it!= vechiles.end()) vechiles.erase(it);
  }  
  void add(Vechile *v){
    vechiles.push_back(v);
  }
 };
//entryTime kaise automatically dekh skte hh
 class Ticket{
   public: 
    int ticketId;
     int entryTime;
     Vechile *vech;
     Lot *lot;
     Ticket(int id, int t, Vechile* v, Lot* l) {
        ticketId=id;
        entryTime=t;
        vech=v;
        lot=l;
     }
    
};
 
 class ParkingLot{
    string name;
    vector<Lot> lots;//Lots stored by value ,dies with the parkking lot 
       int nxtTicket=1;
   // Ticket t;

  public:
  ParkingLot(string n, int lotcnt,int capPerLot){
name=n;
    for(int i=0;i<lotcnt;i++){
        lots.push_back(Lot(i,capPerLot));//builts a Lot then copies it into the vector
    }
  }
    Ticket* park(Vechile *v, int entryTime){
          for(Lot &l:lots){
            if(l.hasSpace()){
                l.add(v);
                return new Ticket(nxtTicket++,entryTime,v, &l);
            }
          }
           return nullptr; 
          
    }
   void unpark(Ticket *t){
         //unable to identif thsi complex relationships
         t->lot->remove(t->vech);
          delete t;
    }
};


int main(){
    int t=5;
    ParkingLot lot("Main",2,3);
    map<int,Ticket*> active;
    while(t--){
//  string vType="2wheeler";
//  int vechNO=231;
// int entryTime=0;
string op,vType;
int vechNO, entryTime;
cin>>op>>vType>>vechNO>>entryTime;

//2 ways to create objects in c++
 //Vechile *v=new Vechile(vechNO,vType);
 //ii am not understanidng why this does not go  
// Vechile v(vechNO,vType);
// Ticket *t= lot.park(v,entryTime);
 if(op=="park"){
     Vechile *v=new Vechile(vechNO,vType);
    Ticket *tk= lot.park(v,entryTime);
    if(tk) {active[vechNO]=tk;
       cout<<"parked "<<vechNO<<" ticket "<<tk->ticketId<<endl; }
    else cout<<"no space"<<endl;
 }else{
    auto it=active.find(vechNO);
    if(it==active.end()) {cout<<"not parked"<<endl; continue;}
    lot.unpark(it->second);
    active.erase(it);
 }
}

}

