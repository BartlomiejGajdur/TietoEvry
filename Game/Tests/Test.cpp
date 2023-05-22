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

    
    // std::string downloadMapa(){
    //     FileManager mapa("../Config/mapa.txt");
    //     mapa.openFile();
    //     mapa.readFromFile();
    //     std::string line = mapa.getFileContent();
    // }
    
    std::shared_ptr<Base> BASE = std::make_shared<Base>();
    std::shared_ptr<Knight> Knight1 = std::make_shared<Knight>(Coordinates{0,0},70);
    std::shared_ptr<Swordsman> Swordsman1 = std::make_shared<Swordsman>(Coordinates{1,1},60);
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


