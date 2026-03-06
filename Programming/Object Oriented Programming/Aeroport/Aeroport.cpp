#include <iostream>
#include <string>
#include <iomanip>


class Zbor{
    private:
    std::string oras1,oras2;
    int ora_p1,ora_p2;
    int ora_s1,ora_s2;
    float nr;
    public:
    Zbor(){}
    Zbor(std::string oras1, std::string oras2, int ora_p1,int ora_p2,int ora_s1,int ora_s2){
        this->oras1=oras1;
        this->oras2=oras2;
        this->ora_p1=ora_p1;
        this->ora_p2=ora_p2;
        this->ora_s1=ora_s1;
        this->ora_s2=ora_s2;
    }
    Zbor(float nr){
        this->nr=nr; 
    }
    void afisare1(){
        std::cout<<this->oras1<<" - "<<this->oras2<<std::endl;
    }
    void afisare(){
        std::cout<<this->oras1<<" - "<<this->oras2<<std::endl;
        std::cout<<this->ora_p1<<":"<<this->ora_p2<<" - "<<this->ora_s1<<":"<<this->ora_s2<<std::endl;
    }
    void afis_vit(){
        std::cout<<std::fixed<<std::setprecision(2)<<this->nr<<std::endl;
    }
    std::string get_oras1(){
        return this->oras1;
    }
    std::string get_oras2(){
        return this->oras2;
    }
    int get_ora_p1(){
        return this->ora_p1;
    }
    int get_ora_p2(){
        return this->ora_p2;
    }
    int get_ora_s1(){
        return this->ora_s1;
    }
    int get_ora_s2(){
        return this->ora_s2;
    }
};

class Aeroport{
    private:
    int n;
    Zbor z[10];
    Zbor z1[10];
    public:
    Aeroport(){}
    Aeroport(int n){
        this->n=n;
    }
    Zbor& get_zbor(int i){
        return z[i];
    }
    Zbor& get_zbor1(int i){
        return z1[i];
    }
};

int main(){
    int n,test,x;
    int ora_p1,ora_p2;
    int ora_s1,ora_s2;
    std::string oras1;
    std::string oras2;
    std::cin>>n;
    std::cin.ignore();
    Zbor z[n];
    Zbor z1[n];
    Aeroport A1;
    Aeroport A(n);
    for(int i=0;i<n;i++){
        std::cin>>oras1;
        std::cin>>oras2;
        std::cin>>ora_p1>>ora_p2;
        std::cin>>ora_s1>>ora_s2;
        std::cin.ignore();
        A.get_zbor(i) = Zbor(oras1,oras2,ora_p1,ora_p2,ora_s1,ora_s2);
    }
    std::cin>>test;
    std::cin.ignore();
    int t11,t12,t21,t22,nr;
    float timp;
    float v_zbor;
    float suma;
    switch(test){
    case 1:
        std::cin>>x;
        for(int i=0;i<n;i++){
        if(x==0 && A.get_zbor(i).get_oras1()==A.get_zbor(x).get_oras1())
        A.get_zbor(i).afisare();
        if(x==1 && A.get_zbor(i).get_oras2()==A.get_zbor(x).get_oras2())
        A.get_zbor(i).afisare();
        }
    break;
    case 2:
    std::cin>>t11>>t12;
    std::cin>>t21>>t22;
    for(int i=0;i<n;i++){
        if(A.get_zbor(i).get_ora_p1()>=t11 && A.get_zbor(i).get_ora_p2()>=t12 && 
        A.get_zbor(i).get_ora_s1()<=t21 && A.get_zbor(i).get_ora_s2()<=t22)
        A.get_zbor(i).afisare();
    }
    break;
    case 3:
    for(int i=0;i<n;i++){
    std::cin>>nr;
    if(A.get_zbor(i).get_ora_p2()>=A.get_zbor(i).get_ora_s2())
    timp=(((A.get_zbor(i).get_ora_s1()-A.get_zbor(i).get_ora_p1())*60)-(A.get_zbor(i).get_ora_p2() - A.get_zbor(i).get_ora_s2()));
    else if(A.get_zbor(i).get_ora_p2()<=A.get_zbor(i).get_ora_s2())
    timp=(((A.get_zbor(i).get_ora_s1()-A.get_zbor(i).get_ora_p1())*60)+(A.get_zbor(i).get_ora_s2() - A.get_zbor(i).get_ora_p2()));
    v_zbor=(nr/(timp/60));
    //std::cout<<v_zbor<<std::endl;
     A.get_zbor1(i) = Zbor(v_zbor);
    }
    for(int i=0;i<n;i++){
        A.get_zbor(i).afisare();
        A.get_zbor1(i).afis_vit();
    }
    break;
    case 4:
    for(int i=0;i<n;i++){
    std::cin>>nr;
    if(A.get_zbor(i).get_ora_p2()>=A.get_zbor(i).get_ora_s2())
    timp=(((A.get_zbor(i).get_ora_s1()-A.get_zbor(i).get_ora_p1())*60)-(A.get_zbor(i).get_ora_p2() - A.get_zbor(i).get_ora_s2()));
    else if(A.get_zbor(i).get_ora_p2()<=A.get_zbor(i).get_ora_s2())
    timp=(((A.get_zbor(i).get_ora_s1()-A.get_zbor(i).get_ora_p1())*60)+(A.get_zbor(i).get_ora_s2() - A.get_zbor(i).get_ora_p2()));
    //v_zbor=(nr/(timp/60));
    suma=((400*0.15*nr)-(10000*(timp/60)));
     //std::cout<<suma<<std::endl;
     A.get_zbor1(i) = Zbor(suma);
     timp=0;
    }
    for(int i=0;i<n;i++){
        A.get_zbor(i).afisare1();
        A.get_zbor1(i).afis_vit();
    }
    break;
}
}