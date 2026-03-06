#include <iostream>
#include <iomanip>
#include <string>

class Profil{
    private:
    std::string nume;
    int ID;
    int anul, luna, ziua;
    public:
    Profil(){}
    Profil(std::string nume,int anul,int luna,int ziua,int ID){
        this->nume=nume;
        this->anul=anul;
        this->luna=luna;
        this->ziua=ziua;
        this->ID=ID;
    }
    void afisare(){
        std::cout<<this->ID<<std::endl;
        std::cout<<this->nume<<std::endl;
        std::cout<<this->anul<<" "<<this->luna<<" "<<this->ziua<<std::endl;
    }
    void ver_data(){
        if(this->anul>=1900 && this->anul<=2021 && 
        this->luna>=1 && this->luna<=12 && this->ziua>=1 && this->ziua<=30){
            std::cout<<this->ID<<std::endl;
            std::cout<<this->anul<<" "<<this->luna<<" "<<this->ziua<<std::endl;
        }
        else{
        std::cout<<this->ID<<std::endl;
        std::cout<<"EROARE: Data de nastere introdusa nu e valida"<<std::endl;
        }
    }
    void calc_varst(int anul1, int luna1, int ziua1){
        if(this->anul>=1900 && this->anul<=2021 && 
        this->luna>=1 && this->luna<=12 && this->ziua>=1 && this->ziua<=30){
            if(this->anul<=anul1 && this->luna<=luna1 && this->ziua<=ziua1 && (anul1-this->anul)>=18){
                std::cout<<this->nume<<std::endl;
                std::cout<<(anul1-this->anul)<<std::endl;
            }
            else if(this->anul<=anul1 && this->luna<=luna1 && this->ziua>=ziua1 && ((anul1-1)-this->anul)>=18){
                std::cout<<this->nume<<std::endl;
                std::cout<<((anul1)-this->anul)<<std::endl;
            }
            else if(this->anul<=anul1 && this->luna>=luna1 && ((anul1-1)-this->anul)>=18){
                std::cout<<this->nume<<std::endl;
                std::cout<<((anul1-1)-this->anul)<<std::endl;
            }
        }
    }
    int calc_varst1(int anul2, int luna2, int ziua2, int anul1, int luna1, int ziua1){
        if(anul1>=1900 && anul1<=2021 && 
        luna1>=1 && luna1<=12 && ziua1>=1 && ziua1<=30){
            if(anul1<=anul2 && luna1<=luna2 && ziua1<=ziua2 && (anul2-anul1)>=18){
                return (anul2-anul1);
            }
            else if(anul1<=anul2 && luna1<=luna2 && ziua1>=ziua2 && (anul2-anul1)>=18){
                return (anul2-anul1);
            }
            else if(anul1<=anul2 && luna1>=luna2 && ((anul2-1)-anul1)>=18){
                return ((anul2-1)-anul1);
            }
        }
        return 0;
    }
    int get_an(){
        return this->anul;
    }
    int get_luna(){
        return this->luna;
    }
    int get_zi(){
        return this->ziua;
    }
    std::string get_nume(){
        return this->nume;
    }
    int get_ID(){
        return this->ID;
    }
    
    void afis_postari(int ID1, int min1, int max1,int ut,std::string text, int &k,int postari,int v, Profil A[],int g1,int v1,int &k1,int &ok1, int &ok2){
            
            if((v<=max1 && v>=min1) || ID1==A[g1].get_ID()){
                if(k1==0){
                std::cout<<"News Feed"<<std::endl;
                }
                std::cout<<A[ID1].get_nume()<<std::endl;
                std::cout<<text<<std::endl;
                ok1=1;
                k1++;
            }
            else if(v<=max1 && v>=min1){
                if(k1==0){
                std::cout<<"News Feed"<<std::endl;
                }
                std::cout<<A[ID1].get_nume()<<std::endl;
                std::cout<<text<<std::endl;
                ok2=1;
                k1++;
            }
            k++;
            if((k+1)==postari && ok1==0 && ok2==0){
                std::cout<<"News Feed"<<std::endl;
                std::cout<<"No posts for you"<<std::endl;
            }
            
        }
};

class Post{
    private:
    std::string text;
    public:
    Post(){}
    Post(std::string text){
        this->text=text;
    }
    std::string get_text(){
        return this->text;
    }
};

class Website{
    private:
    Profil A[10];
    public:
    Website(){}
};

int main(){
    int ut;
    std::cin>>ut;
    std::string nume;
    std::cin.ignore();
    int test,anul,luna,ziua;
    int anul1,luna1,ziua1;
    int anul2,luna2,ziua2;
    int postari, ID1, min1, max1;
    int g;
    std::string text;
    Profil A[ut];
    Website B;
    for(g=0;g<ut;g++){
        std::getline(std::cin,nume);
        std::cin>>anul>>luna>>ziua;
        std::cin.ignore();
        A[g] = Profil(nume,anul,luna,ziua,g);
    }
    std::cin>>test;
    std::cin.ignore();
    switch(test){
        case 1:
        for(int i=0;i<ut;i++){
            A[i].afisare();
        }
        break;
        case 2:
        for(int i=0;i<ut;i++){
            A[i].ver_data();
        }
        break;
        case 3:
        for(int i=0;i<ut;i++){
            std::cin>>anul1>>luna1>>ziua1;
            A[i].calc_varst(anul1,luna1,ziua1);
        }
        break;
        case 4:
        int g1=0;
        int k1=-1;
        int c=0, ok1=0,ok2=0;;
        std::cin>>anul2>>luna2>>ziua2;
        std::cin>>postari;
        Post P[postari];
        std::cin.ignore();
        for(int i=0;i<postari;i++){
            std::cin>>ID1;
            std::cin>>min1>>max1;
            std::cin.ignore();
            std::getline(std::cin,text);
            P[ID1]=Post(text);
            int v = A[i].calc_varst1(anul2,luna2,ziua2,A[0].get_an(),A[0].get_luna(),A[0].get_zi());
            int v1 = A[i].calc_varst1(anul2,luna2,ziua2,A[i].get_an(),A[i].get_luna(),A[i].get_zi());
            A[i].afis_postari(ID1,min1,max1,ut,P[ID1].get_text(),k1,postari,v,A,g1,v1,c,ok1,ok2);
            g1++;
        }
        break;
    }
}