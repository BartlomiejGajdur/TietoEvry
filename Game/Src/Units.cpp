#include "../Include/Units.hpp"

Knight::Knight(const Coordinates& coord){
              unitType_ = UnitTYPE::Knight; 
              endurance_ = 70;
              speed_ = 5;
              purchaseCost_ = 400;
              attackRange_ = 1;
              BuildTime_ = 5;
              ObjectCoordinates_ = coord;
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

  Swordsman::Swordsman(const Coordinates& coord){
              unitType_ = UnitTYPE::Swordsman; 
              endurance_ = 60;
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 1;
              BuildTime_ = 3;
              ObjectCoordinates_ = coord;
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
Archer::Archer(const Coordinates& coord){
              unitType_ = UnitTYPE::Archer; 
              endurance_ = 40;
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 5;
              BuildTime_ = 3;
              ObjectCoordinates_ = coord;
              counter++;
        };

 Archer::Archer(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Archer; 
              speed_ = 2;
              purchaseCost_ = 250;
              attackRange_ = 5;
              BuildTime_ = 3;
              counter++;
        }

  Pikeman::Pikeman(const Coordinates& coord){
              unitType_ = UnitTYPE::Pikeman; 
              endurance_ = 50;
              speed_ = 2;
              purchaseCost_ = 200;
              attackRange_ = 2;
              BuildTime_ = 3;
              ObjectCoordinates_ = coord;
              counter++;
        };

Pikeman::Pikeman(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Pikeman; 
              speed_ = 2;
              purchaseCost_ = 200;
              attackRange_ = 2;
              BuildTime_ = 3;
              counter++;
        }

Ram::Ram(const Coordinates& coord){
              unitType_ = UnitTYPE::Ram; 
              endurance_ = 90;
              speed_ = 2;
              purchaseCost_ = 500;
              attackRange_ = 1;
              BuildTime_ = 4;
              ObjectCoordinates_ = coord;
              counter++;
        };

 Ram::Ram(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Ram; 
              speed_ = 2;
              purchaseCost_ = 500;
              attackRange_ = 1;
              BuildTime_ = 4;
              counter++;
        }

Catapult::Catapult(const Coordinates& coord){
              unitType_ = UnitTYPE::Catapult; 
              endurance_ = 50;
              speed_ = 2;
              purchaseCost_ = 800;
              attackRange_ = 7;
              BuildTime_ = 6;
              ObjectCoordinates_ = coord;
              counter++;
        };

Catapult::Catapult(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Catapult; 
              speed_ = 2;
              purchaseCost_ = 800;
              attackRange_ = 7;
              BuildTime_ = 6;
              counter++;
        }
Worker::Worker(const Coordinates& coord){
              unitType_ = UnitTYPE::Worker; 
              endurance_ = 20;
              speed_ = 2;
              purchaseCost_ = 100;
              attackRange_ = 1;
              BuildTime_ = 2;
              ObjectCoordinates_ = coord;
              counter++;
        };

Worker::Worker(const Coordinates& cord, const unsigned short endurance): Unit(cord,endurance){
              unitType_ = UnitTYPE::Worker; 
              speed_ = 2;
              purchaseCost_ = 100;
              attackRange_ = 1;
              BuildTime_ = 2;
              counter++;
        }

Base::Base(const Coordinates& cord){
              unitType_ = UnitTYPE::Base; 
              endurance_ = 200;
              speed_ = 0;
              purchaseCost_ = 0;
              attackRange_ = 0;
              BuildTime_ = 0;
              ObjectCoordinates_ = cord;
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

bool Base::Produce(const UnitTYPE& unitType){
      if(production.first != UnitTYPE::Base)
      {
            std::cout<<"Base during production! \n";
            return false;
      }
            std::cout<<"Production started! \n";
            production.first = unitType;
            production.second = Unit::getBuildTime(unitType);
      return true;

}
