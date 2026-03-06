#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

class MathFunction{
  protected:
  std::string function_name;
  public:
  MathFunction(std::string function_name):function_name(function_name){}
  virtual float get_value(int)=0;
  virtual float get_max_value(int,int)=0;
  virtual void afisare()=0;
  virtual void radacina()=0;
};

class Polynomial: public MathFunction{
    protected:
    std::vector<float> coefficients;
    public:
    Polynomial(std::string function_name, std::vector<float> coefficients):
    MathFunction(function_name),coefficients(coefficients){}
    float get_value(int val) override{
        float value=0;
        int nr=0;
        float num=1;
            for(int k=0;k<coefficients.size();k++){
            if(coefficients[nr]!=0 && nr==0)
            value=value+coefficients[nr];
            if(coefficients[nr]>=0 && nr==1)
                value=(value+(coefficients[nr]*val));
            else if(coefficients[nr]>=0 && nr>1){
                for(int j=0;j<nr;j++){
                        num=num*val;
                }
                value=(value+(coefficients[nr]*num));
                num=1;
            }
            else if(coefficients[nr]<0 && nr==1)
                value=(value-(fabs(coefficients[nr])*val));
            else if(coefficients[nr]<0 && nr>1){
                for(int j=0;j<nr;j++){
                num=num*val;
                }
                value=(value-(fabs(coefficients[nr])*num));
                num=1;
        }
        ++nr;
        }
        nr=0;
        return value;
    }
    float get_max_value(int nr1,int nr2) override{
        float value=0;
        int nr=0;
        float num=1;
        int max1=-32000;
        for(int i=nr1;i<=nr2;i++){
            for(int k=0;k<coefficients.size();k++){
            if(coefficients[nr]!=0 && nr==0)
            value=value+coefficients[nr];
            if(coefficients[nr]>=0 && nr==1)
                value=(value+(coefficients[nr]*i));
            else if(coefficients[nr]>=0 && nr>1){
                for(int j=0;j<nr;j++){
                        num=num*i;
                }
                value=(value+(coefficients[nr]*num));
                num=1;
            }
            else if(coefficients[nr]<0 && nr==1)
                value=(value-(fabs(coefficients[nr])*i));
            else if(coefficients[nr]<0 && nr>1){
                for(int j=0;j<nr;j++){
                num=num*i;
                }
                value=(value-(fabs(coefficients[nr])*num));
                num=1;
        }
        ++nr;
        }
        if(value>max1){
        max1=value;
        }
        nr=0;
        value=0;
        }
        return max1;
    }
    void afisare() override{
       int n_x=0;
       std::cout<<function_name<<std::endl;
       std::cout<<"f(x) = "<<coefficients[n_x];
       for(int i=0;i<coefficients.size();i++){
       ++n_x;
       if(n_x==coefficients.size()){
           std::cout<<std::endl;
           n_x=0;
           break;
       }
       if(coefficients[n_x]==0){
       continue;
       }
       if(coefficients[n_x]>=0 && n_x==1)
       std::cout<<" + "<<coefficients[n_x]<<"x";
       else if(coefficients[n_x]>=0 && n_x>1)
       std::cout<<" + "<<coefficients[n_x]<<"x^"<<n_x;
       else if(coefficients[n_x]<0 && n_x==1){
           if(fabs(coefficients[n_x])==1)
       std::cout<<" - x";
       else
       std::cout<<" - "<<fabs(coefficients[n_x])<<"x";
       }
       else if(coefficients[n_x]<0 && n_x>1)
         if(fabs(coefficients[n_x])==1)
       std::cout<<" - x^"<<n_x;
       else
       std::cout<<" - "<<fabs(coefficients[n_x])<<"x^"<<n_x;
       }
    }
    void radacina() override{}
};
class Quadratic: public Polynomial{
    private:
    public:
    Quadratic(std::string function_name, std::vector<float> coefficients):
    Polynomial(function_name, coefficients){}
    void print_roots(){
        
    }
    float get_value(int val) override{
        float value=0;
        int nr=0;
        float num=1;
            for(int k=0;k<coefficients.size();k++){
            if(coefficients[nr]!=0 && nr==0)
            value=value+coefficients[nr];
            if(coefficients[nr]>=0 && nr==1)
                value=(value+(coefficients[nr]*val));
            else if(coefficients[nr]>=0 && nr>1){
                for(int j=0;j<nr;j++){
                        num=num*val;
                }
                value=(value+(coefficients[nr]*num));
                num=1;
            }
            else if(coefficients[nr]<0 && nr==1)
                value=(value-(fabs(coefficients[nr])*val));
            else if(coefficients[nr]<0 && nr>1){
                for(int j=0;j<nr;j++){
                num=num*val;
                }
                value=(value-(fabs(coefficients[nr])*num));
                num=1;
        }
        ++nr;
        }
        nr=0;
        return value;
    }
    float get_max_value(int nr1,int nr2) override{
        float value=0;
        int nr=0;
        float num=1;
        int max1=-32000;
         for(int i=nr1;i<=nr2;i++){
            for(int k=0;k<coefficients.size();k++){
                if(coefficients[nr]!=0 && nr==0)
            value=value+coefficients[nr];
            if(coefficients[nr]>=0 && nr==1)
                value=(value+(coefficients[nr]*i));
                else if(coefficients[nr]>=0 && nr>1){
                for(int j=0;j<nr;j++){
                              num=num*i;
                }
                value=(value+(coefficients[nr]*num));
                num=1;
                }
            else if(coefficients[nr]<0 && nr==1)
                value=(value-(fabs(coefficients[nr])*i));
            else if(coefficients[nr]<0 && nr>1){
                for(int j=0;j<nr;j++){
                num=num*i;
                }
                value=(value-(fabs(coefficients[nr])*num));
                 num=1;
            }
                 ++nr;
        }
        if(value>max1){
        max1=value;
        }
        nr=0;
        value=0;
        }
        return max1;
    }
    void afisare() override{
       int n_x=0;
       std::cout<<function_name<<std::endl;
       std::cout<<"f(x) = "<<coefficients[n_x];
       for(int i=0;i<coefficients.size();i++){
       ++n_x;
       if(n_x==coefficients.size()){
           std::cout<<std::endl;
           n_x=0;
           break;
       }
       if(coefficients[n_x]==0){
       continue;
       }
       if(coefficients[n_x]>=0 && n_x==1)
       std::cout<<" + "<<coefficients[n_x]<<"x";
       else if(coefficients[n_x]>=0 && n_x>1)
       std::cout<<" + "<<coefficients[n_x]<<"x^"<<n_x;
       else if(coefficients[n_x]<0 && n_x==1){
       std::cout<<" - "<<fabs(coefficients[n_x])<<"x";
       }
       else if(coefficients[n_x]<0 && n_x>1)
       std::cout<<" - "<<fabs(coefficients[n_x])<<"x^"<<n_x;
       }
    }
       void radacina(){
           float X1,X2;
           X1=(-coefficients[1]+sqrt(pow(coefficients[1],2)-4*coefficients[2]*coefficients[0]));
           X1=X1/(2*coefficients[2]);
           X2=((-coefficients[1]-sqrt(pow(coefficients[1],2)-4*coefficients[2]*coefficients[0]))/(2*coefficients[2]));
           if(X1!=X2){
               std::cout<<"X1 = "<<std::fixed<<std::setprecision(2)<<X1<<std::endl;
               std::cout<<"X2 = "<<std::fixed<<std::setprecision(2)<<X2<<std::endl;
           }
           else if(X1==X2){
               std::cout<<"X1 = X2 = "<<std::fixed<<std::setprecision(2)<<X1<<std::endl;
    }
       }
};
class Exponential: public MathFunction{
    private:
    const float e;
    float constant;
    float exp_coeff;
    public:
    Exponential(std::string function_name, float e, float constant, float exp_coeff):
    MathFunction(function_name),e(e),constant(constant),exp_coeff(exp_coeff){}
    float get_value(int val) override{
        float value=0;
        int nr=0;
        float num=1;
            value=value+constant;
            for(int j=0;j<fabs(val);j++){
                num=num*(float)val;
            }
            value=value+exp_coeff*e*num;
            num=1;
    return value;
    }
    float get_max_value(int nr1,int nr2) override{
        float value=0;
        int nr=0;
        float num=1;
        float max1=-32000;
        for(int i=nr1;i<=nr2;i++){
            value=value+constant;
            for(int j=0;j<fabs(nr1);j++){
                num=num*(float)i;
            }
            value=value+exp_coeff*e*num;
            num=1;
            if(value>max1)
            max1=value;
            value=0;
    }
    return max1;
    }
    void afisare() override{
        std::cout<<function_name<<std::endl;
        std::cout<<"f(x) = "<<constant<<" + "<<exp_coeff<<"e^x"<<std::endl;
    }
    void radacina() override{}
};
class DiscreteFunction: public MathFunction{
    private:
    std::vector<float>x_values;
    std::vector<float>y_values;
    public:
    DiscreteFunction(std::string function_name, std::vector<float>x_values, std::vector<float>y_values):
    MathFunction(function_name),x_values(x_values),y_values(y_values){}
    float find_best_approximation(std::vector<float> y_values1){
        float val = 0;
        for(int i=0;i<3;i++){
        val=val+fabs(y_values[i]-y_values1[i]);
        }
        return val;
    }
    float get_value(int) override{
        return 0;
    }
    float get_max_value(int,int) override{
        return 0;
    }
    void afisare() override{
        
    }
    void radacina() override{}
};

int main(){
    int nr,test,k2=0;
    std::cin>>nr;
    std::vector<MathFunction*> M;
    for(int i=0;i<nr;i++){
        std::string nume;
        int nr_term;
        float x;
        float constant;
        float exp_coeff;
        std::cin>>nume;
        if(nume=="Polynomial"){
            std::cin>>nr_term;
            std::vector<float> coefficients;
            for(int i=0;i<nr_term;i++){
                std::cin>>x;
                coefficients.push_back(x);
            }
            M.push_back(new Polynomial(nume,coefficients));
        }
        if(nume=="Quadratic"){
            std::vector<float> coefficients;
            for(int i=0;i<3;i++){
                std::cin>>x;
                coefficients.push_back(x);
            }
            M.push_back(new Quadratic(nume,coefficients));
        }
        if(nume=="Exponential"){
            std::cin>>constant;
            std::cin>>exp_coeff;
            M.push_back(new Exponential(nume,2.71,constant,exp_coeff));
        }
        k2++;
    }
    std::cin>>test;
    std::cin.ignore();
    int nr1,nr2;
    switch(test){
        case 1:
        for(std::vector<MathFunction*>::iterator i=M.begin();i!=M.end();i++){
            (*i)->afisare();
        }
        break;
        case 2:
        for(std::vector<MathFunction*>::iterator i=M.begin();i!=M.end();i++){
            (*i)->radacina();
        }
        break;
        case 3:
        std::cin>>nr1>>nr2;
        for(std::vector<MathFunction*>::iterator i=M.begin();i!=M.end();i++){
                    std::cout<<std::fixed<<std::setprecision(2)<<(*i)->get_max_value(nr1,nr2)<<std::endl;
        }
        break;
        case 4:
        std::vector<float>x_values;
        std::vector<float>y_values;
        std::vector<float>y_values1;
        float x,y;
        for(int i=0;i<3;i++){
            std::cin>>x;
            x_values.push_back(x);
        }
        for(int i=0;i<3;i++){
            std::cin>>y;
            y_values.push_back(y);
        }
        float aprox=0,min1=32000;
        int k=0,k1=0;
        M.push_back(new DiscreteFunction("",x_values,y_values));
        for(std::vector<MathFunction*>::iterator i=M.begin();i!=M.end()-1;i++){
            for(int j=0;j<3;j++){
            y_values1[j] = (*i)->get_value(x_values[j]);
            }
            aprox = dynamic_cast<DiscreteFunction*>(M.back())->find_best_approximation(y_values1);
            if(min1>aprox){
                min1=aprox;
                k1=k;
            }
            k++;
            if(k==k2)
            M[k1]->afisare();
            }
            std::cout<<min1<<std::endl;
            
    }
}