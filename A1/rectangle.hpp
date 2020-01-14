#ifndef RECT_HPP
#define RECT_HPP

#include "shape.hpp"

class Rectangle : public Shape {
public:
  Rectangle(const rectangle_t & r);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
private:
  rectangle_t rect_;
};

#endif
