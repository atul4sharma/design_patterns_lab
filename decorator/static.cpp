
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

struct Shape
{
  virtual std::string str() const = 0;
};

struct Circle : Shape
{
  float radius;

  Circle(){}

  explicit Circle(const float radius)
    : radius{radius}
  {
  }

  void resize(float factor)
  {
    radius *= factor;
  }

  std::string str() const override
  {
      std::ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square : Shape
{
  float side;

  Square(){}

  explicit Square(const float side)
    : side{side}
  {
  }

  std::string str() const override
  {
      std::ostringstream oss;
    oss << "A square of with side " << side;
    return oss.str();
  }
};

// we are not changing the base class of existing
// objects

// cannot make, e.g., ColoredSquare, ColoredCircle, etc.

struct ColoredShape : Shape
{
  Shape& shape;
  std::string color;

  ColoredShape(Shape& shape, const std::string& color)
    : shape{shape},
      color{color}
  {
  }

  std::string str() const override
  {
      std::ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

// mixin inheritance

template <typename T>
concept IsShape = std::is_base_of<Shape, T>::value;

template <typename T> struct ColoredShape2 : T
{
  std::string color;

  // need this (or not!)
  ColoredShape2(){}

  template <typename...Args>
  ColoredShape2(const std::string& color, Args ...args)
    : T(std::forward<Args>(args)...), color{color}
    // you cannot call base class ctor here
    // b/c you have no idea what it is
  {
  }

  std::string str() const override
  {
      std::ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T> struct TransparentShape2 : T
{
  uint8_t transparency;

  template<typename...Args>
  TransparentShape2(const uint8_t transparency, Args ...args)
    : T(std::forward<Args>(args)...), transparency{ transparency }
  {
  }

  std::string str() const override
  {
      std::ostringstream oss;
    oss << T::str() << " has "
      << static_cast<float>(transparency) / 255.f * 100.f
      << "% transparency";
    return oss.str();
  }
};


void mixin_inheritance()
{
  // won't work without a default constructor
  ColoredShape2<Circle> green_circle{ "green" };
  green_circle.radius = 123;
  std::cout << green_circle.str() << std::endl;

  TransparentShape2<ColoredShape2<Square>> blue_invisible_square{ 0 };
  blue_invisible_square.color = "blue";
  blue_invisible_square.side = 321;
  std::cout << blue_invisible_square.str() << std::endl;
}


int main()
{
  mixin_inheritance();
  return 0;
}
