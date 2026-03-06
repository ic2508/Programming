#include <iostream>
#include <string>
#include <iomanip>

class Echipa{
    private:
    std::string echipa;
    int vic,egal,inf;
    public:
    Echipa(){}
    Echipa(std::string echipa, int vic,int egal,int inf){
        this->echipa=echipa;
        this->vic=vic;
        this->egal=egal;
        this->inf=inf;
    }
    void afis(){
        std::cout<<this->echipa<<" "<<this->vic<<" "<<this->egal<<" "<<this->inf<<std::endl;
    }
    int victorii(){
    int punctaj=(this->vic*3)+(this->egal*1)+(this->inf*0);
    return punctaj;
    }
    void vict(int scor){
        std::cout<<this->echipa<<" "<<scor<<std::endl;
    }
};

class Liga{
    private:
    int n;
    Echipa v[10];
    public:
    Liga(){}
    Liga(int n){
        this->n=n;
    }
    void apend(int i,std::string echipa, int vic,int egal,int inf){
        v[i] = Echipa(echipa,vic,egal,inf);
    }
    void afis1(int index){
    //std::cout<<6;
    v[index].afis();
}
};

int main(){
    int n;
    std::cin>>n;
    Echipa v[n];
    Liga L(n);
    for(int i=0;i<n;i++){
        std::string echipa;
        int vic,egal,inf;
        std::cin>>echipa>>vic>>egal>>inf;
        std::cin.ignore();
        v[i]=Echipa(echipa,vic,egal,inf);
        L.apend(i,echipa,vic,egal,inf);
    }
    int test;
    int scor;
    std::cin>>test;
    std::cin.ignore();
    switch(test){
        case 1:
        for(int i=0;i<n;i++)
        L.afis1(i);
        break;
        case 2:
        for(int i=0;i<n;i++){
        scor = v[i].victorii();
        v[i].vict(scor);
    }
        break;
    }
    
}