#pragma once

#include <string>
#include <iostream>

template <typename T>
struct Observer
{
    virtual void field_changed(T& source, std::string const & field) = 0;

};
