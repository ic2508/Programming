#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>

class Participant{
    private:
    std::string nume,piesa,tari;
    int punctaj;
    int nr=0;
    public:
    Participant(std::string nume, std::string piesa, std::string tari, int punctaj):
    nume(nume),piesa(piesa),tari(tari),punctaj(punctaj){}
    void afisare(){
        std::cout<<this->nume<<" "<<this->piesa<<" "<<this->punctaj<<std::endl;
    }
    void adaugare1(int puncte){
        this->punctaj=this->punctaj+puncte;
        this->nr=this->nr+1;
    }
    void adaugare2(int puncte){
        this->punctaj=this->punctaj+puncte;
    }
    std::string get_nume(){
        return this->nume;
    }
    int get_punctaj(){
        return this->punctaj;
    }
    int get_nr(){
        return this->nr;
    }
    ~Participant(){}
};
bool comp(Participant *s, Participant *d){
    if(s->get_punctaj()>d->get_punctaj())
    return true;
    else if(s->get_punctaj()>=d->get_punctaj() && s->get_nr()>d->get_nr())
    return true;
    else
    return false;
}
bool comp2(Participant *s, Participant *d){
    if(s->get_punctaj()>d->get_punctaj() && s->get_nr()>d->get_nr())
    return true;
    else if(s->get_punctaj()>=d->get_punctaj() && s->get_nr()>d->get_nr())
    return true;
    else
    return false;
}
class Eurovision{
    private:
    std::vector<Participant*>P;
    public:
    Eurovision(){}
    void clasament(){
        std::sort(P.begin(),P.end(),comp);
        for(int i=0;i<P.size();i++){
            P[i]->afisare();
        }
    }
    void populara(){
        std::sort(P.begin(),P.end(),comp2);
        P[0]->afisare();
    }
    void inregistrare(){
        int cnt=7;
        std::string tari;
        for(int i=0;i<P.size();i++){
            for(int j=0;j<4;j++){
            std::cin>>tari;
            for(int k=0;k<P.size();k++){
            if(P[k]->get_nume()==tari)
            P[k]->adaugare1(cnt);
            }
            cnt-=2;
            }
            cnt=7;
        }
    }
    void afisare(){
        for(int i=0;i<P.size();i++){
            P[i]->afisare();
        }
    }
    void citire(){
        std::string nume, piesa;
        std::string tari="";
        int punctaj=0;
        std::cin>>nume;
        std::cin>>piesa;
        //std::cin>>tari;
        P.push_back(new Participant(nume,piesa,tari,punctaj));
    }
    ~Eurovision(){}
};

int main(){
    int test;
    std::cin>>test;
    std::cin.ignore();
    Eurovision E;
    while(test<=6 && test>=1){
        switch(test){
            case 1:
            E.citire();
            break;
            case 2:
            E.afisare();
            break;
            case 3:
            E.inregistrare();
            break;
            case 4:
            E.populara();
            break;
            case 5:
            E.clasament();
            break;
        }
        if(test==6)
        break;
        std::cin>>test;
    }
    
}