#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

class Publicatie{
    protected:
    std::string cercetator,titlu,tip;
    int nr_autori,anul;
    long int nr_citari;
    public:
    Publicatie(std::string cercetator,std::string titlu
    ,std::string tip,int nr_autori,int anul,long int nr_citari):
    cercetator(cercetator),titlu(titlu),tip(tip),nr_autori(nr_autori),
    anul(anul),nr_citari(nr_citari){}
    virtual void afisare()=0;
    virtual float punctaj()=0;
    virtual int citari()=0;
    int get_anul(){
        return this->anul;
    }
    long int get_citari(){
        return this->nr_citari;
    }
    virtual ~Publicatie(){}
};

class Conferinta: public Publicatie{
    private:
    int tip_pub;
    public:
    Conferinta(std::string cercetator,std::string titlu
    ,std::string tip,int nr_autori,int anul,long int nr_citari,int tip_pub):
    Publicatie(cercetator,titlu,tip,nr_autori,anul,nr_citari),tip_pub
    (tip_pub){}
    float punctaj(){
        if(tip_pub==1)
        return 0.75;
        else if(tip_pub==0)
        return 0.25;
        return 0;
    }
    int citari(){
        if(nr_citari>10)
        return 1;
        return 0;
    }
    void afisare(){
        if(tip_pub==1)
        std::cout<<titlu<<", "<<nr_autori<<", "<<anul<<", "<<nr_citari<<", "<<
        "ISI"<<std::endl;
        else if(tip_pub==0)
        std::cout<<titlu<<", "<<nr_autori<<", "<<anul<<", "<<nr_citari<<", "<<
        "non-ISI"<<std::endl;
    }
    ~Conferinta(){}
};

class Revista: public Publicatie{
    private:
    int tip_pub;
    public:
    Revista(std::string cercetator,std::string titlu
    ,std::string tip,int nr_autori,int anul,long int nr_citari,int tip_pub):
    Publicatie(cercetator,titlu,tip,nr_autori,anul,nr_citari),tip_pub
    (tip_pub){}
    float punctaj(){
        if(tip_pub==1)
        return 20.00/nr_autori;
        else if(tip_pub==2)
        return 10.00/nr_autori;
        else if(tip_pub==3)
        return 5.00/nr_autori;
        return 0;
    }
    int citari(){
        if(nr_citari>10)
        return 1;
        return 0;
    }
    void afisare(){
        std::cout<<titlu<<", "<<nr_autori<<", "<<anul<<", "<<nr_citari<<", "<<
        "Q"<<tip_pub<<std::endl;
    }
     ~Revista(){}
};
bool sort(Publicatie *s,Publicatie *d){
    if(s->get_citari()>d->get_citari())
    return true;
    else
    return false;
}
class Profil{
    private:
    int n;
    std::vector<Publicatie*> P;
    public:
    Profil(int n):n(n){}
    void afisare(std::string cercetator){
        std::cout<<cercetator<<std::endl;
        for(int i=0;i<P.size();i++){
            P[i]->afisare();
        }
    }
    void sortare(){
        int g=0;
        std::sort(P.begin(),P.end(),sort);
        for(int i=0;i<P.size();i++){
            for(int j=0;j<P.size();j++){
                if(P[i]->get_citari()<P[j]->get_citari()){
                ++g;
                }
                
            }
            if(g==3){
            std::cout<<P[i]->get_citari()<<std::endl;
            break;
        }
        g=0;
        }
    }
    void citari(){
        int nr=0;
        for(int i=0;i<P.size();i++){
            nr=nr+P[i]->citari();
        }
        std::cout<<nr<<std::endl;
    }
    void punctaj(){
        float punctaj=0;
        for(int j=2023;j>=2021;j--){
        for(int i=0;i<P.size();i++){
            if(j==P[i]->get_anul())
            punctaj=punctaj+P[i]->punctaj();
        }
        std::cout<<std::fixed<<std::setprecision(2)<<punctaj<<std::endl;
        punctaj=0;
        }
    }
    void citire(std::string cercetator){
        for(int i=0;i<n;i++){
        std::string titlu,tip;
        int nr_autori,anul,tip_pub;
        long int nr_citari;
        std::cin.ignore();
        std::getline(std::cin,titlu);
        std::cin>>nr_autori;
        std::cin>>anul;
        std::cin>>nr_citari;
        std::cin>>tip;
        if(tip=="conferinta"){
            std::cin>>tip_pub;
            P.push_back(new Conferinta(cercetator,titlu,tip,nr_autori,anul,
            nr_citari,tip_pub));
        }
        else if(tip=="revista"){
            std::cin>>tip_pub;
            P.push_back(new Revista(cercetator,titlu,tip,nr_autori,anul,
            nr_citari,tip_pub));
        }
    }
    }
};

int main(){
    std::string cercetator;
    std::getline(std::cin,cercetator);
    int n,test;
    std::cin>>n;
    Profil Pf(n);
    Pf.citire(cercetator);
    std::cin>>test;
    switch(test){
        case 1:
        Pf.afisare(cercetator);
        break;
        case 2:
        Pf.punctaj();
        break;
        case 3:
        Pf.citari();
        break;
        case 4:
        Pf.sortare();
        break;
    }
}