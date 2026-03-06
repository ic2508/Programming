#include <iostream>
#include <string>
#include <iomanip>

class Vagon{
   private: 
   int nr_pasageri;
   int clasa_v;
   float pret;
   int cap;
   public:
   Vagon(){}
   Vagon(int nr_pasageri,int clasa_v,float pret,int cap){
       this->nr_pasageri=nr_pasageri;
       this->clasa_v=clasa_v;
       this->pret=pret;
       this->cap=cap;
   }
   int get_nr_pasageri(){
       return this->nr_pasageri;
   }
      int get_clasa_v(){
       return this->clasa_v;
      }
      float get_pret(){
       return this->pret;
      }
      int get_cap(){
       return this->cap;
      }
      void afisare1(){
        std::cout<<this->nr_pasageri<<"/"<<this->cap<<" "<<this->clasa_v<<" "<<this->pret<<std::endl;
      }
      float pret1(float suma){
          suma=suma+this->pret;
          return suma;
      }
      float red(){
          return ((70*this->cap)/100);
      }
      void mod_pret(int reducere){
          this->pret=this->pret-((this->pret*reducere)/100);
      }
      int mutare(int index, int pas){
          if(this->cap>this->nr_pasageri){
              int m = (this->cap-this->nr_pasageri);
              this->nr_pasageri=this->nr_pasageri+m;
              pas=pas-m;
              return pas;
          }
          return 0;
      }
          void pas_change(int ram){
              this->nr_pasageri=ram;
          }
          void pas_rem(){
              this->nr_pasageri=0;
          }
      
};

class Tren{
    private:
    std::string ruta;
    int n;
    Vagon v[100];
    public:
    Tren(){}
    Tren(std::string ruta,int n){
        this->ruta=ruta;
        this->n=n;
    }
    Vagon& get_Vagon(int index){
        return v[index];
    }
    void afisare(){
        std::cout<<this->ruta<<std::endl;
    }
};

int v1[100];
int main(){
    std::string ruta;
    std::getline(std::cin,ruta);
    int n;
    std::cin>>n;
    std::cin.ignore();
    Tren T1;
    Tren T(ruta,n);
    Vagon v[n];
    for(int i=0;i<n;i++){
        int nr_pasageri;
        int cap;
        int clasa_v;
        float pret;
        std::cin>>cap>>nr_pasageri>>clasa_v>>pret;
        std::cin.ignore();
        T.get_Vagon(i)=Vagon(nr_pasageri,clasa_v,pret,cap);
    }
    int test;
    std::cin>>test;
    std::cin.ignore();
    int a;
    float suma=0,suma1=0;
    int index, reducere;
    int k=0;
    int ram;
    switch(test){
        case 1:
        T.afisare();
        for(int i=0;i<n;i++)
        T.get_Vagon(i).afisare1();
        break;
        case 2:
        for(int i=0;i<n;i++){
            suma=suma+T.get_Vagon(i).get_pret()*T.get_Vagon(i).get_nr_pasageri();
        }
        std::cout<<std::fixed<<std::setprecision(2)<<suma;
        break;
        case 3:
        std::cin>>a;
        std::cin.ignore();
        for(int i=0;i<a;i++){
        std::cin>>index>>reducere;
        std::cin.ignore();
        if(T.get_Vagon(index).get_nr_pasageri()>=T.get_Vagon(index).red()){
            T.get_Vagon(index).mod_pret(reducere);
            suma=suma+T.get_Vagon(index).get_pret()*T.get_Vagon(index).get_nr_pasageri();
            v1[k]=index;
            k++;
        }
        //else{
        //    suma=suma+v[index].get_pret()*v[index].get_cap();
        //    v1[k]=index;
        //    k++;
        //}
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<k;j++){
                if(v1[j]!=i)
                suma=suma+T.get_Vagon(i).get_pret()*T.get_Vagon(i).get_nr_pasageri();
            }
        }
        std::cout<<std::fixed<<std::setprecision(2)<<suma/2;
        break;
        case 4:
        std::cin>>index;
        for(int i=0;i<n;i++){
            if(T.get_Vagon(i).get_clasa_v()==T.get_Vagon(index).get_clasa_v() && i!=index){
                ram = T.get_Vagon(i).mutare(index, T.get_Vagon(index).get_nr_pasageri());
                T.get_Vagon(index).pas_change(ram);
            }
        }
        T.get_Vagon(index).pas_rem();
        T.afisare();
        for(int i=0;i<n;i++)
        T.get_Vagon(i).afisare1();
        std::cout<<ram<<std::endl;
        
        break;
    }
}