#include "../Include/Time.hpp"
#include <iostream>

void Time::addObserver(Observer *obs)
{
    observers_.push_back(obs);
}

void Time::removeObserver(Observer *obs)
{
    observers_.remove(obs);
}

void Time::nextRound()
{
    ++Round_;

    auto it = observers_.begin();

    while (it != observers_.end())
    {
        (*it)->nextRound();
        ++it;
    }
}