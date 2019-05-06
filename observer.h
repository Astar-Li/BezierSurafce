#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer
{
public:
    virtual void handleNotification() = 0;
};

class Observable
{
public:
    void addObserver(Observer &observer)
    {
        observers.push_back(&observer);
    }
    void notifyObservers()
    {
        for (auto& observer : observers)
            observer->handleNotification();
    }
private:
    std::vector<Observer *> observers;
};

#endif // OBSERVER_H
