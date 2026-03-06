#include <iostream>
#include <string>
#include <iomanip>

class Copac{
  friend class Livada;
  private:
  std::string num_soi,tip_soi;
  float sup_necesar;
  int nr_cop;
  public:
  Copac(){}
  Copac(std::string num_soi,std::string tip_soi, float sup_necesar, int nr_cop){
      this->num_soi=num_soi;
      this->tip_soi=tip_soi;
      this->sup_necesar=sup_necesar;
      this->nr_cop=nr_cop;
  }
  void afis(){
      std::cout<<this->num_soi<<" "<<this->sup_necesar<<" "<<this->nr_cop<<" "<<this->tip_soi<<std::endl;
  }
  std::string get_tip_soi(){
      return this->tip_soi;
  }
  float sup_lib(float sup){
       float sup_ram=(sup-(this->nr_cop*this->sup_necesar));
       return sup_ram;
  }
  float get_sup_necesar(){
      return this->sup_necesar;
  }
  int get_nr_cop(){
      return this->nr_cop;
  }
  void nr_ram(float sup){
      int nr_ram1 = ((sup/this->sup_necesar)-this->nr_cop);
      std::cout<<nr_ram1<<std::endl;
  }
};

class Livada{
    private:
    int n;
    float sup;
    Copac *c[10];
    public:
    //Copac** get_copac(int i){
    //    return c;
    //}
    Livada(){}
    Livada(int n,float sup,Copac *c[]){
        this->n=n;
        this->sup=sup;
        for(int i=0;i<n;i++){
           this->c[i]=new Copac(*c[i]);
    }
    }
    ~Livada() {
        for(int i = 0; i < n; i++) {
            delete c[i];
        }
    }
    void apend(std::string num_soi,std::string tip_soi, float sup_necesar, int nr_cop){
        for(int i=0;i<n;i++){
        c[i] = new Copac(num_soi,tip_soi,sup_necesar,nr_cop);
        }
    }
    void afis1(int i){
        c[i]->afis();
    }
    std::string get_tip_soi1(int i){
      return c[i]->get_tip_soi();
  }
  float sup_lib1(int i, float sup){
       return c[i]->sup_lib(sup);
  }
  float get_sup_necesar1(int i){
      return c[i]->get_sup_necesar();
  }
  int get_nr_cop1(int i){
      return c[i]->get_nr_cop();
  }
  void nr_ram1(int i, float sup){
      c[i]->nr_ram(sup);
  }
};
int main(){
 float sup;
 int n,test;
 std::cin>>sup>>n;
 std::cin.ignore();
 Livada L;
 Copac *c[10];
 for(int i=0;i<n;i++){
     std::string num_soi,tip_soi;
     float sup_necesar;
     int nr_cop;
     std::getline(std::cin,num_soi);
     std::cin>>sup_necesar>>nr_cop;
     std::cin.ignore();
     std::getline(std::cin,tip_soi);
     c[i] = new Copac(num_soi,tip_soi,sup_necesar,nr_cop);
     L.apend(num_soi,tip_soi,sup_necesar,nr_cop);

 }
 Livada L1(n,sup,c);
 std::cin>>test;
 std::cin.ignore();
 std::string crit_soi;
 float sup_r=0;
 switch(test){
     case 1:
     std::cout<<sup<<std::endl;
     for(int i=0;i<n;i++)
     L1.afis1(i);
     break;
     case 2:
     std::getline(std::cin,crit_soi);
     std::cin.ignore();
     for(int i=0;i<n;i++){
     if(L1.get_tip_soi1(i) == crit_soi){
         L1.afis1(i);
     }
     }
     break;
     case 3:
     for(int i=0;i<n;i++){
         sup_r=L1.sup_lib1(i,sup);
         sup=(sup-(L1.get_sup_necesar1(i) * L1.get_nr_cop1(i)));
     }
     std::cout<<std::fixed<<std::setprecision(2)<<sup_r<<std::endl;
     break;
     case 4:
     for(int i=0;i<n;i++){
         L1.nr_ram1(i,sup);
     }
     break;
 }
}