#include "Object.hpp"

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