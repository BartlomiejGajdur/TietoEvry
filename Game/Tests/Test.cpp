#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <memory>

#include "../Include/Coordinates.hpp"
#include "../Include/FileManager.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/Units.hpp"
#include "../Include/map.hpp"

struct UnitsUnderTestFixture : public ::testing::Test {
  Map mapa{
      "09001\n60000\n90000\n00002\n",
      std::make_shared<Player>(),
      std::make_shared<Player>(),
  };

  std::shared_ptr<Knight> Knight1 = std::make_shared<Knight>(Coordinates{0, 0}, 70);
  std::shared_ptr<Knight> Knight2 = std::make_shared<Knight>(Coordinates{2, 3}, 70);
  std::shared_ptr<Swordsman> Swordsman1 = std::make_shared<Swordsman>(Coordinates{1, 1}, 60);
  std::shared_ptr<Archer> Archer1 = std::make_shared<Archer>(Coordinates{0, 0}, 40);
  std::shared_ptr<Catapult> Catapult1 = std::make_shared<Catapult>(Coordinates{7, 0}, 50);
  std::shared_ptr<Worker> Worker1 = std::make_shared<Worker>(Coordinates{0, 0});

  std::shared_ptr<Knight> OwnPlayersKnight = std::make_shared<Knight>(Coordinates{1, 2}, 70);

  void addUnitsToEnemyPlayer() {
    mapa.get_PlayerE()->addUnit(Knight1);
    mapa.get_PlayerE()->addUnit(Swordsman1);
    mapa.get_PlayerE()->addUnit(Archer1);
    mapa.get_PlayerE()->addUnit(Catapult1);
    mapa.get_PlayerE()->addUnit(Worker1);
    mapa.get_PlayerE()->addUnit(Knight2);
  }

  void addUnitsToOwnPlayer() { mapa.get_PlayerP()->addUnit(OwnPlayersKnight); }
};

/*
Na koniec rundy ma sprawdzac rowniez ilosc workerow i ilu z nich jest w kopalnii
jakiejs i wykonac dodanie pieniedzy Czyli jakis wektor obiektow lub samych
lokalizacji tych obiektow/ potem leciec po kazdym unicie i jak jest ze jest
worker to sprawdzic lokalizacje czy pasuje z drugiego vectora, jestli tak to
licnzik ++*/
/*
Nowa runda ma rozdawac pieniadze/ wlasnie z tego u gory + produkcji czas ma
niwelowac jak spadnie na 0 to ma zmieniac ze unit produkcyjny jest to baza i
dodawac jednostke w miejscu bazy/ resetowanie speeda i mozliwosci ataku*/

TEST_F(UnitsUnderTestFixture, MoneySubstract)
{
    mapa.get_PlayerE()->substractMoney(400);
    EXPECT_EQ(mapa.get_PlayerE()->getMoney(),1600);
}


TEST_F(UnitsUnderTestFixture, GetBase_ReturnsCorrectUnit) {
  addUnitsToEnemyPlayer();
  addUnitsToOwnPlayer();
  EXPECT_EQ(mapa.get_PlayerE()->getBase()->getId(),
            mapa.get_PlayerE()->getUnits()[0]->getId());
}

TEST_F(UnitsUnderTestFixture, Production_Start) {

  long moneyBeforePurchase = mapa.get_PlayerP()->getMoney();
  
  EXPECT_TRUE(mapa.ProductAction_PlayerP(UnitTYPE::Catapult));
  EXPECT_EQ(mapa.get_PlayerP()->getMoney()+Unit::getPurchaseCost(UnitTYPE::Catapult),moneyBeforePurchase);
}

TEST_F(UnitsUnderTestFixture, Production_LackOfPlayersMoney) {
  
  mapa.get_PlayerP()->substractMoney(mapa.get_PlayerP()->getMoney());
  long moneyBeforePurchase = mapa.get_PlayerP()->getMoney();

  EXPECT_FALSE(mapa.ProductAction_PlayerP(UnitTYPE::Catapult));
  EXPECT_EQ(moneyBeforePurchase, mapa.get_PlayerP()->getMoney());
}

TEST_F(UnitsUnderTestFixture, Production_BaseDuringProduction) {
  long moneyBeforePurchase = mapa.get_PlayerP()->getMoney();  

  EXPECT_TRUE(mapa.ProductAction_PlayerP(UnitTYPE::Catapult));
  EXPECT_EQ(mapa.get_PlayerP()->getMoney()+Unit::getPurchaseCost(UnitTYPE::Catapult),moneyBeforePurchase);

  long moneyAfterPurchase = mapa.get_PlayerP()->getMoney();

  EXPECT_FALSE(mapa.ProductAction_PlayerP(UnitTYPE::Catapult));
  EXPECT_EQ(mapa.get_PlayerP()->getMoney(),moneyAfterPurchase);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_ValidCoordinates_ReturnsTrue) {
  addUnitsToEnemyPlayer();
  Coordinates validCoord{1, 2};

  bool result = mapa.MoveAction_PlayerE(Knight1->getId(), validCoord);

  EXPECT_TRUE(result);
  EXPECT_EQ(Knight1->getObjectCoordinates(), validCoord);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_OutOfMapCoordinates_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates outOfMapCoord{10, 5};

  bool result = mapa.MoveAction_PlayerE(Swordsman1->getId(), outOfMapCoord);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      Swordsman1->getObjectCoordinates(),
      Coordinates(1, 1)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_UnitNotFound_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates validCoord{2, 2};
  int nonExistentId = 999;

  bool result = mapa.MoveAction_PlayerE(nonExistentId, validCoord);

  EXPECT_FALSE(result);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_CannotStandOnField_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates invalidCoord{1, 0};

  bool result = mapa.MoveAction_PlayerE(Archer1->getId(), invalidCoord);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      Archer1->getObjectCoordinates(),
      Coordinates(0, 0)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_TooFarToMove_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates farCoord{7, 7};

  bool result = mapa.MoveAction_PlayerE(Catapult1->getId(), farCoord);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      Catapult1->getObjectCoordinates(),
      Coordinates(7, 0)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveBase_CannotMove_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates validCoord{1, 2};

  bool result = mapa.MoveAction_PlayerE(
      mapa.get_PlayerE()->getUnits()[0]->getId(), validCoord);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      mapa.get_PlayerE()->getUnits()[0]->getObjectCoordinates(),
      Coordinates(3, 4)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, MoveUnit_WorkerStandOnMine_ReturnsTrue) {
  addUnitsToEnemyPlayer();
  Coordinates MineCoord{0, 1};

  bool result = mapa.MoveAction_PlayerE(Worker1->getId(), MineCoord);

  EXPECT_TRUE(result);
  EXPECT_EQ(Worker1->getObjectCoordinates(), MineCoord);
}

TEST_F(UnitsUnderTestFixture, MoveUnit_UnitStandOnMine_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  Coordinates MineCoord{0, 1};

  bool result = mapa.MoveAction_PlayerE(Knight1->getId(), MineCoord);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      Knight1->getObjectCoordinates(),
      Coordinates(0, 0)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture,
       MoveUnit_StandindOnUnitBelongsToOtherPlayer_ReturnsFalse) {
  addUnitsToEnemyPlayer();
  addUnitsToOwnPlayer();

  // Perform moving Enemy player's units
  Coordinates OthersPlayerUnit = OwnPlayersKnight->getObjectCoordinates();

  bool result = mapa.MoveAction_PlayerE(Knight1->getId(), OthersPlayerUnit);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      Knight1->getObjectCoordinates(),
      Coordinates(0, 0)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture,
       MoveUnit_StandindOnUnitBelongsToOtherPlayer2_ReturnsFalse) {

  addUnitsToEnemyPlayer();
  addUnitsToOwnPlayer();

  // Perform moving Enemy player's units
  Coordinates OthersPlayerUnit = Knight1->getObjectCoordinates();

  bool result =
      mapa.MoveAction_PlayerP(OwnPlayersKnight->getId(), OthersPlayerUnit);

  EXPECT_FALSE(result);
  EXPECT_EQ(
      OwnPlayersKnight->getObjectCoordinates(),
      Coordinates(1, 2)); // Check that the unit's position remains unchanged
}

TEST_F(UnitsUnderTestFixture, PerformAttack_TooFarAway) {
  addUnitsToOwnPlayer();
  addUnitsToEnemyPlayer();

  // Attempt to attack when units are too far away
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = Knight1->getId();
  EXPECT_FALSE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
}

TEST_F(UnitsUnderTestFixture, PerformAttack_MoveAndAttack) {
  addUnitsToOwnPlayer();
  addUnitsToEnemyPlayer();

  // Move unit closer and perform attack
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = Knight2->getId();

  // Perform move to attack the enemy
  EXPECT_TRUE(
      mapa.MoveAction_PlayerP(OwnPlayersKnight->getId(), Coordinates{2, 2}));
  EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

  // Perform attack
  EXPECT_TRUE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
  EXPECT_EQ(Knight2->getEndurance(), 35);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_MoveAndAttack_Failure) {
  addUnitsToOwnPlayer();
  addUnitsToEnemyPlayer();

  // Move unit closer and attempt to attack, but no speed points left
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = Knight2->getId();

  // Perform move to attack the enemy
  EXPECT_TRUE(
      mapa.MoveAction_PlayerP(OwnPlayersKnight->getId(), Coordinates{3, 3}));
  EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(3, 3));

  EXPECT_TRUE(
      mapa.MoveAction_PlayerP(OwnPlayersKnight->getId(), Coordinates{2, 2}));
  EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

  // Attempt to attack without any speed points remaining
  EXPECT_FALSE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
  EXPECT_EQ(Knight2->getEndurance(), 70);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_DoubleAttack_Failure) {
  addUnitsToOwnPlayer();
  addUnitsToEnemyPlayer();

  // Move unit closer and perform attack, then attempt another attack
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = Knight2->getId();

  // Perform move to attack the enemy
  EXPECT_TRUE(
      mapa.MoveAction_PlayerP(OwnPlayersKnight->getId(), Coordinates{2, 2}));
  EXPECT_EQ(OwnPlayersKnight->getObjectCoordinates(), Coordinates(2, 2));

  // First attack
  EXPECT_TRUE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
  EXPECT_EQ(Knight2->getEndurance(), 35);

  // Second attack attempt (should fail)
  EXPECT_FALSE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
  EXPECT_EQ(Knight2->getEndurance(), 35);
}

TEST_F(UnitsUnderTestFixture, PerformAttack_UnitNotFound_PlayerP) {
  addUnitsToEnemyPlayer();

  // Attempt to attack with a unit that doesn't belong to the player
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = Knight1->getId();

  EXPECT_FALSE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
}

TEST_F(UnitsUnderTestFixture, PerformAttack_UnitNotFound_PlayerE) {
  addUnitsToOwnPlayer();

  // Attempt to attack a unit that doesn't exist
  int playerUnitId = OwnPlayersKnight->getId();
  int enemyUnitId = 12345; // Wrong ID

  EXPECT_FALSE(mapa.AttackAction_PlayerP(playerUnitId, enemyUnitId));
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
  EXPECT_TRUE(mapa.AttackAction_PlayerE(enemyUnitId_1, playerUnitId));
  EXPECT_EQ(OwnPlayersKnight->getEndurance(), 40);

  EXPECT_TRUE(mapa.AttackAction_PlayerE(enemyUnitId_2, playerUnitId));
  EXPECT_EQ(OwnPlayersKnight->getEndurance(), 25);

  // Move unit closer to the enemy
  EXPECT_TRUE(mapa.MoveAction_PlayerE(enemyUnitId_3, Coordinates{1, 1}));
  EXPECT_EQ(Knight1->getObjectCoordinates(), Coordinates(1, 1));

  // Perform attack that results in the player's unit being killed
  size_t before = mapa.get_PlayerP()->getUnits().size();
  EXPECT_TRUE(mapa.AttackAction_PlayerE(enemyUnitId_3, playerUnitId));
  EXPECT_EQ(mapa.get_PlayerP()->getUnitByID(playerUnitId), nullptr);
  EXPECT_EQ(before - 1, mapa.get_PlayerP()->getUnits().size());
}
