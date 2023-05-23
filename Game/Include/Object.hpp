#pragma once
#include "MapObjects.hpp"

class Road : public Object{
    public:
    Road(){ObjectType_ = ObjectTYPE::Road;};
    Road(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};
};

class Mine : public Object{
    public:
    Mine(){ObjectType_ = ObjectTYPE::Mine;};
    Mine(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};

};

class Obstacle : public Object{
    public:
    Obstacle(){ObjectType_ = ObjectTYPE::Obstacle;};
    Obstacle(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};

};