#include "../Include/Coordinates.hpp"

bool Coordinates::operator==(const Coordinates &other)
    {
        return this->positionX_ == other.positionX_ &&
                this->positionY_ == other.positionY_;
    }

std::ostream& operator<<(std::ostream &os, const Coordinates& position)
    {   
        os<<"X["<<position.getPositionX()<<"] Y["<<position.getPositionY()<<"]";
        return os;
    }

size_t Coordinates::distance(const Coordinates& lhs, const Coordinates& rhs){
    return abs(lhs.getPositionX()-rhs.getPositionX()) + abs(lhs.getPositionY()-rhs.getPositionY());
}

size_t Coordinates::distance(const Coordinates& other){
    return abs(this->getPositionX()-other.getPositionX()) + abs(this->getPositionY()-other.getPositionY());
}