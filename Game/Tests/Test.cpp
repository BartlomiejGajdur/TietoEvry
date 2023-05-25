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
        "0900\n6000\n9000\n0000\n",
        std::make_shared<Player>(),
        std::make_shared<Player>(),
    };

    std::shared_ptr<Base> BASE = std::make_shared<Base>(Coordinates{2,4});
    std::shared_ptr<Knight> Knight1 = std::make_shared<Knight>(Coordinates{0,0},70);
    std::shared_ptr<Knight> Knight2 =  std::make_shared<Knight>(Coordinates{2,3},70);
    std::shared_ptr<Swordsman> Swordsman1 = std::make_shared<Swordsman>(Coordinates{1,1},60);
    std::shared_ptr<Archer> Archer1 = std::make_shared<Archer>(Coordinates{0,0},40);
    std::shared_ptr<Catapult> Catapult1 = std::make_shared<Catapult>(Coordinates{7,0},50);
    std::shared_ptr<Worker> Worker1 = std::make_shared<Worker>(Coordinates{0,0});
    std::shared_ptr<Knight> OwnPlayersKnight = std::make_shared<Knight>(Coordinates{1,2},70);

    void addUnitsToEnemyPlayer(){
        mapa.getPlayerBelongsToEnemy()->addUnit(BASE);
        mapa.getPlayerBelongsToEnemy()->addUnit(Knight1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Swordsman1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Archer1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Catapult1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Worker1);
        mapa.getPlayerBelongsToEnemy()->addUnit(Knight2);

    }


    void addUnitsToOwnPlayer(){
        mapa.getPlayerBelongsToUs()->addUnit(OwnPlayersKnight);

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
    EXPECT_EQ(BASE->getObjectCoordinates(), Coordinates(2, 4));  // Check that the unit's position remains unchanged
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
    Coordinates OthersPlayerUnit = OwnPlayersKnight->getObjectCoordinates();

    bool result = mapa.performMoveByPlayerBelongsToEnemy(Knight1->getId(), OthersPlayerUnit);

    EXPECT_FALSE(result);
    EXPECT_EQ(Knight1->getObjectCoordinates(), Coordinates(0, 0));  // Check that the unit's position remains unchanged

}

TEST_F(UnitsUnderTestFixture, MoveUnit_StandindOnUnitBelongsToOtherPlayer2_ReturnsFalse) {

    addUnitsToEnemyPlayer();
    addUnitsToOwnPlayer();

    //Perform moving Enemy player's units
    Coordinates OthersPlayerUnit = Knight1->getObjectCoordinates();

    bool result = mapa.performMoveByPlayerBelongsToUs(OwnPlayersKnight->getId(), OthersPlayerUnit);

    EXPECT_FALSE(result);
    EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(1, 2));  // Check that the unit's position remains unchanged

    }

TEST_F(UnitsUnderTestFixture, PerformAttack_TooFarAway) {
    addUnitsToOwnPlayer();
    addUnitsToEnemyPlayer();

    // Attempt to attack when units are too far away
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = Knight1->getId();
    EXPECT_FALSE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
}

TEST_F(UnitsUnderTestFixture, PerformAttack_MoveAndAttack) {
    addUnitsToOwnPlayer();
    addUnitsToEnemyPlayer();

    // Move unit closer and perform attack
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = Knight2->getId();

    // Perform move to attack the enemy
    EXPECT_TRUE(mapa.performMoveByPlayerBelongsToUs(OwnPlayersKnight->getId(), Coordinates{2, 2}));
    EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

    // Perform attack
    EXPECT_TRUE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
    EXPECT_EQ(Knight2->getEndurance(), 35);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_MoveAndAttack_Failure) {
    addUnitsToOwnPlayer();
    addUnitsToEnemyPlayer();

    // Move unit closer and attempt to attack, but no speed points left
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = Knight2->getId();

    // Perform move to attack the enemy
    EXPECT_TRUE(mapa.performMoveByPlayerBelongsToUs(OwnPlayersKnight->getId(), Coordinates{3, 3}));
    EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(3, 3));

    EXPECT_TRUE(mapa.performMoveByPlayerBelongsToUs(OwnPlayersKnight->getId(), Coordinates{2, 2}));
    EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

    // Attempt to attack without any speed points remaining
    EXPECT_FALSE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
    EXPECT_EQ(Knight2->getEndurance(), 70);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_DoubleAttack_Failure) {
    addUnitsToOwnPlayer();
    addUnitsToEnemyPlayer();

    // Move unit closer and perform attack, then attempt another attack
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = Knight2->getId();

    // Perform move to attack the enemy
    EXPECT_TRUE(mapa.performMoveByPlayerBelongsToUs(OwnPlayersKnight->getId(), Coordinates{2, 2}));
    EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

    // First attack
    EXPECT_TRUE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
    EXPECT_EQ(Knight2->getEndurance(), 35);

    // Second attack attempt (should fail)
    EXPECT_FALSE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
    EXPECT_EQ(Knight2->getEndurance(), 35);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_UnitNotFound_PlayerP) {
    addUnitsToEnemyPlayer();

    // Attempt to attack with a unit that doesn't belong to the player
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = Knight1->getId();

    EXPECT_FALSE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
}

TEST_F(UnitsUnderTestFixture, PerformAttack_UnitNotFound_PlayerE) {
    addUnitsToOwnPlayer();

    // Attempt to attack a unit that doesn't exist
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId = 12345; // Wrong ID

    EXPECT_FALSE(mapa.performAttackByPlayerBelongsToUs(playerUnitId, enemyUnitId));
}

TEST_F(UnitsUnderTestFixture, PerformAttack_UnitDies) {
    addUnitsToOwnPlayer();
    addUnitsToEnemyPlayer();

    // Attack an enemy unit until it dies
    int playerUnitId = OwnPlayersKnight->getId();
    int enemyUnitId_1 = Swordsman1->getId();
    int enemyUnitId_2 = Archer1->getId();
    int enemyUnitId_3 = Knight1->getId();

    // Attack enemy units multiple times
    EXPECT_TRUE(mapa.performAttackByPlayerBelongsToEnemy(enemyUnitId_1, playerUnitId));
    EXPECT_EQ(OwnPlayersKnight->getEndurance(), 40);

    EXPECT_TRUE(mapa.performAttackByPlayerBelongsToEnemy(enemyUnitId_2, playerUnitId));
    EXPECT_EQ(OwnPlayersKnight->getEndurance(), 25);

    // Move unit closer to the enemy
    EXPECT_TRUE(mapa.performMoveByPlayerBelongsToEnemy(enemyUnitId_3, Coordinates{1, 1}));
    EXPECT_EQ(Knight1->getObjectCoordinates(), Coordinates(1, 1));

    // Perform attack that results in the player's unit being killed
    size_t before = mapa.getPlayerBelongsToUs()->getUnits().size();
    EXPECT_TRUE(mapa.performAttackByPlayerBelongsToEnemy(enemyUnitId_3, playerUnitId));
    EXPECT_EQ(mapa.getPlayerBelongsToUs()->getUnitByID(playerUnitId), nullptr);
    EXPECT_EQ(before - 1, mapa.getPlayerBelongsToUs()->getUnits().size());
}
