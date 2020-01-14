#ifndef RECT_HPP
#define RECT_HPP

#include "shape.hpp"
namespace vertola
{
  class Rectangle : public Shape 
  {
  public:
    Rectangle(const rectangle_t & r);
    double getArea() const override;
    double getAngle() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(const double dx, const double dy) override;
    void scale(const double scf) override;
    void getInfo() const override;
    void rotate(const double a) override;
  private:
    rectangle_t rect_;
    double angle_;
  };
}
#endif
