#include <iostream>
#include <cmath>
#include <iomanip>

class Angajat{
  protected:
  std::string nume;
  float salariu_baza;
  std::string functie;
  float procent;
  public:
  Angajat(std::string nume,std::string functie,float salariu_baza){
     this->nume=nume;
     this->functie=functie;
     this->salariu_baza=salariu_baza;
  }
  virtual float get_salariu_baza(){
      return this->salariu_baza;
  }
  virtual float get_salariu_brut(){
      return this->salariu_baza;
  }
  virtual float get_salariu_net(){
      return ((get_salariu_brut())*((100.0-40.0)/100.0));
  }
  std::string get_nume(){
      return this->nume;
  }
  virtual void marire_salariu(float procent_marire_salariu){
      this->salariu_baza=(this->salariu_baza+((procent_marire_salariu*this->salariu_baza)/100));
  }
  std::string get_functie(){
      return this->functie;
  }
  virtual ~Angajat(){
   //   std::cout<<"Destructor Angajat"<<std::endl;
  }
};

class Analist: public Angajat{
    public:
    Analist(std::string nume,std::string functie,float salariu_baza):Angajat(nume,functie,salariu_baza){
    }
    float get_salariu_brut() override{
      return this->salariu_baza;
  }
    float get_salariu_net() override{
      return ((this->salariu_baza)*((100.0-40.0)/100.0));
    }
    float get_salariu_baza(){
      return this->salariu_baza;
  }
  void marire_salariu(float procent_marire_salariu){
      this->salariu_baza=(this->salariu_baza+((procent_marire_salariu*this->salariu_baza)/100));
  }
  ~Analist(){
    //    std::cout<<"Destructor Analist"<<std::endl;
  }
};

class Programator: public Analist{
    protected:
    float procent_deducere_salariu_it;
    public:
    Programator(std::string nume,std::string functie,float salariu_baza,float procent_deducere_salariu_it):
    Analist(nume,functie,salariu_baza),procent_deducere_salariu_it(procent_deducere_salariu_it){
    }
    float get_procent_deducere_salariu_it(){
        return procent_deducere_salariu_it;
    }
    float get_salariu_brut() override{
      return this->salariu_baza;
  }
    float get_salariu_net() override{
      return ((this->salariu_baza)*((100.0-40.0)+this->procent_deducere_salariu_it)/100.0);
    }
    float get_salariu_baza(){
      return this->salariu_baza;
  }
  void marire_salariu(float procent_marire_salariu){
      this->salariu_baza=(this->salariu_baza+((procent_marire_salariu*this->salariu_baza)/100));
  }
  ~Programator(){
   //    std::cout<<"Destructor Programator"<<std::endl;
  }
};

class LiderEchipaProgramare: public Programator{
    protected:
    float bonus_vechime_functie;
    int vechime_functie;
    public:
    LiderEchipaProgramare(std::string nume,std::string functie,float salariu_baza,float procent_deducere_salariu_it,float bonus_vechime_functie,int vechime_functie):
    Programator(nume,functie,salariu_baza,procent_deducere_salariu_it){
        this->bonus_vechime_functie=bonus_vechime_functie;
        this->vechime_functie=vechime_functie;
    }
    float get_bonus_vechime_functie(){
        return bonus_vechime_functie;
    }
    int get_vechime_functie(){
        return vechime_functie;
    }
    float get_salariu_brut() override{
      return (this->salariu_baza+(get_bonus_vechime_functie()*get_vechime_functie()));
  }
  float get_salariu_net() override{
     
      return (get_salariu_brut()*((100.0-40.0)+get_procent_deducere_salariu_it())/100.0);
  }
  float get_salariu_baza(){
      return this->salariu_baza;
  }
  void marire_salariu(float procent_marire_salariu){
      this->salariu_baza=(this->salariu_baza+((procent_marire_salariu*this->salariu_baza)/100));
  }
  ~LiderEchipaProgramare(){
   //   std::cout<<"Destructor LiderEchipaProgramare"<<std::endl;
  }
};

class FirmaProgramare{
    private:
    int nr_ang;
    Angajat** A;
    public:
    FirmaProgramare(Angajat** A,int nr_ang):A(A),nr_ang(nr_ang){}
    void afiseaza_angajati(){
        for(int i=0;i<nr_ang;i++){
        std::cout<<A[i]->get_nume()<<std::endl;
        std::cout<<A[i]->get_functie()<<std::endl;
        }
    }
    void mareste_salarii(std::string functie_in_firma ,float procent_marire_salariu){
        for(int i=0;i<nr_ang;i++){
        if(A[i]->get_functie()==functie_in_firma){
        std::cout<<A[i]->get_nume()<<std::endl;
        std::cout<<"Salariu de baza vechi: "<<A[i]->get_salariu_baza()<<std::endl;
        A[i]->marire_salariu(procent_marire_salariu);
        std::cout<<"Salariu de baza nou: "<<A[i]->get_salariu_baza()<<std::endl;
        }
        }
    }
    int destructor(std::string nume_angajat,std::string functie_in_firma){
        for(int i=0;i<nr_ang;i++){
            if(A[i]->get_nume()==nume_angajat && A[i]->get_functie()=="Analist"){
                delete A[i];
                std::cout<<"Destructor Analist"<<std::endl;
                std::cout<<"Destructor Angajat"<<std::endl;
                return i;
            }
                else if(A[i]->get_nume()==nume_angajat && A[i]->get_functie()=="Programator"){
                delete A[i];
                std::cout<<"Destructor Programator"<<std::endl;
                std::cout<<"Destructor Analist"<<std::endl;
                std::cout<<"Destructor Angajat"<<std::endl;
                return i;
        }
        else if(A[i]->get_nume()==nume_angajat && A[i]->get_functie()=="LiderEchipaProgramare"){
                delete A[i];
                std::cout<<"Destructor LiderEchipaProgramare"<<std::endl;
                std::cout<<"Destructor Programator"<<std::endl;
                std::cout<<"Destructor Analist"<<std::endl;
                std::cout<<"Destructor Angajat"<<std::endl;
                return i;
        }
    }
    return 0;
    }
    void creeare(std::string functie_in_firma,std::string nume_angajat,int val){
        if(functie_in_firma=="Programator")
        A[val] = new Programator(nume_angajat,functie_in_firma,8000,10);
        else if(functie_in_firma=="Analist"){
            A[val] = new Analist(nume_angajat,functie_in_firma,6000);
        }
        else if(functie_in_firma=="LiderEchipaProgramare"){
            A[val] = new LiderEchipaProgramare(nume_angajat,functie_in_firma,14000,10,500,0);
        }
        
    }
    void promoveaza(std::string functie_in_firma, std::string nume_angajat){
        for(int i=0;i<nr_ang;i++){
            std::cout<<A[i]->get_nume()<<std::endl;
            if(A[i]->get_nume()==nume_angajat)
            std::cout<<functie_in_firma<<std::endl;
            else if(A[i]->get_nume()!=nume_angajat)
            std::cout<<A[i]->get_functie()<<std::endl;
        }
        
    }
    void afiseaza_salarii(){
        for(int i=0;i<nr_ang;i++){
        std::cout<<A[i]->get_nume()<<std::endl;
        std::cout<<"Salariu brut: "<<A[i]->get_salariu_brut()<<std::endl;
        std::cout<<"Salariu Net: "<<A[i]->get_salariu_net()<<std::endl;
        }
    }
    ~FirmaProgramare(){
    for(int i=0;i<nr_ang;i++){
        delete A[i];
    }
    delete [] A;
}
};

int main(){
    int nr_ang,test;
    std::cin>>nr_ang;
    Angajat** A = new Angajat*[nr_ang];
    std::cin.ignore();
    
    for(int i=0;i<nr_ang;i++){
        std::string nume;
        std::string rol;
        float salariu;
        float vechime=0;
        std::getline(std::cin,nume);
        std::getline(std::cin,rol);
        std::cin>>salariu;
        if(rol=="LiderEchipaProgramare"){
        std::cin>>vechime;
        std::cin.ignore();
        A[i] = new LiderEchipaProgramare(nume,rol,salariu,10,500,vechime);
        }
        else if(rol=="Programator"){
        std::cin.ignore();
        A[i] = new Programator(nume,rol,salariu,10);
        }
        else if(rol=="Analist"){
        std::cin.ignore();
        A[i] = new Analist(nume,rol,salariu);    
        }
    }
    FirmaProgramare FP(A,nr_ang);
    std::cin>>test;
    std::cin.ignore();
    std::string functie_in_firma ;
    std::string nume_angajat;
    float procent_marire_salariu;
    switch(test){
        case 1:
        FP.afiseaza_angajati();
        break;
        case 2:
        FP.afiseaza_salarii();
        break;
        case 3:
        for(int i=0;i<3;i++){
        std::cin>>functie_in_firma;
        std::cin>>procent_marire_salariu;
        std::cin.ignore();
        FP.mareste_salarii(functie_in_firma,procent_marire_salariu);
        }
        break;
        case 4:
        std::getline(std::cin,nume_angajat);
        std::getline(std::cin,functie_in_firma);
        int val = FP.destructor(nume_angajat,functie_in_firma);
        FP.creeare(functie_in_firma,nume_angajat,val);
        FP.promoveaza(functie_in_firma,nume_angajat);
        break;
    }
}