#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>

class Camera{
    private:
    int nr_cam,nr_pers;
    std::string tip_cam;
    float pret;
    public:
    Camera(int nr_cam,std::string tip_cam,int nr_pers,
    float pret):nr_cam(nr_cam),tip_cam(tip_cam),
    nr_pers(nr_pers),pret(pret){}
    void afisare(){
        std::cout<<this->nr_cam<<" "<<this->tip_cam<<" "
        <<this->nr_pers<<" "<<this->pret<<std::endl;
    }
    int conversie(){
        if(this->tip_cam=="single")
        return 1;
        else if(this->tip_cam=="double" || this->tip_cam=="twin")
        return 2;
        else if(this->tip_cam=="triple")
        return 3;
        return 0;
    }
    int get_nr_cam(){
        return this->nr_cam;
    }
    int get_nr_pers(){
        return this->nr_pers;
    }
    std::string get_tip(){
        return this->tip_cam;
    }
    float get_pret(){
        return this->pret;
    }
};

bool cresc(Camera *s, Camera *d){
    if(s->conversie()==d->conversie() && s->get_pret()<d->get_pret())
    return true;
    else if(s->conversie()<d->conversie())
    return true;
    return false;
}


class Hotel{
    private:
    int n;
    std::vector<Camera*> C;
    public:
    Hotel(int n):n(n){}
    void afisare(int cnt){
        for(auto &c : C){
            c->afisare();
        }
    }
    void sortare(){
        std::sort(C.begin(),C.end(),cresc);
         for(auto &c : C){
            c->afisare();
        }
    }
    void grad_ocupare(){
        float nr_cam_o=0;
        float nr_cam_t=0;
        for(std::vector<Camera*>::iterator i=
        C.begin();i!=C.end();i++){
            if((*i)->get_nr_pers()!=0)
            nr_cam_o++;
            nr_cam_t++;
        }
        std::cout<<std::fixed<<std::setprecision(2)<<
        ((nr_cam_o/nr_cam_t)*100.00)<<std::endl;
    }
    void cap_ram(){
        int nr_ram=0;
        for(std::vector<Camera*>::iterator i=
        C.begin();i!=C.end();i++){
            if((*i)->get_nr_pers()==0 && (*i)->get_tip()=="single")
            nr_ram=nr_ram+1;
            else if((*i)->get_nr_pers()==0 && ((*i)->get_tip()=="double" || 
            (*i)->get_tip()=="twin"))
            nr_ram=nr_ram+2;
            else if((*i)->get_nr_pers()==0 && (*i)->get_tip()=="triple")
            nr_ram=nr_ram+3;
        }
        std::cout<<nr_ram<<std::endl;
    }
    void citire(){
        int nr_cam,nr_pers;
        std::string tip_cam;
        float pret;
        std::cin>>nr_cam>>tip_cam>>nr_pers>>pret;
        C.push_back(new Camera(nr_cam,tip_cam,nr_pers,pret));
    }
};

int main(){
Hotel H(30);
int comanda;
int cnt=0;
 do {
     std::cin >> comanda;
     ++cnt;
     switch (comanda) {
         case 1: {
             H.citire();
             break;
         }
         case 2: {
             H.afisare(cnt);
             break;
         }
         case 3: {
             H.grad_ocupare();
         break;
         }
         case 4:
            H.cap_ram();
         break;
         case 5:
            H.sortare();
         break;
     }
     }while(comanda!=-1);
}
