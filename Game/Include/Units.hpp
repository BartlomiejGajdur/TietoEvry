#include "Object.hpp"
#include <iostream>

class Knight : public Unit{
    public:
        Knight(){
              unitType_ = UnitTYPE::Knight; 
              endurance_ = 70;
              speed_ = 5;
              purchaseCost_ = 400;
              attackRange_ = 1;
              BuildTime_ = 5;
              ObjectCoordinates_ = Coordinates{0,0};
              speedLeft_ = speed_;
              id_++;
        };

        Knight(const Coordinates& cord, const unsigned short endurance){
              unitType_ = UnitTYPE::Knight; 
              endurance_ = endurance;
              speed_ = 5;
              purchaseCost_ = 400;
              attackRange_ = 1;
              BuildTime_ = 5;
              ObjectCoordinates_ = cord;
              speedLeft_ = speed_;
              id_++;
        }

    
    private:
};

class Swordsman : public Unit{
    public:
        Swordsman(){
              unitType_ = UnitTYPE::Swordsman; 
              endurance_ = 60;
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 1;
              BuildTime_ = 3;
              ObjectCoordinates_ = Coordinates{0,0};
              speedLeft_ = speed_;
              id_++;
        };

        Swordsman(const Coordinates& cord, const unsigned short endurance){
              unitType_ = UnitTYPE::Swordsman; 
              endurance_ = endurance;
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 1;
              BuildTime_ = 3;
              ObjectCoordinates_ = cord;
              speedLeft_ = speed_;
              id_++;
        }

    
    private:
};

class Base : public Unit{
    public:
        Base(){
              unitType_ = UnitTYPE::Base; 
              endurance_ = 200;
              speed_ = 0;
              purchaseCost_ = 0;
              attackRange_ = 0;
              BuildTime_ = 0;
              ObjectCoordinates_ = Coordinates{0,0};
              speedLeft_ = speed_;
              id_++;
        };

        Base(const Coordinates& cord, const unsigned short endurance){
              unitType_ = UnitTYPE::Base; 
              endurance_ = endurance;
              speed_ = 0;
              purchaseCost_ = 0;
              attackRange_ = 0;
              BuildTime_ = 0;
              ObjectCoordinates_ = cord;
              speedLeft_ = speed_;
              id_++;
        }

    bool Move(const Coordinates& moveTo) override { std::cout<<"Base Cannot move!\n"; return false;}
    bool Attack(std::shared_ptr<Unit> Solider) override { std::cout<<"Base Cannot attack!\n"; return false;}

    // Ma mieć produce 
    //Player ma do siebie przypisana baze ta baza ma produkowac jednostki. Czyli jezeli w bazie aktualnie nic sie nie produkuje to zaczyna produkcje.
    //W klasie player bedzie podawanie jednostki ktora ma sie produkowac tam odejmujemy pieniadze rowniez tam jest tez licznik jednostek 
    bool produce(UnitTYPE unitType);
    
    private:
        unsigned short timeToProduce;

};