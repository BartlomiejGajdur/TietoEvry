#include <gtest/gtest.h>

#include <iostream>
#include "../Include/FileManager.hpp"
#include <algorithm>
#include "../Include/Coordinates.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"
#include "../Include/Units.hpp"
#include <memory>

struct UnitsUnderTestFixture : public ::testing::Test{

    
    Map mapa{
        "000\n666\n999\n000\n"};
    
    std::shared_ptr<Base> BASE = std::make_shared<Base>(Coordinates{2,2});
    std::shared_ptr<Knight> Knight1 = std::make_shared<Knight>(Coordinates{0,0},70);
    std::shared_ptr<Swordsman> Swordsman1 = std::make_shared<Swordsman>(Coordinates{1,1},60);

    std::shared_ptr<Archer> Archer1 = std::make_shared<Archer>(Coordinates{0,0},40);
    std::shared_ptr<Catapult> Catapult1 = std::make_shared<Catapult>(Coordinates{7,0},50);

    std::shared_ptr<Worker> Worker1 = std::make_shared<Worker>();
};

TEST_F(UnitsUnderTestFixture, CorrectMove)
{
    Coordinates moveTo{3, 2};
    bool result = Knight1->Move(moveTo);

    EXPECT_TRUE(result); 
    EXPECT_EQ(Knight1->getObjectCoordinates(), moveTo); 
}

TEST_F(UnitsUnderTestFixture, DestinationCoordinatesInconsistentWithSpeedPoints)
{

    Coordinates FirstMove{3, 1};
    bool result = Knight1->Move(FirstMove);


    EXPECT_TRUE(result); 
    EXPECT_EQ(Knight1->getObjectCoordinates(), FirstMove); 


    Coordinates SecondMove{4,2};
    result = Knight1->Move(SecondMove);

    EXPECT_FALSE(result); 
    EXPECT_EQ(Knight1->getObjectCoordinates(), FirstMove); 
}

TEST_F(UnitsUnderTestFixture, WrongActionForTheUnit)
{

    Coordinates Move{3, 1};
    bool result = BASE->Move(Move);

    EXPECT_FALSE(result); 
}

TEST_F(UnitsUnderTestFixture, MoveOutOfMap)
{

    Coordinates Move{-1,-1};
    bool result = Knight1->Move(Move);

    EXPECT_FALSE(result); 
}

TEST_F(UnitsUnderTestFixture, AttackRange)
{
    //To far to attack
    EXPECT_FALSE(Archer1->Attack(Catapult1)); 
    EXPECT_EQ(Catapult1->getEndurance(),50);


    EXPECT_TRUE(Catapult1->Attack(Archer1)); 
    EXPECT_EQ(Archer1->getEndurance(),0);
}

TEST_F(UnitsUnderTestFixture, SpeedPointsNeededToPerformAttack)
{
    //Whole speed points used
    EXPECT_TRUE(Archer1->Move(Coordinates{2,0}));

    //Try to perfrom attack in range
    EXPECT_FALSE(Archer1->Attack(Catapult1)); 
    EXPECT_EQ(Catapult1->getEndurance(),50);
}

TEST_F(UnitsUnderTestFixture, Mapa)
{

    EXPECT_TRUE(mapa.posibilityToStandOn(Knight1,Coordinates{0,0}));
    EXPECT_TRUE(mapa.posibilityToStandOn(Worker1,Coordinates{0,0}));
    EXPECT_TRUE(mapa.posibilityToStandOn(Worker1,Coordinates{1,1}));
    EXPECT_FALSE(mapa.posibilityToStandOn(Knight1,Coordinates{1,1}));

}



