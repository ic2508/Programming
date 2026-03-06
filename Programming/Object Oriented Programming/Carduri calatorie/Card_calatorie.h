#ifndef CARD_CALATORIE_H
#define CARD_CALATORIE_H

class Card_calatorie{
private:
    int id;
    char tip;
public:
    Card_calatorie(){}
    Card_calatorie(int id,char tip):id(id),tip(tip){}
    virtual void validare_calatorie(int, int)=0;
    virtual void incarcare(int)=0;
    virtual void afisare()=0;
    virtual int transfer1(int, int)=0;
    virtual void transfer2(int)=0;
    int get_id(){
        return id;
    }
    char get_tip(){
        return tip;
    }
    virtual ~Card_calatorie(){}
};

#endif