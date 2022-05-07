#pragma once

#include "observer.hpp"

#include <vector>
#include <algorithm>
#include <string>

struct Observable
{
    virtual ~Observable() = default;

    virtual void subsribe(Observer & ob)
    {
        observers.push_back(&ob);
    }

    virtual void unsubscribe(Observer & ob)
    {
        observers.erase(
                std::remove(observers.begin(), observers.end(), &ob),
                observers.end()
                );
    }

    virtual void notify(std::string const & message)
    {
        for(auto * ob: observers)
            ob->update(message);
    }

    private:
        std::vector<Observer *> observers;
};
