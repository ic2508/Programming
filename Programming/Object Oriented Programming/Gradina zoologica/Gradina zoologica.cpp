#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

class Pasare{
    protected:
    std::string nume;
    int dimensiune;
    char c;
    public:
    Pasare(std::string nume, int dimensiune, char c):
    nume(nume),dimensiune(dimensiune),c(c){}
    virtual void afisare()=0;
    virtual void afis_suprafata()=0;
    virtual float supra()=0;
    char get_c(){
        return this->c;
    }
    int get_dimensiune(){
        return this->dimensiune;
    }
};

class Zburatoare: public Pasare{
    private:
    int batai_pe_minut;
    public:
    Zburatoare(std::string nume,int dimensiune, char c, int batai_pe_minut):
    Pasare(nume,dimensiune,c),batai_pe_minut(batai_pe_minut){}
    void afisare(){
        std::cout<<this->nume<<" "<<this->dimensiune<<" "
        <<this->batai_pe_minut<<std::endl;
    }
    float supra(){
        return ((this->dimensiune*110*this->batai_pe_minut)/100);
    }
    void afis_suprafata(){
        std::cout<<this->nume<<" "<<((this->dimensiune*110*this->batai_pe_minut)/100)
        <<std::endl;
    }
};

class Nezburatoare: public Pasare{
    private:
    std::string culoare;
    public:
    Nezburatoare(std::string nume,int dimensiune, char c,std::string culoare):
    Pasare(nume,dimensiune,c),culoare(culoare){}
    void afisare(){
        std::cout<<this->nume<<" "<<this->dimensiune<<" "
        <<this->culoare<<std::endl;
    }
    float supra(){
        return (this->dimensiune*30);
    }
    void afis_suprafata(){
        std::cout<<this->nume<<" "<<(this->dimensiune*30)
        <<std::endl;
    }
};
bool suprafata(Pasare *s, Pasare *d){
    if(s->supra()<d->supra())
    return true;
    else
    return false;
}
class Manager{
    private:
    std::vector<Pasare*> P;
    int n;
    public:
    Manager(int n):n(n){}
    void afisare(){
        for(int i=0;i<P.size();i++){
            P[i]->afisare();
        }
    }
    void afis_crit(char c_test, int dim_min){
        for(int i=0;i<P.size();i++){
            if(c_test==P[i]->get_c() && dim_min<P[i]->get_dimensiune())
            P[i]->afisare();
        }
    }
    void sup(){
        for(int i=0;i<P.size();i++){
            P[i]->afis_suprafata();
        }
    }
    void sortare(){
        std::sort(P.begin(),P.end(),suprafata);
        for(int i=0;i<P.size();i++){
            P[i]->afisare();
        }
    }
    void sup_min(){
        float sum1 = 0;
        float sum2 = 0;
        for(int i=0;i<P.size();i++){
            if(P[i]->get_c()=='z')
            sum1=sum1+P[i]->supra();
            else if(P[i]->get_c()=='n')
            sum2=sum2+P[i]->supra();
        }
        if(sum1>sum2)
        std::cout<<sum1;
        else if(sum2<sum1)
        std::cout<<sum2;
    }
    void citire(){
        for(int i=0;i<n;i++){
            char c;
            std::string nume,culoare;
            int dim,batai;
            std::cin>>c;
            std::cin>>nume;
            std::cin>>dim;
            if(c=='z'){
                std::cin>>batai;
                P.push_back(new Zburatoare(nume,dim,c,batai));
            }
            else if(c=='n'){
                std::cin>>culoare;
                P.push_back(new Nezburatoare(nume,dim,c,culoare));
            }
        }
    }
};

int main(){
    int n,test,dim_min;
    char c_test;
    std::cin>>n;
    Manager M(n);
    M.citire();
    std::cin>>test;
    std::cin.ignore();
    switch(test){
        case 1:
        M.afisare();
        break;
        case 2:
        std::cin>>c_test;
        std::cin>>dim_min;
        M.afis_crit(c_test,dim_min);
        break;
        case 3:
        M.sup();
        break;
        case 4:
        M.sortare();
        break;
        case 5:
        M.sup_min();
        break;
    }
}
