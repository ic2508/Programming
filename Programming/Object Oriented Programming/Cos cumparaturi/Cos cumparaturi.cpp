#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
class Produs{
    private:
    std::string nume, categorie;
    float pret, greutate;
    public:
    Produs(){}
    Produs(std::string nume, std::string categorie,float pret, float greutate){
        this->nume=nume;
        this->categorie=categorie;
        this->pret=pret;
        this->greutate=greutate;
    }
    void afis(){
        std::cout<<this->nume<<", "<<this->categorie<<", "<<this->pret<<" lei, "<<this->greutate<<" kg"<<std::endl;
    }
    void afis_buc(int buc){
        std::cout<<this->nume<<", "<<this->categorie<<", "<<this->pret<<" lei, "<<this->greutate<<" kg, "<<buc<<" buc"<<std::endl;
    }
    
    std::string get_categorie(){
        return this->categorie;
    }
    std::string get_nume(){
        return this->nume;
    }
    float get_greutate(){
        return this->greutate;
    }
    float get_pret(){
        return this->pret;
    }
};

class Cos_cumparaturi{
    private:
    int n;
    Produs P[20];
    public:
    Cos_cumparaturi(){}
    Cos_cumparaturi(int n):n(n){}
    float greutate(){
        float g=0;
        for(int i=0;i<n;i++){
        g=g+P[i].get_greutate();
        }
        return g;
    }
    float pret(){
        float p=0;
        for(int i=0;i<n;i++){
        p=p+P[i].get_pret();
        }
        return p;
    }
    void apend(std::string nume,std::string categorie,float pret,float greutate,int i){
        P[i] = Produs(nume,categorie,pret,greutate);
    }
    void afis1(int i){
        P[i].afis();
    }
    void afis_buc1(int i,int buc){
        P[i].afis_buc(buc);
    }
    std::string get_nume1(int x){
        return P[x].get_nume();
    }
    std::string get_categorie1(int i){
        return P[i].get_categorie();
    }
};
int v[20];

int main(){
    Produs P[20];
    int n,test,cnt=0;
    std::cin>>n;
    Cos_cumparaturi C(n);
    std::cin.ignore();
    for(int i=0;i<n;i++){
        std::string nume, categorie;
        float pret, greutate;
        std::getline(std::cin,nume);
        std::getline(std::cin,categorie);
        std::cin>>pret;
        std::cin>>greutate;
        std::cin.ignore();
        P[i] = Produs(nume,categorie,pret,greutate);
        C.apend(nume,categorie,pret,greutate,i);
    }
    std::cin>>test;
    std::cin.ignore();
    std::string numecat;
    float gr,pr;
    int k=0,prag,ok=0;
    float cost;
    switch(test){
        case 1:
        for(int i=0;i<n;i++){
            C.afis1(i);
        }
        break;
        case 2:
        std::getline(std::cin,numecat);
        for(int i=0;i<n;i++){
        if(numecat==C.get_categorie1(i)){
        C.afis1(i);
        ok=1;
        }
        cnt++;
        }
        if(cnt==n && ok==0)
        std::cout<<"N/A"<<std::endl;
        break;
        case 3:
        for(int i=n-1;i>=0;i--){
            for(int j=i;j>=0;j--){
            if(C.get_nume1(i)==C.get_nume1(j))
            v[i]++;
            }
        }
        for(int i=0;i<n;i++){
            if(v[i]!=2)
            C.afis_buc1(i,v[(n-i)-1]);
        }
        break;
        case 4:
        gr = C.greutate();
        std::cout<<std::fixed<<std::setprecision(2)<<gr<<std::endl;
        break;
        case 5:
        std::cin>>prag;
        std::cin>>cost;
        gr = C.greutate();
        pr = C.pret();
        float pret_n = (ceil(gr - prag))*cost;
        float pret_t = pr+pret_n;
        std::cout<<std::fixed<<std::setprecision(2)<<pret_t<<std::endl;
        break;
    }
}