#pragma once
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

class Archer : public Unit{
    public:
        Archer();
        Archer(const Coordinates& cord, const unsigned short endurance);
   
    private:
};

class Pikeman : public Unit{
    public:
        Pikeman();
        Pikeman(const Coordinates& cord, const unsigned short endurance);

    private:
};

class Catapult : public Unit{
    public:
        Catapult();
        Catapult(const Coordinates& cord, const unsigned short endurance);
   
    private:
};

class Ram : public Unit{
    public:
        Ram();
        Ram(const Coordinates& cord, const unsigned short endurance);

    private:
};

class Worker : public Unit{
    public:
        Worker();
        Worker(const Coordinates& cord, const unsigned short endurance);

    private:
};

class Base : public Unit{
    public:
        Base(const Coordinates& cord);
        Base(const Coordinates& cord, const unsigned short endurance);

    inline bool Move([[maybe_unused]] const Coordinates& moveTo) override { std::cout<<"Base Cannot move!\n"; return false;}
    inline bool Attack([[maybe_unused]] std::shared_ptr<Unit> Solider) override { std::cout<<"Base Cannot attack!\n"; return false;}
    // Ma mieć produce 
    //Player ma do siebie przypisana baze ta baza ma produkowac jednostki. Czyli jezeli w bazie aktualnie nic sie nie produkuje to zaczyna produkcje.
    //W klasie player bedzie podawanie jednostki ktora ma sie produkowac tam odejmujemy pieniadze rowniez tam jest tez licznik jednostek 
    bool produce(UnitTYPE unitType);
    
    private:
        unsigned short timeToProduce;

};