#include <iostream>
#include <string>
#include <iomanip>


class Produs{
    private:
    std::string denumire;
    int pret;
    int nr_ramas;
    public:
    Produs(){}
    Produs(std::string denumire,int pret, int nr_ramas){
        this->denumire=denumire;
        this->pret=pret;
        this->nr_ramas=nr_ramas;
    }
    void afisare(){
        if(this->nr_ramas==0){
        return;
        }
        std::cout<<this->denumire<<std::endl;
        std::cout<<this->pret<<std::endl;
        std::cout<<this->nr_ramas<<std::endl;
    }
    std::string get_denumire(){
        return this->denumire;
    }
    int get_nr_ramas(){
        return this->nr_ramas;
    }
    int get_pret(){
        return this->pret;
    }
};
class Cos_cumparaturi{
    private:
    int nr_produse;
    std::string produse;
    public:
    Cos_cumparaturi(){}
    Cos_cumparaturi(int nr_produse, std::string produse){
        this->nr_produse=nr_produse;
        this->produse=produse;
    }
    int plata_cos(Produs P[],int i,int cnt){
        int k=0;
        for(int j=0;j<cnt;j++){
            if(this->produse==P[j].get_denumire()){
                if(this->nr_produse<=P[j].get_nr_ramas()){
                    return 0;
                }
                    else{
                    std::cout<<"Produsul "<<P[j].get_denumire()<<" mai are doar "<<P[j].get_nr_ramas()<<" bucati in stoc"<<std::endl;
                    ++k;
                    return k;
            }
        }
    }
    return 0;
    }
    int indice(Produs P[],int i,int cnt){
        for(int j=0;j<cnt;j++){
            if(this->produse==P[j].get_denumire()){
                if(this->nr_produse<=P[j].get_nr_ramas()){
                    return j;
                }
    }
        }
        return 0;
    }
    int get_nr_produse(){
        return this->nr_produse;
    }
};
class Reducere{
    private:
    std::string produse1;
    int nr_produse1,procent,cap_jos,cap_sus;
    public:
    Reducere(){}
    Reducere(int nr_produse1, std::string produse1){
        this->nr_produse1=nr_produse1;
        this->produse1=produse1;
    }
    Reducere(int procent,int cap_jos,int cap_sus){
        this->procent=procent;
        this->cap_jos=cap_jos;
        this->cap_sus=cap_sus;
    }
    void afis(){
        std::cout<<procent<<std::endl;
    }
    int reducere(Produs P[],int i,int cnt){
        int k=0;
        for(int j=0;j<cnt;j++){
            if(this->produse1==P[j].get_denumire()){
                if(this->nr_produse1<=P[j].get_nr_ramas()){
                    return 0;
                }
                    else{
                    std::cout<<"Produsul "<<P[j].get_denumire()<<" mai are doar "<<P[j].get_nr_ramas()<<" bucati in stoc"<<std::endl;
                    ++k;
                    return k;
            }
        }
    }
    return 0;
    }
    int indice(Produs P[],int i,int cnt){
        for(int j=0;j<cnt;j++){
            if(this->produse1==P[j].get_denumire()){
                if(this->nr_produse1<=P[j].get_nr_ramas()){
                    return j;
                }
    }
        }
        return 0;
    }
    int get_nr_produse1(){
        return this->nr_produse1;
    }
    int get_cap_jos(){
        return this->cap_jos;
    }
    int get_cap_sus(){
        return this->cap_sus;
    }
    int get_procent(){
        return this->procent;
    }
};

class Magazin{
    private:
    Produs P[10];
    Cos_cumparaturi C[10];
    Reducere R[10];
    public:
    Magazin(){}
};
int v[3];
int main(){
    Magazin M;
    Produs P[10];
    Cos_cumparaturi C[10];
    Reducere R[10];
    Reducere R1[10];
    int pr,test,cnt=0,cnt2=0,k2=0,k3=0,nr_produse,nr_produse1;
    //std::cin>>pr;
    //std::cin.ignore();
    for(int i=0;i<10;i++){
        std::string denumire;
        int pret;
        int nr_ramas;
        std::getline(std::cin,denumire);
        if(denumire=="STOP"){
        break;
        }
        std::cin>>pret;
        std::cin>>nr_ramas;
        std::cin.ignore();
        P[i] = Produs(denumire,pret,nr_ramas);
        cnt++;
    }
    std::cin>>test;
    std::string produse;
    std::string produse1;
    std::cin.ignore();
    int plata=0,plata1=0;
    int suma=0;
    int procent,cap_jos,cap_sus;
    switch(test){
        case 1:
        for(int i=0;i<cnt;i++){
            P[i].afisare();
        }
        break;
        case 2:
        for(int i=0;i<10;i++){
        std::getline(std::cin,produse);
        if(produse=="STOP"){
        break;
        }
        std::cin>>nr_produse;
        std::cin.ignore();
        C[i]=Cos_cumparaturi(nr_produse,produse);
        cnt2++;
        }
        for(int i=0;i<cnt2;i++){
            int k1 = C[i].plata_cos(P,i,cnt);
            int indice = C[i].indice(P,i,cnt);
            if(k1==0){
                plata=plata+C[i].get_nr_produse()*P[indice].get_pret();
                k2++;
        }
        if(k2==cnt2){
            std::cout<<"Total de plata"<<std::endl;
            std::cout<<plata<<std::endl;
        }
        }
        break;
        case 3:
        
        std::cin>>procent>>cap_jos>>cap_sus;
        std::cin.ignore();
        for(int i=0;i<10;i++){
        std::getline(std::cin,produse1);
        if(produse1=="STOP"){
        break;
        }
        std::cin>>nr_produse1;
        std::cin.ignore();
        R[i]=Reducere(nr_produse1,produse1);
        cnt2++;
        }
        for(int i=0;i<cnt2;i++){
            int k1 = R[i].reducere(P,i,cnt);
            int indice1 = R[i].indice(P,i,cnt);
            if(k1==0){
                //std::cout<<C[i].get_nr_produse()<<" ";
                if(P[indice1].get_pret()<=cap_sus && P[indice1].get_pret()>=cap_jos){
                suma=((P[indice1].get_pret()*procent)/100);
                int suma1=(P[indice1].get_pret()-suma);
                plata1=plata1+(R[i].get_nr_produse1()*suma1);
               // std::cout<<plata1<<" ";
                k2++;
                }
                else{
                plata1=plata1+(R[i].get_nr_produse1()*P[indice1].get_pret());
                k2++;
                 k3++;
                }
         if(k2==cnt2 && k3!=cnt2){
            std::cout<<"Total de plata"<<std::endl;
            std::cout<<plata1<<std::endl;
        }        
        else if(k2==cnt2 && k3==cnt2){
            std::cout<<"Niciun produs nu e eligibil pentru reducere"<<std::endl;
            std::cout<<"Total de plata"<<std::endl;
            std::cout<<plata1<<std::endl;
        }
        }
        }
        break;
        case 4:
        
        for(int i=0;i<3;i++){
        std::cin>>procent>>cap_jos>>cap_sus;
        std::cin.ignore();
        R1[i]=Reducere(procent,cap_jos,cap_sus);
        //R1[i].afis();
        }
        for(int i=0;i<10;i++){
        std::getline(std::cin,produse1);
        if(produse1=="STOP"){
        break;
        }
        std::cin>>nr_produse1;
        std::cin.ignore();
        R[i]=Reducere(nr_produse1,produse1);
        cnt2++;
        }
        for(int h=0;h<3;h++){
        for(int i=0;i<cnt2;i++){
            int k1 = R[i].reducere(P,i,cnt);
            int indice1 = R[i].indice(P,i,cnt);
            if(k1==0){
                //std::cout<<C[i].get_nr_produse()<<" ";
                if(P[indice1].get_pret()<=R1[h].get_cap_sus() && P[indice1].get_pret()>=R1[h].get_cap_jos()){
                suma=((P[indice1].get_pret()*R1[h].get_procent())/100);
                //std::cout<<R[h].get_procent()<<" ";
                int suma1=(P[indice1].get_pret()-suma);
                plata1=plata1+(R[i].get_nr_produse1()*suma1);
                //std::cout<<plata1<<" ";
                k2++;
                }
                else{
                plata1=plata1+(R[i].get_nr_produse1()*P[indice1].get_pret());
                //std::cout<<plata1<<"  ";
                k2++;
                k3++;
                }
         if(k2==cnt2 && k3!=cnt2){
            v[h]=plata1;
           // std::cout<<plata1<<" ";
        }        
        else if(k2==cnt2 && k3==cnt2){
            v[h]=plata1;
            //std::cout<<plata1<<" ";
        }
        }
        }
        k2=0;
        k3=0;
        plata1=0;
        }
        for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2 - i; ++j) {
            // Compară elementele adiacente și le interschimbă dacă este necesar
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
        }
       //int aux=0;
       //int j;
       //for(int i=0;i<1;i++){
       //    for(j=i+1;j<2;j++){
       //        if(v[i]>v[j])
       //        aux=v[i];
       //        v[i]=v[j];
       //        v[j]=aux;
       //    }
       //}
        std::cout<<"Total de plata"<<std::endl;
        std::cout<<v[0]<<std::endl;
        break;
        case 5:
        int proc;
        for(int i=0;i<3;i++){
        std::cin>>procent>>cap_jos>>cap_sus;
        std::cin.ignore();
        R1[i]=Reducere(procent,cap_jos,cap_sus);
        }
        for(int i=0;i<10;i++){
        std::getline(std::cin,produse1);
        if(produse1=="STOP"){
        break;
        }
        std::cin>>nr_produse1;
        std::cin.ignore();
        R[i]=Reducere(nr_produse1,produse1);
        cnt2++;
        }
        for(int i=0;i<cnt2;i++){
            int k1 = R[i].reducere(P,i,cnt);
            int indice1 = R[i].indice(P,i,cnt);
            if(k1==0){
                for(int h=0;h<3;h++){
                if(P[indice1].get_pret()<=R1[h].get_cap_sus() && P[indice1].get_pret()>=R1[h].get_cap_jos()){
                        for(int d=0;d<3;d++){
                            if(R1[h].get_procent()<R1[d].get_procent())
                            proc=R1[d].get_procent();
                        }
                    }
                suma=((P[indice1].get_pret()*R1[h].get_procent())/100);
                int suma1=(P[indice1].get_pret()-suma);
                plata1=plata1+(R[i].get_nr_produse1()*suma1);
                k2++;
                }
            }
                else{
                plata1=plata1+(R[i].get_nr_produse1()*P[indice1].get_pret());
                k2++;
                k3++;
                }
         if(k2==cnt2 && k3!=cnt2){
            v[i]=plata1;
        }        
        else if(k2==cnt2 && k3==cnt2){
            v[i]=plata1;
        }
        }
        
        k2=0;
        k3=0;
        plata1=0;
        for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2 - i; ++j) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
        }
        std::cout<<"Total de plata"<<std::endl;
        for(int i=0;i<3;i++){
        std::cout<<v[i]<<std::endl;
        }
        break;
    }
}