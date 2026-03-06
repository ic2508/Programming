#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

class Jucarie{
  protected:
  std::string tematica;
  std::string nume;
  char c;
  public:
  Jucarie(std::string tematica,std::string nume,char c):tematica(tematica)
  ,nume(nume),c(c){}
  virtual void afisare()=0;
  virtual void afisare_tema()=0;
  virtual void varsta_min(float)=0;
  virtual int get_inaltime()=0;
  virtual int get_latime()=0;
  virtual int get_lungime()=0;
  virtual int get_nr_piese()=0;
  virtual float varsta()=0;
  std::string get_tematica(){
      return this->tematica;
  }
  char get_c(){
      return this->c;
  }
};

class Action_figure: public Jucarie{
  private:
  int inaltime,latime,lungime;
  public:
  Action_figure(std::string tematica,std::string nume,char c,int inaltime,
  int latime,int lungime):Jucarie(tematica,nume,c),
  inaltime(inaltime),latime(latime),lungime(lungime){}
  int get_nr_piese(){
      return 0;
  }
  int get_inaltime(){
      return this->inaltime;
  }
  int get_latime(){
      return this->latime;
  }
  int get_lungime(){
      return this->lungime;
  }
  void afisare(){
      std::cout<<"Action_figure "<<this->tematica<<" "<<this->nume<<" "<<
      this->inaltime<<" "<<this->latime<<" "<<this->lungime<<std::endl;
  }
  void afisare_tema(){
      std::cout<<"Action_figure "<<this->tematica<<" "<<this->nume<<" "<<
      this->inaltime<<" "<<this->latime<<" "<<this->lungime<<std::endl;
  }
  void varsta_min(float min1){
      std::cout<<"Action_figure "<<this->tematica<<" "<<(int)(10.00/
      min1)<<std::endl;
  }
  float varsta(){
      float min1=32000;
            if(inaltime<min1)
            min1=inaltime;
            if(latime<min1)
            min1=latime;
            if(lungime<min1)
            min1=lungime;
            return min1;
  }
};

class Puzzle: public Jucarie{
  private:
  int nr_piese,latime,lungime;
  public:
  Puzzle(std::string tematica,std::string nume,char c,int nr_piese,
  int latime,int lungime):Jucarie(tematica,nume,c),
  nr_piese(nr_piese),latime(latime),lungime(lungime){}
  int get_inaltime(){
      return 0;
  }
  int get_nr_piese(){
      return this->nr_piese;
  }
  int get_latime(){
      return this->latime;
  }
  int get_lungime(){
      return this->lungime;
  }
  void afisare(){
      std::cout<<"Puzzle "<<this->tematica<<" "<<this->nume<<" "<<
      this->nr_piese<<" "<<this->latime<<" "<<this->lungime<<std::endl;
  }
  void afisare_tema(){
      std::cout<<"Puzzle "<<this->tematica<<" "<<this->nume<<" "<<
      this->nr_piese<<" "<<this->latime<<" "<<this->lungime<<std::endl;
  }
  void varsta_min(float min1){
      std::cout<<"Action_figure "<<this->tematica<<" "<<(int)(10.00/
      min1)<<std::endl;
  }
  float varsta(){
      float min1=32000;
      if(((float)latime/sqrt((float)nr_piese))<min1)
            min1=((float)latime/sqrt((float)nr_piese));
            if(((float)lungime/sqrt((float)nr_piese))<min1)
            min1=((float)lungime/sqrt((float)nr_piese));
            return min1;
  }
};
bool sortare(Jucarie *s,Jucarie *d){
    if(s->varsta()>d->varsta())
    return true;
    else
    return false;
}
class Manager{
    private:
    int n;
    std::vector<Jucarie*>J;
    public:
    Manager(int n):n(n){}
    void sort(){
        std::sort(J.begin(),J.end(),sortare);
        for(int i=0;i<J.size();i++){
            J[i]->afisare();
        }
    }
    void afisare(){
        for(int i=0;i<J.size();i++){
            J[i]->afisare();
        }
    }
    void afisare_tema(std::string tema){
        for(int i=0;i<J.size();i++){
            if(J[i]->get_tematica()==tema)
            J[i]->afisare_tema();
        }
    }
    void varsta_min(){
        float min1=32000;
        for(int i=0;i<J.size();i++){
            if(J[i]->get_c()=='a'){
            if(J[i]->get_inaltime()<min1)
            min1=J[i]->get_inaltime();
            if(J[i]->get_latime()<min1)
            min1=J[i]->get_latime();
            if(J[i]->get_lungime()<min1)
            min1=J[i]->get_lungime();
            J[i]->varsta_min(min1);
        }
        else if(J[i]->get_c()=='p'){
            if(((float)J[i]->get_latime()/sqrt((float)J[i]->get_nr_piese()))<min1)
            min1=((float)J[i]->get_latime()/sqrt((float)J[i]->get_nr_piese()));
            if(((float)J[i]->get_lungime()/sqrt((float)J[i]->get_nr_piese()))<min1)
            min1=((float)J[i]->get_lungime()/sqrt((float)J[i]->get_nr_piese()));
            J[i]->varsta_min(min1);
        }
        min1=32000;
        }
    }
    void citire(){
        for(int i=0;i<n;i++){
        std::string tema_juc;
        std::string nume_juc;
        char c;
        std::cin>>c;
        std::cin>>tema_juc;
        std::cin>>nume_juc;
        int h,l,L,nr_piese;
        if(c=='a'){
            std::cin>>h;
            std::cin>>l;
            std::cin>>L;
            J.push_back(new Action_figure(tema_juc,nume_juc,c,h,l,L));
        }
        else if(c=='p'){
            std::cin>>nr_piese;
            std::cin>>l;
            std::cin>>L;
            J.push_back(new Puzzle(tema_juc,nume_juc,c,nr_piese,l,L));
        }
    }
    }
};

int main(){
    int n,test;
    std::cin>>n;
    Manager M(n);
    M.citire();
    std::cin>>test;
    std::string tema;
    switch(test){
        case 1:
        M.afisare();
        break;
        case 2:
        std::cin>>tema;
        M.afisare_tema(tema);
        break;
        case 3:
        M.varsta_min();
        break;
        case 4:
        M.sort();
        break;
    }
}