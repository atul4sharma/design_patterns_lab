#pragma once

#include <string>
#include <iostream>

struct Observer
{
    virtual ~Observer() = default;

    virtual void update(std::string const & message)
    {
        std::cout << message << "\n";
    }
};
