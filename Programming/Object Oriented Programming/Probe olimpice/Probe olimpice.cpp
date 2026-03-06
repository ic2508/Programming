#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

class ProbaSportiva{
    protected:
    char c;
    std::string proba;
    int nr_part;
    std::string nume;
    float rez;
    public:
    ProbaSportiva(char c, std::string proba, int nr_part, 
    std::string nume, float rez):c(c),proba(proba),nr_part(nr_part),
    nume(nume),rez(rez){}
    virtual void afisare() = 0;
    virtual float get_rez() = 0;
    virtual std::string get_proba() = 0;
    virtual char get_c() = 0;
    virtual std::string get_nume() = 0;
};

class ProbaScor: public ProbaSportiva{
    private:
    public:
    ProbaScor(char c, std::string proba, int nr_part, 
    std::string nume, float rez):ProbaSportiva(c,proba,nr_part,nume,rez){}
    void afisare(){
        std::cout<<nume<<" "<<rez<<std::endl;
    }
    std::string get_proba(){
        return this->proba;
    }
    std::string get_nume(){
        return this->nume;
    }
    float get_rez(){
        return this->rez;
    }
    char get_c(){
        return this->c;
    }
};

class ProbaTimp: public ProbaSportiva{
    private:
    public:
    ProbaTimp(char c, std::string proba, int nr_part, 
    std::string nume, float rez):ProbaSportiva(c,proba,nr_part,nume,rez){}
    void afisare(){
        std::cout<<nume<<" "<<rez<<std::endl;
    }
    std::string get_proba(){
        return this->proba;
    }
    std::string get_nume(){
        return this->nume;
    }
    float get_rez(){
        return this->rez;
    }
    char get_c(){
        return this->c;
    }
};
bool ord(ProbaSportiva *s,ProbaSportiva *d){
        if(s->get_c()=='s'){
        if(s->get_rez()>d->get_rez())
        return true;
        else
        return false;
        }
        if(s->get_c()=='t'){
        if(s->get_rez()<d->get_rez())
        return true;
        else
        return false;
    }
    return 0;
}
class Participant{
    private:
    int n;
    float cnt;
    std::vector<ProbaSportiva*> PS;
    public:
    Participant(int n):n(n){}
    Participant(float cnt):cnt(cnt){}
    void afisare(){
        std::string proba_t = "";
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            if(proba_t != (*i)->get_proba())
            std::cout<<(*i)->get_proba()<<std::endl;
            (*i)->afisare();
            proba_t = (*i)->get_proba();
        }
    }
    
    void rez_med(){
        std::string proba_t = "";
        int k=0;
        float s=0;
        int j=0;
        int nr=0;
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            ++nr;
            if(proba_t != (*i)->get_proba())
            std::cout<<"Rezultat mediu la "<<std::fixed<<std::setprecision(2)<<(*i)->get_proba()<<": ";
            s=s+(*i)->get_rez();
            ++k;
            proba_t = (*i)->get_proba();
            if((i+1)<PS.end()){
            if(proba_t != (*(i+1))->get_proba()){
            std::cout<<s/k<<std::endl;
            k=0;
            s=0;
            }
            }
            else if(nr==PS.size()){
            std::cout<<s/k<<std::endl;
            k=0;
            s=0;
        }
        }
    }
    void clasament(std::string comp){
        std::sort(PS.begin(),PS.end(),ord);
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            if(comp==(*i)->get_proba())
            std::cout<<(*i)->get_nume()<<" "<<(*i)->get_rez()<<std::endl;
        }
    }
    float val(std::string comp,std::string nume){
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            if(comp==(*i)->get_proba()){
                if(nume==(*i)->get_nume()){
                    return (*i)->get_rez();
                }
            }
        }
        return 0;
    }
    void loc(std::string comp,std::string nume,float val){
        float final=0;
        float max1=-32000;
        float min1=32000;
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            if(comp==(*i)->get_proba()){
                if((*i)->get_c()=='s'){
                if((*i)->get_rez()>max1)
                max1=(*i)->get_rez();
                final=max1;
            }
            if((*i)->get_c()=='t'){
                if((*i)->get_rez()<min1)
                min1=(*i)->get_rez();
                final=min1;
            }
            }
        }
        std::cout<<nume<<" "<<((final*2)-val)<<std::endl;
    }
    void record(std::vector<float> val){
        std::string proba_t = "";
        int k=0;
        float s=0;
        int j=0;
        int nr=0;
        int k1=0;
        int k2=0;
        for(std::vector<ProbaSportiva*>::iterator i=PS.begin();
        i!=PS.end();i++){
            ++nr;
            s=s+(*i)->get_rez();
            ++k;
            proba_t = (*i)->get_proba();
            if((i+1)<PS.end()){
            if((*i)->get_c()=='s'){
            if((*i)->get_rez()>val[k1]){
            std::cout<<"Un nou record mondial la "<<(*i)->get_proba()<<"!"<<std::endl;
            ++k1;
            k=0;
            s=0;
            ++k2;
            }
            else if((proba_t != (*(i+1))->get_proba()) && k2==0){
            k=0;
            s=0;
            ++k1;
            k2=0;
            }
            }
            else if((*i)->get_c()=='t'){
            if((*i)->get_rez()<val[k1]){
            std::cout<<"Un nou record mondial la "<<(*i)->get_proba()<<"!"<<std::endl;
            ++k1;
            k=0;
            s=0;
            ++k2;
            }
            else if((proba_t != (*(i+1))->get_proba()) && k2==0){
            k=0;
            s=0;
            ++k1;
            }
            }
            }
            else if(nr==PS.size() && (*i)->get_c()=='s'){
            if((*i)->get_rez()>val[k1]){
            std::cout<<"Un nou record mondial la "<<(*i)->get_proba()<<"!"<<std::endl;
            ++k1;
            k=0;
            s=0;
            }
            else{
            k=0;
            s=0;
            ++k1;
            }
        }
        else if(nr==PS.size() && (*i)->get_c()=='t'){
            if((*i)->get_rez()<val[k1]){
            std::cout<<"Un nou record mondial la "<<(*i)->get_proba()<<"!"<<std::endl;
            k1++;
            k=0;
            s=0;
            }
            else{
            k=0;
            s=0;    
            }
        }
        
    }
    }
    void citire(){
    float cnt=0;
    for(int i=0;i<n;i++){
        char c;
        std::string proba;
        int nr_part;
        std::string nume;
        float rez;
        std::cin>>c;
        std::cin.ignore();
        std::getline(std::cin,proba);
        std::cin>>nr_part;
        std::cin.ignore();
        if(c=='s'){
            for(int i=0;i<nr_part;i++){
            ProbaSportiva *P1;
            std::cin>>nume;
            std::cin>>rez;
            std::cin.ignore();
            P1 = new ProbaScor(c,proba,nr_part,nume,rez);
            PS.push_back(P1);
            ++cnt;
            }
        }
        else if(c=='t'){
            for(int i=0;i<nr_part;i++){
            ProbaSportiva *P1;
            std::cin>>nume;
            std::cin>>rez;
            std::cin.ignore();
            P1 = new ProbaTimp(c,proba,nr_part,nume,rez);
            PS.push_back(P1);
            ++cnt;
            }
        }
    }
    Participant P(cnt);
    }
};


int main(){
    int n,test;
    float x;
    std::cin>>n;
    std::vector<float> val;
    Participant P(n);
    std::cin.ignore();
    P.citire();
    std::cin>>test;
    std::cin.ignore();
    std::string comp,nume;
    switch(test){
        case 1:
        P.afisare();
        break;
        case 2:
        P.rez_med();
        break;
        case 3:
        for(int i=0;i<n;i++){
        std::cin>>x;
        val.push_back(x);
        }
        P.record(val);
        break;
        case 4:
        std::cin>>comp;
        P.clasament(comp);
        break;
        case 5:
        std::cin>>comp;
        std::cin>>nume;
        float val1 = P.val(comp,nume);
        P.loc(comp,nume,val1);
        break;
    }
}