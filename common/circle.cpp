#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <math.h>

vertola::Circle::Circle(const double r, const vertola::point_t & c):
  radius_(r),
  center_(c),
  angle_(0)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Radius < 0.0");
  }
}

double vertola::Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

double vertola::Circle::getAngle() const
{
  return angle_;
}

vertola::rectangle_t vertola::Circle::getFrameRect() const
{
  rectangle_t rectangle = { 2 * radius_, 2 * radius_, center_ };
  return {rectangle.height, rectangle.width, rectangle.pos};
}

void vertola::Circle::move(const vertola::point_t & point)
{
  center_ = point;
}

void vertola::Circle::move(const double dx, const double dy) 
{
  center_.x += dx;
  center_.y += dy;
}

void vertola::Circle::scale(const double scf)
{
  if (scf < 0.0)
  {
    throw std::invalid_argument("scale Value < 0.0");
  }
  radius_ *= scf;
}
void vertola::Circle::getInfo() const
{
  std::cout << std::endl << "Radius: " << radius_ << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "Point(x, y): (" << center_.x << ", " << center_.y << ")" << std::endl;
  std::cout << "Frame rectangle(h,w,center(x,y)): " << getFrameRect().height << ", " << getFrameRect().width
      <<", ("<<getFrameRect().pos.x<<", "<<getFrameRect().pos.y<<")"<<std::endl;
}
void vertola::Circle::rotate(const double a)
{
  angle_ += a;
}
