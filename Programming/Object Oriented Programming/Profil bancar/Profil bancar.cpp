#include <iostream>
#include <string>
#include <iomanip>

class Card{
    private:
    //int nr
    float sold_card;
    public:
    Card(){}
    Card(float sold_card){
        this->sold_card=sold_card;
    }
    void afisare_c(){
        std::cout<<"card_bancar:"<<std::endl;
        std::cout<<this->sold_card<<std::endl;
    }
    void bani(float nr1){
        this->sold_card=this->sold_card+nr1;
        std::cout<<"card_bancar:"<<std::endl;
        std::cout<<this->sold_card<<std::endl;
    }
    void depunere(float nr1){
        this->sold_card=this->sold_card-nr1;
        std::cout<<"card_bancar:"<<std::endl;
        std::cout<<this->sold_card<<std::endl;
    }
    void depunere2(float nr1){
        this->sold_card=this->sold_card-nr1;
    }
    float get_sold(){
        return sold_card;
    }
};



class Cont_economii{
    private:
    float sold_economii, dob_economii;
    public:
    Cont_economii(){}
    Cont_economii(float sold_economii,float dob_economii){
        this->sold_economii=sold_economii;
        this->dob_economii=dob_economii;
    }
    void afisare_e(){
        std::cout<<"cont_economii:"<<std::endl;
        std::cout<<this->sold_economii<<std::endl;
        std::cout<<this->dob_economii<<std::endl;
    }
    void transfer(int nr1){
        this->sold_economii=(this->sold_economii+nr1);
        float c = 1+(this->dob_economii/100);
        this->sold_economii=this->sold_economii*c;
    }
    void transfer(){
        float c = 1+(this->dob_economii/100);
        this->sold_economii=this->sold_economii*c;
    }
    float sold_economii1(){
        return this->sold_economii;
    }
};

class Profil{
    private:
    Cont_economii *E1;
    Card *C1;
    std::string titular;
    public:
    Profil(){}
    Profil(std::string titular, float sold_card, float sold_economii, float dob_economii)
        : titular(titular), E1(new Cont_economii(sold_economii, dob_economii)), C1(new Card(sold_card)) {}
    Cont_economii* get_Cont_economii(){
        return E1;
    }
    Card* get_card(){
        return C1;
    }
    ~Profil(){
        delete [] E1;
        delete [] C1;
    }
    void afisare_p(){
        std::cout<<this->titular<<std::endl;
    }
    
};

int main(){
    std::string titular;
    float sold_card, sold_economii, dob_economii;
    int test;
    std::getline(std::cin,titular);
    std::cin>>sold_card>>sold_economii>>dob_economii;
    std::cin>>test;
    std::cin.ignore();
    Profil P;
    Profil P1(titular,sold_card,sold_economii,dob_economii);
    float nr1;
    switch(test){
        case 1:
        P1.afisare_p();
        P1.get_card()->afisare_c();
        P1.get_Cont_economii()->afisare_e();
        break;
        case 2:
        std::cin>>nr1;
        if(nr1<0)
        std::cout<<"EROARE: depunere suma negativa";
        else if(nr1>=0){
            P1.get_card()->bani(nr1);
        }
        break;
        case 3:
        std::cin>>nr1;
        if(nr1>P1.get_card()->get_sold())
        std::cout<<"EROARE: fonduri insuficiente";
        else if(nr1<=P1.get_card()->get_sold()){
            P1.get_card()->depunere(nr1);
        }
        break;
        case 4:
        std::cin>>nr1;
        if(nr1>P1.get_card()->get_sold())
        std::cout<<"EROARE: fonduri insuficiente";
        else if(nr1<=P1.get_card()->get_sold()){
            P1.get_card()->depunere2(nr1);
            P1.get_Cont_economii()->transfer(nr1);
        P1.get_card()->afisare_c();
        P1.get_Cont_economii()->afisare_e(); 
        }
        break;
        case 5:
        std::cin>>nr1;
        if(nr1<0)
        std::cout<<"EROARE: fonduri insuficiente";
        else if(nr1>=0){
            int luni=0;
            float suma = P1.get_Cont_economii()->sold_economii1();
            while(suma<nr1){
            //P1.get_card()->depunere2(suma);
            P1.get_Cont_economii()->transfer();
            luni++;
            suma = P1.get_Cont_economii()->sold_economii1();
            }
            std::cout<<luni<<std::endl;
        }
        break;
    }
    
}