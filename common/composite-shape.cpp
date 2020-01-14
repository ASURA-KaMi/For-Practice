#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>


vertola::CompositeShape::CompositeShape(std::shared_ptr <vertola::Shape> shape):
  arr_(nullptr),
  quant_(0),
  angle_(0)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  
  addShape(shape);
}

vertola::CompositeShape::CompositeShape(const vertola::CompositeShape & shapeCopy):
  quant_(shapeCopy.quant_),
  angle_(shapeCopy.angle_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> CopyList(new std::shared_ptr<Shape>[quant_]);
  {
    for (size_t i = 0; i < quant_; ++i)
    {
      CopyList[i] = shapeCopy.arr_[i];
    }
    arr_.swap(CopyList);
  }
}

vertola::CompositeShape::CompositeShape(vertola::CompositeShape && shapeMove):
  arr_(std::move(shapeMove.arr_)),
  quant_(shapeMove.quant_),
  angle_(shapeMove.angle_)
{
  shapeMove.arr_.reset();
  shapeMove.quant_ = 0;
  shapeMove.angle_ = 0;
}

vertola::CompositeShape & vertola::CompositeShape::operator=(const vertola::CompositeShape & shapeCopy)
{
  if (this == & shapeCopy)
  {
    return *this;
  }
  quant_ = shapeCopy.quant_;
  angle_ = shapeCopy.angle_;
  std::unique_ptr<std::shared_ptr<vertola::Shape>[]> new_arr_(new std::shared_ptr<vertola::Shape>[quant_]);
  for (size_t i = 0; i < quant_; ++i)
  {
    new_arr_[i] = shapeCopy.arr_[i];
  }
  arr_.swap(new_arr_);
  
  return *this;
}

vertola::CompositeShape & vertola::CompositeShape::operator=(vertola::CompositeShape && shapeMove)
{
  if (this != & shapeMove)
  {
    arr_.swap(shapeMove.arr_);
    quant_ = shapeMove.quant_;
    shapeMove.arr_.reset();
    shapeMove.quant_ = 0;
    shapeMove.angle_ = 0;
  }
  return *this;
}

double vertola:: CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < quant_; ++i)
  {
    area += arr_[i]->getArea();
  }
  return area;
}

vertola::rectangle_t vertola::CompositeShape::getFrameRect() const
{
  double width;
  double height;
  vertola::point_t center;
  if (quant_ != 0)
  {
    vertola::rectangle_t frameRect = arr_[0]->getFrameRect();
    double left = frameRect.pos.x - (frameRect.width / 2);
    double right = frameRect.pos.x + (frameRect.width / 2);
    double bottom = frameRect.pos.y - (frameRect.height / 2);
    double top = frameRect.pos.y + (frameRect.height / 2);
    for (size_t i = 1; i < quant_; ++i)
    {
      frameRect = arr_[i]->getFrameRect();
      double left_i = frameRect.pos.x - (frameRect.width / 2);
      double right_i = frameRect.pos.x + (frameRect.width / 2);
      double bottom_i = frameRect.pos.y - (frameRect.height / 2);
      double top_i = frameRect.pos.y + (frameRect.height / 2);

      if (left_i < left)
      {
        left = left_i;
      }
      if (right_i > right)
      {
        right = right_i;
      }
      if (bottom_i < bottom)
      {
        bottom = bottom_i;
      }
      if (top_i > top)
      {
        top = top_i;
      }
    }
    width = right - left;
    height = top - bottom;
    center = {((left + right) / 2), ((top + bottom) / 2)};
  }
  else
  {
    width = 0;
    height = 0;
    center = {0, 0};
  }
  return{width, height, center};
}

void vertola::CompositeShape::move(const double dx, const double dy)
{
  for (size_t i = 0; i < quant_; ++i)
  {
    arr_[i]->move(dx, dy);
  }
}

void vertola::CompositeShape::move(const vertola::point_t & newPos)
{
  const vertola::point_t curPos = getFrameRect().pos;
  double dx = (newPos.x - curPos.x);
  double dy = (newPos.y - curPos.y);
  move(dx, dy);
}

void vertola::CompositeShape::scale(const double scf)
{
  if (scf < 0)
  {
    throw std::invalid_argument("Invalid scf");
  }
  
  const vertola::point_t curPos = getFrameRect().pos;
  for (size_t i = 0; i < quant_; ++i)
  {
    const vertola::point_t shapePos = arr_[i]->getFrameRect().pos;
    arr_[i]->move((scf - 1) * (shapePos.x - curPos.x), (scf - 1) * (shapePos.y - curPos.y));
    arr_[i]->scale(scf);
  }
}

void vertola::CompositeShape::rotate(const double deg)
{
  angle_ += deg;
  if (fabs(angle_) >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
  const double sn = sin(deg * M_PI / 180);
  const double csn = cos(deg * M_PI / 180);
  const vertola::point_t curPos = getFrameRect().pos;
  for (size_t i = 0; i < quant_; ++i)
  {
    const vertola::point_t shapePos = arr_[i]->getFrameRect().pos;
    arr_[i]->move({(shapePos.x - curPos.x) * csn + (shapePos.y - curPos.y) * sn + curPos.x,
        (shapePos.y - curPos.y) * csn + (shapePos.x - curPos.x) * sn + curPos.y});
    arr_[i]->rotate(deg);
  } 
}

double vertola::CompositeShape::getAngle() const
{
  return angle_;
}

void vertola::CompositeShape::addShape(const std::shared_ptr <vertola::Shape> newShape)
{
  if (!newShape)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  
  for (size_t i = 0; i < quant_; ++i)
  {
    if (newShape == arr_[i])
    {
      throw std::invalid_argument("This shape is already a part of this CompositeShape");
    }
  }

  std::unique_ptr <std::shared_ptr <vertola::Shape>[]> newList(new std::shared_ptr <vertola::Shape>[quant_ + 1]);
  for (size_t i = 0; i < quant_; ++i)
  {
    newList[i] = arr_[i];
  }
  newList[quant_++] = newShape;
  arr_.swap(newList);
}

std::shared_ptr <vertola::Shape> vertola::CompositeShape::getShape(size_t const index) const
{
  if (index >= quant_)
  {
    throw std::out_of_range("Invalid index");
  }
  return arr_[index];
}

void vertola::CompositeShape::deleteShape(const size_t index)
{
  if (quant_ == 0)
  {
    throw std::invalid_argument("Empty CompositeShape");
  }
  else
  {
    if ((index <= 0) || (index > quant_))
    {
      throw std::invalid_argument("Invalid index");
    }
  }

  if (quant_ == 1)
  {
    clear();
  }
  else
  {
    std::unique_ptr <std::shared_ptr <vertola::Shape>[]> newParts(new std::shared_ptr <vertola::Shape>[quant_ - 1]);
    for (size_t i = 0; i < (index - 1); ++i)
    {
      newParts[i] = arr_[i];
    }
    for (size_t i = index; i < quant_; ++i)
    {
      newParts[i - 1] = arr_[i];
    }
    arr_.swap(newParts);
    --quant_;
  }
}

void vertola::CompositeShape::clear()
{
  arr_.reset();
  arr_ = nullptr;
  quant_ = 0;
}

size_t vertola::CompositeShape::getQuantity() const
{
  return quant_;
}
void vertola::CompositeShape::getInfo() const
{
  if (quant_ != 0)
  {
    for (size_t i = 0; i < quant_; i++)
    {
      getShape(i)->getInfo();
    }
  }
  else
  {
    std::cout << "No shapes in compositeshape" << std::endl;
  }
}
