#include <iostream>
#include "Angajat.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
class Salariat: public Angajat{
    private:
    int norma;
    int vechime;
    float salariu_net;
    public:
    Salariat(std::string nume,std::string departament,std::string tip,int norma, int vechime, float salariu_net):Angajat(nume,departament,tip),norma(norma),
    vechime(vechime),salariu_net(salariu_net){}
    void afisare(){
        std::cout<<get_nume()<<" "<<this->norma<<" "<<this->vechime<<" "<<this->salariu_net<<std::endl;
    }
    float salariu_brut() override{
        float salariu_br=this->salariu_net*12;
        if(get_departament()=="IT"){
            salariu_br=salariu_br/0.65;
            return salariu_br;
        }
        else if(get_departament()!="IT"){
            salariu_br=salariu_br/0.55;
            return salariu_br;
        }
        return 0;
    }
    float rentabilitate_angajat() override{
        int zile=this->vechime/3;
        float randament=((this->norma*((250-20)-zile))/salariu_brut());
        return randament;
    }
    std::string get_departament1() override{
        return get_departament();
    }
    std::string get_nume1() override{
        return get_nume();
    }
    std::string tip1(){
        return get_tip();
    }
    ~Salariat(){
        
    }
};

class Colaborator: public Angajat{
    private:
    float onorariu;
    float nr_prestari_anuale;
    public:
    Colaborator(std::string nume, std::string departament,std::string tip, float onorariu,float nr_prestari_anuale):Angajat(nume,departament,tip),
    onorariu(onorariu),nr_prestari_anuale(nr_prestari_anuale){}
    void afisare(){
        std::cout<<get_nume()<<" "<<this->onorariu<<" "<<this->nr_prestari_anuale<<std::endl;
    }
    std::string get_departament1() override{
        return get_departament();
    }
    std::string get_nume1() override{
        return get_nume();
    }
    float rentabilitate_angajat() override{
        return 0;
    }
    float salariu_brut() override{
        float salariu_br=this->onorariu*this->nr_prestari_anuale;
        if(get_departament()=="IT"){
            salariu_br=salariu_br/0.65;
            return salariu_br;
        }
        else if(get_departament()!="IT"){
            salariu_br=salariu_br/0.55;
            return salariu_br;
        }
        return 0;
    }
    ~Colaborator(){
        
    }
};

int main(){
    int n,test;
    std::cin>>n;
    std::vector<Angajat*>A;
    for(int i=0;i<n;i++){
        std::string tip;
        std::string nume;
        std::string departament;
        int norma,vechime,nr_pres;
        float sal_net_lun, onor_net;
        std::cin>>tip;
        std::cin>>nume;
        std::cin>>departament;
        if(tip=="salariat"){
            std::cin>>norma;
            std::cin>>vechime;
            std::cin>>sal_net_lun;
            A.push_back(new Salariat(nume,departament,tip,norma,vechime,sal_net_lun));
            //std::cin.ignore();
        }
        else if(tip=="colaborator"){
            std::cin>>onor_net;
            std::cin>>nr_pres;
            A.push_back(new Colaborator(nume,departament,tip,onor_net,nr_pres));
            //std::cin.ignore();
        }
    }
    std::cin>>test;
    std::cin.ignore();
    std::string nume_fir;
    std::string nume_ang;
    float max1=-1;
    std::string ang;
    switch(test){
        case 1:
        std::cin>>nume_fir;
        for(auto &A1: A){
            if(nume_fir==A1->get_departament1())
            A1->afisare();
        }
        break;
        case 2:
        std::cin>>nume_ang;
        for(auto &A1: A){
            if(nume_ang==A1->get_nume1()){
            float val=A1->salariu_brut();
            std::cout<<std::fixed<<std::setprecision(2)<<val;
            }
        }
        break;
        case 3:
        for(auto &A1:A){
            if(A1->get_tip1()=="salariat"){
            float val = A1->rentabilitate_angajat();
            if(val>max1){
                max1=val;
                ang=A1->get_nume1();
            }
            }
        }
        std::cout<<ang;
        break;
    }
    for(int i=0;i<n;i++){
        delete A[i];
    }
}