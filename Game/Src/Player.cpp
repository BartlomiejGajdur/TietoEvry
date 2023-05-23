#include "../Include/Player.hpp"
#include <iostream>

void Player::printObjectsOwn() const{
    for(const auto& v: objectsOwn_)
    {
        std::cout<<v<<"\n";
    }
}