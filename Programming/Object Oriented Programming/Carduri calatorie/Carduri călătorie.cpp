#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "Card_calatorie.h"

class Card_autobuz: public Card_calatorie{
    private:
    int sold;
    int moment_ultima_calatorie;
    public:
    Card_autobuz(){}
    Card_autobuz(int id, char tip, int sold,int moment_ultima_calatorie=0):Card_calatorie(id,tip),sold(sold),moment_ultima_calatorie(moment_ultima_calatorie){}
    void validare_calatorie(int sold_up, int moment_val){
        if(this->sold>=0 && (this->sold-3)>=0 && (moment_val - moment_ultima_calatorie)>90){
        this->sold=this->sold-3;
        moment_ultima_calatorie=moment_val;
    }
        else if((this->sold-3)<0)
        std::cout<<"Sold insuficient"<<std::endl;
    }
    void incarcare(int sold){
        this->sold=this->sold+sold;
    }
    void afisare(){
        std::cout<<get_id()<<" "<<get_tip()<<" "<<sold<<" "<<moment_ultima_calatorie<<std::endl;
    }
    int transfer1(int sold_tr,int k){
        if(this->sold>=0 && (this->sold-sold_tr)>=0)
        this->sold=this->sold-sold_tr;
        else{
        std::cout<<"Transfer nereusit"<<std::endl;
        k++;
        }
        return k;
    }
    void transfer2(int sold_tr){
        this->sold=this->sold+sold_tr;
    }
    ~Card_autobuz(){}
};

class Card_metrou: public Card_calatorie{
    private:
    int nr_calatorii;
    int moment_ultima_calatorie;
    public:
    Card_metrou(){}
    Card_metrou(int id, char tip, int nr_cal,int moment_ultima_calatorie=0):Card_calatorie(id,tip),nr_calatorii(nr_cal),moment_ultima_calatorie(moment_ultima_calatorie){}
    void validare_calatorie(int nr_cal, int moment_val){
        if(this->nr_calatorii>0 && (this->nr_calatorii-1)>=0 && (moment_val - moment_ultima_calatorie)>90){
        this->nr_calatorii=this->nr_calatorii-1;
        moment_ultima_calatorie=moment_val;
        }
        else if((this->nr_calatorii-1)<0)
        std::cout<<"Numar calatorii insuficient"<<std::endl;
    }
    void incarcare(int nr_calatorii){
        this->nr_calatorii=this->nr_calatorii+nr_calatorii;
    }
    void afisare(){
        std::cout<<get_id()<<" "<<get_tip()<<" "<<nr_calatorii<<" "<<moment_ultima_calatorie<<std::endl;
    }
    int transfer1(int sold_tr,int k){
        if(this->nr_calatorii>=0 && (this->nr_calatorii-sold_tr)>=0)
        this->nr_calatorii=this->nr_calatorii-sold_tr;
        else{
        std::cout<<"Transfer nereusit"<<std::endl;
        k++;
        }
        return k;
    }
    void transfer2(int sold_tr){
        this->nr_calatorii=this->nr_calatorii+sold_tr;
    }
    ~Card_metrou(){}
};

int main(){
    int n;
    int test=0;
    int k=0;
    std::cin>>n;
    std::vector<Card_calatorie*>C;
    for(int i=0;i<n;i++){
        char tip;
        int id;
        int valoare;
        std::cin>>tip>>id;
        if(tip=='a'){
        std::cin>>valoare;
        C.push_back(new Card_autobuz(id,tip,valoare,0));
        }
        else if(tip=='m'){
        std::cin>>valoare;
        C.push_back(new Card_metrou(id,tip,valoare,0));
        }
    }
    std::cin>>test;
    std::cin.ignore();
    int val=0;
    int id_up, sold_up,moment_val,id_tr1,id_tr2, sold_tr;
    while(test!=5){
    switch(test){
        case 1:
        for(auto &C1 : C){
            C1->afisare();
        }
        break;
        case 2:
        std::cin>>id_up;
        std::cin>>sold_up;
        for(auto &C1: C){
                if(C1->get_id()==id_up)
                C1->incarcare(sold_up);
        }
        break;
        case 3:
        std::cin>>id_up;
        std::cin>>moment_val;
        for(auto &C1: C){
            if(C1->get_id()==id_up){
            C1->validare_calatorie(sold_up,moment_val);
        }
        }
        break;
        case 4:
        std::cin>>id_tr1;
        std::cin>>id_tr2;
        std::cin>>sold_tr;
        for(auto &C1: C){
            if(C1->get_id()==id_tr1){
            val=C1->transfer1(sold_tr,k);
            }
        }
        if(val==1){
        val=0;
        break;
        }
        for(auto &C2: C){
            if(C2->get_id()==id_tr2){
            C2->transfer2(sold_tr);
            }
        }
        k=0;
        break;
        case 5:
        break;
    }
    std::cin>>test;
    }
}