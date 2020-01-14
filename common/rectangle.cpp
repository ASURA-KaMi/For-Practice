#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <math.h>

vertola::Rectangle::Rectangle(const vertola::rectangle_t & r):
  rect_(r),
  angle_(0)
{
  if(rect_.width < 0.0)
  {
    throw std::invalid_argument("ERR WIDTH");
  }
  if(rect_.height < 0.0)
  {
    throw std::invalid_argument("ERR HEIGHT");
  }
}

double vertola::Rectangle::getArea() const
{
  return (rect_.width * rect_.height);
}

vertola::rectangle_t vertola::Rectangle::getFrameRect() const
{
  const double sine = sin(angle_* M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double height = fabs(rect_.height * cosine) + fabs(rect_.width * sine);
  const double width = fabs(rect_.width * cosine) + fabs(rect_.height * sine);
  return {width, height, rect_.pos};
}

double vertola::Rectangle::getAngle() const
{
  return angle_;
}

void vertola::Rectangle::move(const vertola::point_t & point) 
{
  rect_.pos = point;
}

void vertola::Rectangle::move(const double dx, const double dy) 
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void vertola::Rectangle::scale(const double scf)
{
  if (scf < 0.0)
  {
    throw std::invalid_argument("scale Value < 0.0");
  }
  rect_.width *= scf;
  rect_.height *= scf;
}
void vertola::Rectangle::getInfo() const
{
  std::cout << std::endl << "h: "<<rect_.height<<"\t"<<"w: " << rect_.width << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "Point(x, y): (" << rect_.pos.x << ", " << rect_.pos.y << ")" << std::endl;
  std::cout << "Frame rectangle(h,w,center(x,y)): " << getFrameRect().height << ", " << getFrameRect().width
      << ", (" << getFrameRect().pos.x << ", " << getFrameRect().pos.y << ")" << std::endl;
}
void vertola::Rectangle::rotate(const double a)
{
  angle_ += a;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
}
