#include <gtest/gtest.h>

// Przykładowa klasa lub funkcje do przetestowania
int Dodaj(int a, int b) {
    return a + b;
}

// Przykładowy test
TEST(DodajTest, DodajLiczby) {
    EXPECT_EQ(Dodaj(2, 3), 5);
    EXPECT_EQ(Dodaj(-1, 1), 0);
    EXPECT_EQ(Dodaj(0, 0), 0);
}

