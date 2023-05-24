#include <gtest/gtest.h>

#include <iostream>
#include "../Include/FileManager.hpp"
#include <algorithm>
#include "../Include/Coordinates.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/map.hpp"
#include "../Include/Units.hpp"
#include <memory>

#include <gtest/gtest.h>

struct UnitsUnderTestFixture : public ::testing::Test {
    Map mapa{
        "090\n600\n909\n000\n",
        std::make_shared<Player>(),
        std::make_shared<Player>(),
    };

    std::shared_ptr<Base> BASE = std::make_shared<Base>(Coordinates{2,2});
    std::shared_ptr<Knight> Knight1 = std::make_shared<Knight>(Coordinates{0,0},70);
    std::shared_ptr<Swordsman> Swordsman1 = std::make_shared<Swordsman>(Coordinates{1,1},60);
    std::shared_ptr<Archer> Archer1 = std::make_shared<Archer>(Coordinates{0,0},40);
    std::shared_ptr<Catapult> Catapult1 = std::make_shared<Catapult>(Coordinates{7,0},50);
    std::shared_ptr<Worker> Worker1 = std::make_shared<Worker>();
    std::shared_ptr<Knight> Knight2 = std::make_shared<Knight>(Coordinates{1,2},70);

    void addUnitsToEnemyPlayer(){
        mapa.getPlayerBelongsToEnemy()->addUnit(BASE);
        mapa.getPlayerBelongsToEnemy()->addUnit(Knight1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Swordsman1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Archer1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Catapult1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Worker1);

    }


    void addUnitsToOwnPlayer(){
        mapa.getPlayerBelongsToUs()->addUnit(Knight2);

    }
};


TEST_F(UnitsUnderTestFixture, MoveUnit_ValidCoordinates_ReturnsTrue) {
    addUnitsToEnemyPlayer();
    Coordinates validCoord{1, 2};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Knight1->getId(), validCoord);

    EXPECT_TRUE(result);
    EXPECT_EQ(Knight1->getObjectCoordinates(), validCoord);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_OutOfMapCoordinates_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates outOfMapCoord{10, 5};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Swordsman1->getId(), outOfMapCoord);

    EXPECT_FALSE(result);
    EXPECT_EQ(Swordsman1->getObjectCoordinates(), Coordinates(1, 1));  // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_UnitNotFound_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates validCoord{2, 2};
    int nonExistentId = 999;

    bool result = mapa.performMoveByPlayerBelongsToEnemy(nonExistentId, validCoord);

    EXPECT_FALSE(result);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_CannotStandOnField_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates invalidCoord{1, 0};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Archer1->getId(), invalidCoord);

    EXPECT_FALSE(result);
    EXPECT_EQ(Archer1->getObjectCoordinates(), Coordinates(0, 0));  // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_TooFarToMove_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates farCoord{7, 7};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Catapult1->getId(), farCoord);

    EXPECT_FALSE(result);
    EXPECT_EQ(Catapult1->getObjectCoordinates(), Coordinates(7, 0));  // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveBase_CannotMove_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates validCoord{1, 2};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(BASE->getId(), validCoord);

    EXPECT_FALSE(result);
    EXPECT_EQ(BASE->getObjectCoordinates(), Coordinates(2, 2));  // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_WorkerStandOnMine_ReturnsTrue) {
    addUnitsToEnemyPlayer();
    Coordinates MineCoord{0, 1};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Worker1->getId(), MineCoord);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(Worker1->getObjectCoordinates(), MineCoord);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_UnitStandOnMine_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    Coordinates MineCoord{0, 1};

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Knight1->getId(), MineCoord);

    EXPECT_FALSE(result);
    EXPECT_EQ(Knight1->getObjectCoordinates(), Coordinates(0, 0));  // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_StandindOnUnitBelongsToOtherPlayer_ReturnsFalse) {
    addUnitsToEnemyPlayer();
    addUnitsToOwnPlayer();

    //Perform moving Enemy player's units
    Coordinates OthersPlayerUnit = Knight2->getObjectCoordinates();

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Knight1->getId(), OthersPlayerUnit);

    EXPECT_FALSE(result);
    EXPECT_EQ(Knight1->getObjectCoordinates(), Coordinates(0, 0));  // Check that the unit's position remains unchanged

}

TEST_F(UnitsUnderTestFixture, MoveUnit_StandindOnUnitBelongsToOtherPlayer2_ReturnsFalse) {

    addUnitsToEnemyPlayer();
    addUnitsToOwnPlayer();

    //Perform moving Enemy player's units
    Coordinates OthersPlayerUnit = Knight1->getObjectCoordinates();

    bool result = mapa.performMoveByPlayerBelongsToUs(Knight2->getId(), OthersPlayerUnit);

    EXPECT_FALSE(result);
    EXPECT_EQ(Knight2->getObjectCoordinates(), Coordinates(1, 2));  // Check that the unit's position remains unchanged

    }
