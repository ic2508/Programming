#ifndef ANGAJAT_H
#define ANGAJAT_H

class Angajat{
private:
    std::string nume;
    std::string departament;
    std::string tip;
public:
    Angajat(std::string nume, std::string departament,std::string tip):nume(nume),departament(departament),tip(tip){}
    virtual void afisare() = 0;
    virtual float rentabilitate_angajat() = 0;
    virtual float salariu_brut() = 0;
    std::string get_tip(){
        return this->tip;
    }
    virtual std::string get_tip1(){
        return this->tip;
    }
    std::string get_nume(){
        return this->nume;
    }
    virtual std::string get_nume1(){
        return this->nume;
    }
    std::string get_departament(){
        return this->departament;
    }
   virtual std::string get_departament1(){
        return this->departament;
    }
};

#endif