#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
class Ipoteza{
    friend class Referinta;
    private:
    int x1e,y1e,x2e,y2e;
    std::string eticheta1;
    float prag1;
    public:
    Ipoteza(){}
    Ipoteza(int x1e, int y1e, int x2e, int y2e, std::string eticheta1,float prag1){
    this->x1e=x1e;
    this->y1e=y1e;
    this->x2e=x2e;
    this->y2e=y2e;
    this->eticheta1=eticheta1;
    this->prag1=prag1;
    }
    int get_x1(){
        return this->x1e;
    }
    int get_x2(){
        return this->x2e;
    }
    int get_y1(){
        return this->y1e;
    }
    int get_y2(){
        return this->y2e;
    }
    std::string get_eticheta(){
        return this->eticheta1;
    }
};

class Referinta{
    private:
    int x1,y1,x2,y2;
    std::string eticheta;
    public:
    Referinta(){}
    Referinta(int x1, int y1, int x2, int y2, std::string eticheta){
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->eticheta=eticheta;
    }
    void afis1(int i,int n){
        std::cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<std::endl;
    }
    void afis2(int i,int n){
        if(i!=(n-1))
        std::cout<<eticheta<<std::endl;
        else if(i==(n-1)){
        std::cout<<eticheta<<std::endl;
        return;
        }
    }
   int maxCx1(int nx1){
    return this->x1 > nx1 ? this->x1 : nx1;
}

int maxCy1(int ny1){
    return this->y1 > ny1 ? this->y1 : ny1;
}

int minCx2(int nx2){
    return this->x2 < nx2 ? this->x2 : nx2;
}

int minCy2(int ny2){
    return this->y2 < ny2 ? this->y2 : ny2;
}
        
    float calculIoU(int nx1,int ny1,int nx2, int ny2, std::string n_eticheta){
        float sup_n,sup;
        if(n_eticheta==this->eticheta){
        if(nx2>nx1 && ny2>ny1 && this->x2>this->x1 && this->x2>this->x1){
        sup_n = ((nx2-nx1+1)*(ny2-ny1+1));
        sup = ((this->x2-this->x1+1)*(this->y2-this->y1+1));
        }
        else{
        sup_n = ((nx1-nx2+1)*(ny1-ny2+1));
        sup = ((this->x1-this->x2+1)*(this->y1-this->y2+1));
        }
        if(sup_n<0)
        sup_n = fabs(sup_n);
        if(sup<0)
        sup = fabs(sup);
        //std::cout<<sup_n<<" "<<sup<<std::endl;
        float sup_int;
        //if(this->x1>nx1 && this->y1>ny1 && this->x2<nx2 && this->y2<ny2){
            float l_int = ((minCx2(nx2) - maxCx1(nx1))+1);
            float L_int = ((minCy2(ny2) - maxCy1(ny1))+1);
            if(l_int<0)
            l_int = fabs(l_int);
            if(L_int<0)
            L_int = fabs(L_int);
            sup_int=(L_int * l_int);
        //}
        //std::cout<<L_int<<" "<<l_int<<std::endl;
        float IoU = (sup_int/((sup_n+sup)-sup_int));
        return IoU;
        }
        return 0;
    }
    std::string get_eticheta(){
        return this->eticheta;
    }
};

int main(){
    int n,test;
    std::cin>>n;
    std::cin.ignore();
    Referinta R[10];
    Ipoteza I[10];
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;
        std::string eticheta;
        //std::cin>>x1>>y1>>x2>>y2;
        std::cin>>x1>>x2>>y1>>y2;
        std::cin.ignore();
        std::getline(std::cin,eticheta);
        //std::cin.ignore();
        R[i] = Referinta(x1,y1,x2,y2,eticheta);
    }
    std::cin>>test;
    std::cin.ignore();
    int nx1,ny1,nx2,ny2,m;
    //int n_x1,n_y1,n_x2,n_y2;
    std::string n_eticheta;
    float val, prag;
    float TP=0,FP=0;
    switch(test){
        case 1:
        for(int i=0;i<n;i++){
            R[i].afis1(i,n);
            R[i].afis2(i,n);
            //std::cin.ignore();
        }
        //std::cin.ignore();
        break;
        case 2:
        //std::cin>>nx1>>ny1>>nx2>>ny2;
        std::cin>>nx1>>nx2>>ny1>>ny2;
        std::cin.ignore();
        std::getline(std::cin,n_eticheta);
        val = R[0].calculIoU(nx1,ny1,nx2,ny2,n_eticheta);
        std::cout<<std::fixed<<std::setprecision(4)<<val<<std::endl;
        break;
        case 3:
        //std::cin>>n_x1>>n_x2>>n_y1>>n_y2;
        std::cin>>nx1>>nx2>>ny1>>ny2;
        std::cin.ignore();
        std::getline(std::cin,n_eticheta);
        std::cin>>prag;
        val = R[0].calculIoU(nx1,ny1,nx2,ny2,n_eticheta);
        if(val>prag && n_eticheta==R[0].get_eticheta())
        std::cout<<"1";
        else if(val>prag && n_eticheta!=R[0].get_eticheta())
        std::cout<<"0";
        else if(val<prag)
        std::cout<<"0";
        break;
        case 4:
        std::cin>>m;
        float prag1;
        int x1e,y1e,x2e,y2e;
        std::string eticheta1;
        for(int i=0;i<n;i++){
        std::cin>>x1e>>x2e>>y1e>>y2e;
        std::cin.ignore();
        std::getline(std::cin,eticheta1);
        I[i] = Ipoteza(x1e,y1e,x2e,y2e,eticheta1,prag1);
    }
    std::cin>>prag1;
        for(int i=0;i<n;i++){
            val = R[i].calculIoU(I[i].get_x1(),I[i].get_y1(),I[i].get_x2(),I[i].get_y2(),I[i].get_eticheta());
            if(val>prag1 && I[i].get_eticheta()==R[i].get_eticheta())
            TP++;
            else if(val>prag1 && I[i].get_eticheta()!=R[i].get_eticheta())
            FP++;
            else if(val<prag1)
            FP++;
            }
    std::cout<<(TP/(TP+FP))<<std::endl;
        break;
    }
}