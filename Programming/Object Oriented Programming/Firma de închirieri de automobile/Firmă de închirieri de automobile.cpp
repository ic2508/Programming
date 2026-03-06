#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

class Automobil{
    protected:
    std::string tip;
    std::string nume;
    int cap;
    float vit;
    int i;
    public:
    Automobil(std::string tip,std::string nume,
    int cap,float vit,int i):tip(tip),nume(nume),
    cap(cap),vit(vit),i(i){}
    virtual void afisare() = 0;
    virtual void grup(int) = 0;
    virtual void drum(float,int) = 0;
    virtual int grup1(int) = 0;
    virtual float coef1(int) = 0;
    virtual int get_i() = 0;
    virtual std::string get_nume() = 0;
    virtual std::string get_tip() = 0;
};

class Masina: public Automobil{
    private:
    public:
    Masina(std::string tip,std::string nume,
    int cap,float vit,int i):
    Automobil(tip,nume,cap,vit,i){}
    void afisare(){
        std::cout<<this->nume<<std::endl;
        std::cout<<this->cap<<std::endl;
        std::cout<<this->vit<<std::endl;
    }
    void grup(int nr_pers){
        std::cout<<this->nume<<std::endl;
        if((nr_pers%(this->cap))==0)
        std::cout<<(nr_pers/this->cap)<<std::endl;
        else if((nr_pers%(this->cap))!=0)
        std::cout<<((nr_pers/this->cap)+1)<<std::endl;
    }
    void drum(float l,int ore){
        if((l/this->vit)<ore){
        std::cout<<this->nume<<std::endl;
        std::cout<<std::fixed<<std::setprecision(2)
        <<(l/this->vit)<<std::endl;
        }
    }
    int grup1(int nr_pers){
        if((nr_pers%(this->cap))==0)
        return (nr_pers/this->cap);
        else if((nr_pers%(this->cap))!=0)
        return ((nr_pers/this->cap)+1);
        return 0;
        }
    float coef1(int nr_pers){
        float c = ((this->vit/100.00)+(this->cap/this->cap));
        std::cout<<c<<std::endl;
        return c;
    }
    
    std::string get_nume(){
        return this->nume;
    }
    std::string get_tip(){
        return this->tip;
    }
    int get_i(){
        return this->i;
    }
};

class Autocar: public Automobil{
    private:
    public:
    Autocar(std::string tip,std::string nume,
    int cap,float vit,int i):
    Automobil(tip,nume,cap,vit,i){}
    void afisare(){
        std::cout<<this->nume<<std::endl;
        std::cout<<this->cap<<std::endl;
        std::cout<<this->vit<<std::endl;
    }
    void grup(int nr_pers){
        std::cout<<this->nume<<std::endl;
        if((nr_pers%(this->cap))==0)
        std::cout<<(nr_pers/this->cap)<<std::endl;
        else if((nr_pers%(this->cap))!=0)
        std::cout<<((nr_pers/this->cap)+1)<<std::endl;
    }
    void drum(float l,int ore){
        if((l/this->vit)<ore){
        std::cout<<this->nume<<std::endl;
        std::cout<<std::fixed<<std::setprecision(2)
        <<(l/this->vit)<<std::endl;
        }
    }
    int grup1(int nr_pers){
        if((nr_pers%(this->cap))==0)
        return (nr_pers/this->cap);
        else if((nr_pers%(this->cap))!=0)
        return ((nr_pers/this->cap)+1);
        return 0;
        }
        std::string get_nume(){
        return this->nume;
    }
    float coef1(int nr_pers){
        int num = 1;
        for(int i=0; i<((2*nr_pers)/this->cap);i++){
            num = num*2.71;
            //std::cout<<num<<std::endl;
        }
        float c = ((this->vit/20.00)+exp(((2.00*(float)nr_pers)/(float)this->cap)));
        std::cout<<c<<std::endl;
        return c;
    }
    std::string get_tip(){
        return this->tip;
    }
    int get_i(){
        return this->i;
    }
};

class FirmaInchirieri{
    private:
    int n;
    std::vector<Automobil*> A;
    public:
    FirmaInchirieri(int n):n(n){}
    void grup(int nr_pers){
        int val = nr_pers;
        for(auto &a : A){
            a->grup(val);
        }
    }
    void drum(float l, int ore){
        for(auto &a : A){
            a->drum(l,ore);
        }
    }
    void pol(int nr_pers){
        std::vector<float> val(n);
        std::vector<int> id(n);
        float max1=-32000;
        int k1=0;
        for(std::vector<Automobil*>::iterator i=A.begin();
        i!=A.end();i++){
            if((*i)->get_tip() == "Masina"){
                val[k1]=((*i)->coef1(nr_pers)*(*i)->grup1(nr_pers));
                //std::cout<<(*i)->coef1(nr_pers)*(*i)->grup1(nr_pers)<<std::endl;
                id[k1]=(*i)->get_i();
                k1++;
            }
            else if((*i)->get_tip() == "Autocar"){
                val[k1]=((*i)->coef1(nr_pers)*(*i)->grup1(nr_pers));
                //std::cout<<(*i)->grup1(nr_pers)<<std::endl;
                id[k1]=(*i)->get_i();
                k1++;
            }
            
    }
    for(int j=0;j<n;j++){
                for(int k=0;k<n-1;k++){
                std::swap(val[k], val[k+1]);
            }
    }
    for(int g=0;g<n;g++){
        //std::cout<<val[g]<<std::endl;
    }
    for(int f=0;f<n;f++){
            for(std::vector<Automobil*>::iterator i=A.begin();
        i!=A.end();i++){
            //if(val[f]==((*i)->coef1(nr_pers)*(*i)->grup1(nr_pers)))
            //std::cout<<(*i)->get_nume()<<std::endl;
    }
    }
    }
    void citire(){
        for(int i=0;i<n;i++){
        std::string tip;
        std::string nume;
        int cap;
        float vit;
        std::cin.ignore();
        std::getline(std::cin,tip);
        if(tip=="Masina"){
        std::getline(std::cin,nume);
        std::cin>>cap;
        std::cin>>vit;
        A.push_back(new Masina(tip,nume,cap,vit,i));
        }
        else if(tip=="Autocar"){
        std::getline(std::cin,nume);
        std::cin>>cap;
        std::cin>>vit;
        A.push_back(new Autocar(tip,nume,cap,vit,i));
        }
    }
    }
    void afisare(){
        for(auto &a : A){
            a->afisare();
        }
    }
    
};

int main(){
    int n,test,nr_pers,ore;
    float l;
    std::cin>>test;
    std::cin>>n;
    FirmaInchirieri F(n);
    F.citire();
    std::cin.ignore();
    switch(test){
        case 1:
        F.afisare();
        break;
        case 2:
        std::cin>>nr_pers;
        F.grup(nr_pers);
        break;
        case 3:
        std::cin>>l;
        std::cin>>ore;
        F.drum(l,ore);
        break;
        case 4:
        std::cin>>nr_pers;
        F.pol(nr_pers);
        break;
    }
    
}