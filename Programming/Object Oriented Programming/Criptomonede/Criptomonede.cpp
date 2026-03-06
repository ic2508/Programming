#include <iostream>
#include <string>
#include <iomanip>
class Criptomoneda{
    private:
    float sold;
    float val_fract,val_curent;
    std::string moneda;
    public:
    Criptomoneda(){}
    Criptomoneda(float sold, float val_fract, float val_curent, std::string moneda){
        this->sold=sold;
        this->val_fract=val_fract;
        this->val_curent=val_curent;
        this->moneda=moneda;
    }
    void frac(float suma){
        this->val_fract=suma;
    }
    
    void afisare(){
             std::cout<<moneda<<" "<<std::fixed<<std::setprecision(2)<<val_fract<<" "<<std::fixed<<std::setprecision(2)<<val_curent<<std::endl;
         }
    void afisare4(float suma){
            std::cout<<moneda<<" "<<std::fixed<<std::setprecision(2)<<suma<<" "<<std::fixed<<std::setprecision(2)<<val_curent<<std::endl;
    }
    void afisare6(){
            std::cout<<moneda<<" "<<std::fixed<<std::setprecision(2)<<val_fract<<" "<<std::fixed<<std::setprecision(2)<<val_curent<<std::endl;
    }
    std::string get_moneda(){
        return moneda;
    }
    float get_val_fract(){
        return val_fract;
    }
    float get_val_curent(){
        return val_curent;
    }
};

class Portofel{
    friend class Criptomoneda;
    private:
    float sold;
    Criptomoneda v[10];
    public:
    Portofel(){}
    void port(float sold, float val_fract, float val_curent, std::string cripto,int n,Criptomoneda C[]){
        for(int i=0;i<n;i++){
            v[i] = C[i];
        }   
    }
    void port1(float sold, float val_fract, float val_curent, std::string cripto,int n,Criptomoneda C[],int k){
            v[k] = C[k];
    }
    void afisare2(int n){
        for(int i=0;i<n;i++){
        v[i].afisare();
        }
    }
    void afisare3(int n,int k,float suma){
        v[k].afisare4(suma);
        }
        void atribuie(int k, Criptomoneda C[]){
            v[k]=C[k];
        }
       void afisare5(int n){
        for(int i=0;i<n;i++){
        v[i].afisare6();
        }
    }
};

void soldare(float &sold1){
        std::cout<<sold1<<std::endl;
    }

int main(){
    float sold;
    int n;
    std::cin>>sold;
    std::cin>>n;
    std::cin.ignore();
    int test;
    Portofel P;
    Criptomoneda C[n];
    std::string cripto;
    float val_fract,val_curent;
    std::string n1_cripto;
    float n1_val_fract;
    float suma1=0;
    float suma=0;
    std::string n_cripto;
    float n_val_fract;
    int nr;
    std::string tranzactie;
    std::string n2_cripto;
    float t_val_fract;
   
    for(int i=0;i<n;i++){
        std::cin>>cripto;
        std::cin>>val_fract;
        std::cin>>val_curent;
        std::cin.ignore();
        C[i] = Criptomoneda(sold,val_fract,val_curent,cripto);
    }
    std::cin>>test;
    std::cin.ignore();
    P.port(sold,val_fract,val_curent,cripto,n,C);
    switch(test){
        case 1:
        std::cout<<std::fixed<<std::setprecision(2)<<sold<<std::endl;
        P.afisare2(n);
        break;
        case 2:
        std::cin>>n_cripto;
        std::cin>>n_val_fract;
        for(int i=0;i<n;i++){
            if(n_cripto==C[i].get_moneda()){
                if(n_val_fract*C[i].get_val_curent()<=sold){
                suma=C[i].get_val_fract()+n_val_fract;
                P.afisare3(n,i,suma);
            }
            else{
               suma=(sold / C[i].get_val_curent()+C[i].get_val_fract());
                P.afisare3(n,i,suma);
            }
            }
        }
        break;
        case 3:
        std::cin>>n1_cripto;
        std::cin>>n1_val_fract;
        for(int i=0;i<n;i++){
            if(n1_cripto==C[i].get_moneda()){
                if(C[i].get_val_fract()>n1_val_fract){
                suma1=C[i].get_val_fract()-n1_val_fract;
                P.afisare3(n,i,suma1);
            }
            else{
               suma1=0;
               P.afisare3(n,i,suma1);
            }
            }
        }
       break;
       case 4:
       std::cin>>nr;
       std::cin.ignore();
       float sold2=sold;
       for(int j=0;j<nr;j++){
           std::cin>>tranzactie>>t_val_fract>>n2_cripto;
           std::cin.ignore();
           if(tranzactie=="cumpara"){
            for(int i=0;i<n;i++){
            if(n2_cripto==C[i].get_moneda()){
                if(t_val_fract*C[i].get_val_curent()<=sold2){
                suma=C[i].get_val_fract()+t_val_fract;
                sold2=sold2-(t_val_fract*C[i].get_val_curent());
                C[i].frac(suma);
                P.port1(sold2,suma,val_curent,cripto,n,C,i);
            }
            else{
               suma=(sold2 / C[i].get_val_curent()+C[i].get_val_fract());
               sold2=0;
               C[i].frac(suma);
               P.port1(sold2,suma,val_curent,cripto,n,C,i);
            }
            }
            }    
           }
           if(tranzactie=="vinde"){
           for(int k=0;k<n;k++){
            if(n2_cripto==C[k].get_moneda()){
                if(C[k].get_val_fract()<t_val_fract){
                suma1=0;
                sold2=sold2+(C[k].get_val_fract()*C[k].get_val_curent());
                C[k].frac(suma1);
                P.port1(sold2,suma1,val_curent,cripto,n,C,k);
            }
            else{
               suma1=C[k].get_val_fract()-t_val_fract;
               C[k].frac(suma1);
               P.port1(sold2,suma1,val_curent,cripto,n,C,k);
            }
            }
        }    
           }
       }
       soldare(sold2);
       P.afisare5(n);
       break;
    }
}