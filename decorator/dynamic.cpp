
#include <iostream>
#include <sstream>
#include <string>

struct Shape
{
    virtual std::string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "Circle has radius of " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    explicit Square(float side)
        : side{side}
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "Square has side " << side;
        return oss.str();
    }
};

struct ColoredSquare : Shape
{
    Shape & shape;
    std::string color;

    ColoredSquare(Shape & shape, std::string const & color)
        :shape{shape}
        ,color{color}
    {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " is of color " << color;
        return oss.str();
    }

};

int main()
{
    Square square{10};
    std::cout << square.str() << "\n";

    ColoredSquare coloredSq{square, "blue"};
    std::cout << coloredSq.str() << "\n";

    return 0;
}
