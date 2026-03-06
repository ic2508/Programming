#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

class Angajat{
  protected:
  std::string tip;
  std::string nume;
  float sal_brut;
  int nr_con,nr_ang;
  public:
  Angajat(std::string tip,std::string nume,float sal_brut,int nr_con
):tip(tip),nume(nume),sal_brut(sal_brut),nr_con(nr_con){}
  virtual void afisare() = 0;
  virtual void plata() = 0;
  virtual void sal_net() = 0;
};

class PersoanaFizica: public Angajat{
    private:
    int nr_ang;
    public:
    PersoanaFizica(std::string tip,std::string nume,float sal_brut
    ,int nr_con, int nr_ang):Angajat(tip,nume,sal_brut,nr_con),
  nr_ang(nr_ang){}
  void afisare(){
      std::cout<<this->tip<<std::endl;
      std::cout<<this->nume<<":"<<this->sal_brut<<std::endl;
      std::cout<<std::endl;
  }
  void plata(){
      std::cout<<this->nume<<":"<<std::fixed<<std::setprecision(0)<<(int)(this->sal_brut/((float)this->
      nr_ang*4.0))<<" lei/h"<<std::endl;
  }
  void sal_net(){
      std::cout<<this->nume<<":"<<(int)this->sal_brut<<"-"
      <<(int)(this->sal_brut-0.42*this->sal_brut)<<std::endl;
  }
};
class PersoanaJuridica: public Angajat{
    private:
    int nr_ang;
    public:
    PersoanaJuridica(std::string tip,std::string nume,float sal_brut
    ,int nr_con,int nr_ang):Angajat(tip,nume,sal_brut,nr_con),
  nr_ang(nr_ang){}
  void afisare(){
      std::cout<<this->tip<<std::endl;
      std::cout<<this->nume<<":"<<this->sal_brut<<std::endl;
      std::cout<<std::endl;
  }
  void plata(){
      std::cout<<this->nume<<":"<<std::fixed<<std::setprecision(0)<<(int)(this->sal_brut/((float)this->
      nr_ang*8.0*4.0))<<" lei/h"<<std::endl;
  }
  void sal_net(){
      std::cout<<this->nume<<":"<<(int)this->sal_brut<<"-"
      <<(int)(this->sal_brut-0.10*this->sal_brut)<<std::endl;
  }
};

class Manager{
    private:
    int n;
    std::vector<Angajat*>A;
    public:
    Manager(int n):n(n){}
    void afisare(){
        for(auto &a : A){
            a->afisare();
        }
    }
    void plata(){
        for(auto &a : A){
            a->plata();
        }
    }
    void sal_net(){
        for(auto &a : A){
            a->sal_net();
        }
    }
    void citire(){
        for(int i=0;i<n;i++){
        std::string tip;
        std::string nume;
        float sal_brut;
        int nr_con,nr_ang;
        std::cin.ignore();
        std::getline(std::cin,tip);
        std::getline(std::cin,nume);
        std::cin>>sal_brut;
        std::cin>>nr_con;
        if(tip=="Persoana fizica"){
            std::cin>>nr_ang;
            A.push_back(new PersoanaFizica(tip,nume,sal_brut,nr_con,nr_ang));
        }
        if(tip=="Persoana juridica"){
            std::cin>>nr_ang;
            A.push_back(new PersoanaJuridica(tip,nume,sal_brut,nr_con,nr_ang));
        }
    }
    }
};

int main(){
    int n,test;
    std::cin>>test;
    std::cin>>n;
    Manager M(n);  
    M.citire();
    std::cin.ignore();
    switch(test){
        case 1:
        M.afisare();
        break;
        case 2:
        M.plata();
        break;
        case 3:
        M.sal_net();
        break;
    }
    
}
