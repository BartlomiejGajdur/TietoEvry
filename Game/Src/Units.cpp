#include "../Include/Units.hpp"

Knight::Knight(){
              unitType_ = UnitTYPE::Knight; 
              endurance_ = 70;
              speed_ = 5;
              purchaseCost_ = 400;
              attackRange_ = 1;
              BuildTime_ = 5;
              ObjectCoordinates_ = Coordinates{0,0};
              counter++;
        };

 Knight::Knight(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Knight; 
              speed_ = 5;
              purchaseCost_ = 400;
              attackRange_ = 1;
              BuildTime_ = 5;
              counter++;
        }

  Swordsman::Swordsman(){
              unitType_ = UnitTYPE::Swordsman; 
              endurance_ = 60;
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 1;
              BuildTime_ = 3;
              ObjectCoordinates_ = Coordinates{0,0};
              counter++;
        };

Swordsman::Swordsman(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Swordsman; 
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 1;
              BuildTime_ = 3;
              counter++;
        }

Base::Base(){
              unitType_ = UnitTYPE::Base; 
              endurance_ = 200;
              speed_ = 0;
              purchaseCost_ = 0;
              attackRange_ = 0;
              BuildTime_ = 0;
              ObjectCoordinates_ = Coordinates{0,0};
              counter++;
        };

Base::Base(const Coordinates& cord, const unsigned short endurance):Unit(cord,endurance){
              unitType_ = UnitTYPE::Base; 
              speed_ = 0;
              purchaseCost_ = 0;
              attackRange_ = 0;
              BuildTime_ = 0;
              counter++;
        }