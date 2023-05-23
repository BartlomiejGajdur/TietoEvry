#include "MapObjects.hpp"
#include <vector>
#include <memory>

class Player{
    public:
        Player(long money): money_(money){};

        long getMoney() const {return money_;};
        void addMoney(long money) { money_ = money;};
        void addObject(std::shared_ptr<MapObject>& object) { objectsOwn_.push_back(object);};
        void printObjectsOwn()const;

    private:
        long money_;
        std::vector<std::shared_ptr<MapObject>> objectsOwn_;

};