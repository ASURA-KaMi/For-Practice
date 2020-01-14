#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(const rectangle_t & r):
  rect_(r)
{
  assert(rect_.width >= 0.0);
  assert(rect_.height >= 0.0);
}

double Rectangle::getArea() const
{
  return (rect_.width * rect_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & point) 
{
  rect_.pos = point;
}

void Rectangle::move(const double dx, const double dy) 
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
