#include "MapObjects.hpp"
#include <iostream>

class Knight : public Unit{
    public:
        Knight();
        Knight(const Coordinates& cord, const unsigned short endurance);
   
    private:
};

class Swordsman : public Unit{
    public:
        Swordsman();
        Swordsman(const Coordinates& cord, const unsigned short endurance);

    private:
};

class Base : public Unit{
    public:
        Base();
        Base(const Coordinates& cord, const unsigned short endurance);

    inline bool Move([[maybe_unused]] const Coordinates& moveTo) override { std::cout<<"Base Cannot move!\n"; return false;}
    inline bool Attack([[maybe_unused]] std::shared_ptr<Unit> Solider) override { std::cout<<"Base Cannot attack!\n"; return false;}
    int getId() const override {return -1;};
    // Ma mieć produce 
    //Player ma do siebie przypisana baze ta baza ma produkowac jednostki. Czyli jezeli w bazie aktualnie nic sie nie produkuje to zaczyna produkcje.
    //W klasie player bedzie podawanie jednostki ktora ma sie produkowac tam odejmujemy pieniadze rowniez tam jest tez licznik jednostek 
    bool produce(UnitTYPE unitType);
    
    private:
        unsigned short timeToProduce;

};