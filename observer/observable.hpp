#pragma once

#include <vector>
#include <algorithm>
#include <string>

template <typename>
struct Observer;

template <typename T>
struct Observable
{
    virtual void subsribe(Observer<T> & ob)
    {
        observers.push_back(&ob);
    }

    virtual void unsubscribe(Observer<T> & ob)
    {
        observers.erase(
                std::remove(observers.begin(), observers.end(), &ob),
                observers.end()
                );
    }

    virtual void notify(T & source, std::string const & field)
    {
        for(auto * ob: observers)
            ob->field_changed(source, field);
    }

    private:
        std::vector<Observer<T> *> observers;
};
