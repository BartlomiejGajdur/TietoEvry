#pragma once
#include <list>

const short MAX_GAME_ROUNDS{2000};

class Observer{
    public:
    virtual void nextRound() = 0;
    virtual ~Observer(){};
};

class Time{
    public:
    Time(){};
    Time(int Round): Round_(Round) {}

    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
    void nextRound();

    private:
    int Round_{0};
    std::list<Observer*> observers_;
};