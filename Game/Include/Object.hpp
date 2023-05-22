#include "MapObjects.hpp"

class Road : public Object{
    Road(){ObjectType_ = ObjectTYPE::Road;};
    Road(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};
};

class Mine : public Object{
    Mine(){ObjectType_ = ObjectTYPE::Mine;};
    Mine(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};

};

class Obstacle : public Object{
    Obstacle(){ObjectType_ = ObjectTYPE::Obstacle;};
    Obstacle(const Coordinates& coordinates, const ObjectTYPE& ObjectType): Object(coordinates,ObjectType){};

};