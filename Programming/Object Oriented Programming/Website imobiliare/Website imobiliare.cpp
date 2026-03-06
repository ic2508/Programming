#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

class Proprietate{
    protected:
    std::vector<Proprietate*>P;
    char tip;
    int pret;
    std::string locatie;
    int sup;
    public:
    Proprietate(char tip,int pret,std::string locatie,int sup):
    tip(tip),pret(pret),locatie(locatie),sup(sup){}
    virtual void afisare() = 0;
    virtual void suprafata() = 0;
    virtual void pret_mp() = 0;
    virtual float pret_mp_f() = 0;
    virtual void comparare(char,int,std::string,int,int) = 0;
    int get_pret(){
        return this->pret;
    }
    char get_tip(){
        return this->tip;
    }
};

class Casa: public Proprietate{
    private:
    int nr_et;
    public:
    Casa(char tip,int pret,std::string locatie,int sup,int nr_et):
    Proprietate(tip,pret,locatie,sup),nr_et(nr_et){}
    void afisare(){
        std::cout<<"Casa "<<this->pret<<" "<<this->locatie<<" "
        <<this->sup<<" "<<this->nr_et<<std::endl;
    }
    void suprafata(){
        std::cout<<this->sup*this->nr_et<<std::endl;
    }
    void pret_mp(){
        std::cout<<std::fixed<<std::setprecision(2)<<
        ((float)this->pret/((float)this->sup*(float)this->nr_et))<<std::endl;
    }
    float pret_mp_f(){
        float val =
        ((float)this->pret/((float)this->sup*(float)this->nr_et));
        return val;
    }
    void comparare(char tip,int pret,std::string locatie,int sup,
    int nr_et){
        if(this->pret>pret && locatie=="0" && this->sup>sup
            && this->nr_et>nr_et)
            afisare();
            else if(this->pret>pret && locatie==this->locatie && this->sup>sup
            && this->nr_et>nr_et)
            afisare();
    }
};

class Apartament: public Proprietate{
    private:
    int dim;
    public:
    Apartament(char tip,int pret,std::string locatie,int sup,int dim):
    Proprietate(tip,pret,locatie,sup),dim(dim){}
    void afisare(){
        std::cout<<"Apartament "<<this->pret<<" "<<this->locatie<<" "
        <<this->sup<<" "<<this->dim<<std::endl;
    }
    void suprafata(){
        std::cout<<this->sup+this->dim<<std::endl;
    }
    void pret_mp(){
        std::cout<<std::fixed<<std::setprecision(2)<<
        ((float)this->pret/((float)this->sup+(float)this->dim))<<std::endl;
    }
    float pret_mp_f(){
        float val =
        ((float)this->pret/((float)this->sup+(float)this->dim));
        return val;
    }
    void comparare(char tip,int pret,std::string locatie,int sup,
    int dim){
        if(this->pret>pret && locatie=="0" && this->sup>sup
            && this->dim>dim)
            afisare();
            else if(this->pret>pret && locatie==this->locatie && this->sup>sup
            && this->dim>dim)
            afisare();
    }
};

bool pret_ord(Proprietate *s,Proprietate *d){
        if(s->pret_mp_f()<d->pret_mp_f())
        return true;
        else if(s->pret_mp_f()<=d->pret_mp_f()){
                if(s->get_pret()<d->get_pret())
                return true;
                else
                return false;
        }
        else
        return false;
    }

int main(){
    int nr,test;
    std::cin>>nr;
    std::vector<Proprietate*>P;
    char tip;
    int pret,nr_et;
    std::string locatie;
    int sup,dim;
    for(int i=0;i<nr;i++){
        std::cin>>tip;
        std::cin>>pret;
        std::cin>>locatie;
        std::cin>>sup;
        if(tip=='c'){
            std::cin>>nr_et;
            P.push_back(new Casa(tip,pret,locatie,sup,nr_et));
        }
        if(tip=='a'){
            std::cin>>dim;
            P.push_back(new Apartament(tip,pret,locatie,sup,dim));
        }
    }
    std::cin>>test;
    std::cin.ignore();
    switch(test){
        case 1:
        for(std::vector<Proprietate*>::iterator i=P.begin();i!=P.end();i++){
            (*i)->afisare();
        }
        break;
        case 2:
        for(std::vector<Proprietate*>::iterator i=P.begin();i!=P.end();i++){
            (*i)->suprafata();
        }
        break;
        case 3:
        for(std::vector<Proprietate*>::iterator i=P.begin();i!=P.end();i++){
            (*i)->pret_mp();
        }
        break;
        case 4:
        std::sort(P.begin(),P.end(),pret_ord);
        for(std::vector<Proprietate*>::iterator i=P.begin();i!=P.end();i++){
            (*i)->afisare();
            (*i)->pret_mp();
        }
        break;
        case 5:
        std::cin>>tip;
        std::cin>>pret;
        std::cin>>locatie;
        std::cin>>sup;
        if(tip=='c')
        std::cin>>nr_et;
        if(tip=='a')
        std::cin>>dim;
        for(std::vector<Proprietate*>::iterator i=P.begin();i!=P.end();i++){
            if((*i)->get_tip()=='c')
            (*i)->comparare(tip,pret,locatie,sup,nr_et);
            else if((*i)->get_tip()=='a')
            (*i)->comparare(tip,pret,locatie,sup,dim);
        }
        break;
    }
}