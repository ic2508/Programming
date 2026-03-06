#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

class Server{
    private:
    int n,IP;
    public:
    Server(int n, int IP):n(n),IP(IP){}
    void afisare(){
        std::cout<<this->n<<" "<<this->IP<<std::endl;
    }
    void adaugare(int cnt){
        this->IP=cnt;
    }
    void deconectare(){
        this->IP=0;
    }
    int get_n(){
        return this->n;
    }
    int get_IP(){
        return this->IP;
    }
};

class Manager{
    private:
    std::vector<Server*> S;
    std::vector<int> ip;
    
    public:
    Manager(){}
    void afisare(){
        for(int i=0;i<S.size();i++){
            S[i]->afisare();
        }
    }
    void vector(int nr){
        int x;
        for(int i=0;i<nr;i++){
            std::cin>>x;
            ip.push_back(x);
        }
        int cnt=1;
        for(int i=0;i<nr;i++){
            if(cnt!=ip[i]){
            ip.insert(ip.begin()+i,cnt);
            break;
            }
            else if(cnt==ip[i] && cnt==nr)
            ip.push_back(++cnt);
            else if(cnt==ip[i])
            ++cnt;
            
        }
        for(int i=0;i<=nr;i++){
            std::cout<<ip[i]<<" ";
        }
    }
    void conectare(int id,int cnt){
        for(int i=0;i<S.size();i++){
        if(id==S[i]->get_n()){
            S[i]->adaugare(cnt);
        }
        }
    }
    void pool(int dim){
        int x,val;
        for(int i=0;i<dim;i++){
            std::cin>>x;
            ip.push_back(x);
        }
        std::cin>>val;
        for(int i=0;i<dim;i++){
            if(val==ip[i]){
            ip.erase(ip.begin()+i);
            break;
            }
        }
        for(int i=0;i<dim-1;i++){
            std::cout<<ip[i]<<" ";
        }
    }
    void deconectare(int id){
        for(int i=0;i<S.size();i++){
        if(id==S[i]->get_n()){
            S[i]->deconectare();
        }
    }
    }
    int val_deconectare(int id){
        for(int i=0;i<S.size();i++){
        if(id==S[i]->get_n()){
            return S[i]->get_IP();
        }
    }
    return 0;
    }
    void citire(){
        int n;
        int IP=0;
        std::cin>>n;
        S.push_back(new Server(n,IP));
    }
};



int main(){
Manager M;
int comanda,nr,id,cnt=1,cnt1=0,dim;
int val1=0, val2=0;
do {
    std::cin >> comanda;
    switch (comanda) {
        case 1: 
        M.citire();
        break;
        case 2:
        M.afisare();
        break;
        case 3: 
        std::cin>>nr;
        M.vector(nr);
        break;
        case 4:
        std::cin>>id;
        if(cnt1==1){
        M.conectare(id,cnt);
        cnt1=0;
        ++cnt;
        cnt=val2;
        }
        else if(cnt1==0){
        M.conectare(id,cnt);
        ++cnt;
        val2=cnt;
        }
        break;
        case 5:
        std::cin>>dim;
        M.pool(dim);
        break;
        case 6:
        std::cin>>id;
        val1 = M.val_deconectare(id);
        M.deconectare(id);
        cnt=val1;
        ++cnt1;
        break;
    }
} while(comanda!=-1);
}