#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <memory>

#include "../Include/Coordinates.hpp"
#include "../Include/FileManager.hpp"
#include "../Include/MapObjects.hpp"
#include "../Include/Units.hpp"
#include "../Include/map.hpp"
/*
16600000000000000000000000000000
00000009999000000000000000000000
00000009999000000600000000000000
00000009999000000000000000000000
00000000000000000000000000000662
Coordinates[0-4][0-31]
*/

std::vector<Coordinates> MineCoordinates{
    {0,1},{0,2},{2,17},{4,29},{4,30}
};

std::vector<Coordinates> WorkersCoordinates{
   {4,31},{4,28}, {2,19},{0,1},{2,17}
};

struct MapUnderTestFixture : public ::testing::Test {
  Map map{
      "16600000000000000000000000000000\n00000009999000000000000000000000\n00000009999000000600000000000000\n00000009999000000000000000000000\n00000000000000000000000000000662\n",
      std::make_shared<Player>(),
      std::make_shared<Player>(),
  };

  void addToPlayerE()
  {
    //Not on the mine square - 3 workers
    std::shared_ptr<Worker> Worker1 = std::make_shared<Worker>(Coordinates{4, 31});
    std::shared_ptr<Worker> Worker2 = std::make_shared<Worker>(Coordinates{4, 28});
    std::shared_ptr<Worker> Worker3 = std::make_shared<Worker>(Coordinates{2, 19});

    //On mine square - 2 workers
    std::shared_ptr<Worker> Worker4 = std::make_shared<Worker>(Coordinates{0, 1});
    std::shared_ptr<Worker> Worker5 = std::make_shared<Worker>(Coordinates{2, 17});

    map.get_PlayerE()->addUnit(Worker1);
    map.get_PlayerE()->addUnit(Worker2);
    map.get_PlayerE()->addUnit(Worker3);
    map.get_PlayerE()->addUnit(Worker4);
    map.get_PlayerE()->addUnit(Worker5);
  }
};

TEST_F(MapUnderTestFixture, VectorMines)
{
    EXPECT_EQ(MineCoordinates, map.getMineCoordinates());
}

TEST_F(MapUnderTestFixture, WorkersVector)
{
    addToPlayerE();
    EXPECT_EQ(WorkersCoordinates, map.get_PlayerE()->getWorkersCoordinates());
}

