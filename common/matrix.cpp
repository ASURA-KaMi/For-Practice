#include"matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <new>
#include <algorithm>
#include"shape.hpp"

using vertola::shape_pointer;
using vertola::array_pointer;

vertola::Matrix::Matrix(const shape_pointer &fig) :
  matrix_(nullptr),
  laycount_(0),
  laysize_(0)
{
  if (fig == nullptr)
  {
    throw std::invalid_argument("Empty Pointer");
  }
  addElement(fig);
}

vertola::Matrix::Matrix(const vertola::CompositeShape & composite_shape) :
  matrix_(nullptr),
  laycount_(0),
  laysize_(0)
{
  if (composite_shape.getQuantity() == 0)
  {
    throw std::invalid_argument("Empty CompositeShape");
  }
  for (size_t i = 0; i < composite_shape.getQuantity(); ++i)
  {
    addElement(composite_shape.getShape(i));
  }

}

vertola::Matrix::Matrix(const Matrix & figname):
  matrix_(new shape_pointer[figname.laycount_ * figname.laysize_]),
  laycount_(figname.laycount_),
  laysize_(figname.laysize_)
{
  for(size_t i=0;i<laycount_*laysize_;++i)
  {
    matrix_[i]=figname.matrix_[i];
  }
}

vertola::Matrix::Matrix(Matrix && figname):
  matrix_(std::move(figname.matrix_)),
  laycount_(figname.laycount_),
  laysize_(figname.laysize_)
{
  figname.matrix_ = nullptr;
  figname.laycount_ = 0;
  figname.laysize_ = 0;
}

vertola::Matrix::~Matrix()
{
  matrix_=nullptr;
  laycount_ = 0;
  laysize_ = 0;
}

vertola::Matrix & vertola::Matrix::operator= (const vertola::Matrix & figname)
{
  if (this == &figname)
  {
    return *this;
  }
  matrix_.reset(new shape_pointer [figname.laysize_*figname.laycount_] );
  laycount_ = figname.laycount_;
  laysize_ = figname.laysize_;
  for(size_t i = 0;i < laycount_ * laysize_; ++i)
  {
    matrix_[i] = figname.matrix_[i];
  }
  return *this;
}

vertola::Matrix & vertola::Matrix::operator= (vertola::Matrix && figname)
{
  if (this == &figname)
  {
    return *this;
  }
  matrix_.reset(new shape_pointer[figname.laycount_* figname.laysize_]);
  laysize_ = figname.laysize_;
  laycount_ = figname.laycount_;
  matrix_=std::move(figname.matrix_);
  figname.matrix_ = nullptr;
  figname.laycount_ = 0;
  figname.laysize_ = 0;
  return *this;
}

bool vertola::Matrix::operator==(const vertola::Matrix & copy_m) const
{
  if ((this->laycount_ == copy_m.laycount_) && (this->laysize_ == copy_m.laysize_))
  {
    bool equal = true;
    for (size_t i = 0; i < laycount_ * laysize_; ++i)
    {
      if (!(this->matrix_[i] == copy_m.matrix_[i]))
      {
        equal = false;
      }
    }
    if (equal)
    {
      return true;
    }
  }
  return false;
}

bool vertola::Matrix::operator!=(const vertola::Matrix & copy_m) const
{
  return !(this == &copy_m);
}


array_pointer vertola::Matrix::operator[](size_t laynum) const
{
  if (laycount_ == 0)
  {
    throw std::out_of_range("Matrix is empty");
  }
  if (laynum > laycount_ - 1)
  {
    throw std::invalid_argument("Invalid layerCount layer number");
  }
  array_pointer layer(new shape_pointer[laysize_]);
  for (size_t i = 0; i < laysize_; ++i)
  {
    layer[i] = matrix_[laynum * laysize_ + i];
  }
  return layer;
}

bool vertola::Matrix::overlapping(size_t laynum, const shape_pointer fig) const
{
  vertola::rectangle_t nShapeFrameRect = fig->getFrameRect();
  vertola::rectangle_t mShapeFrameRect = matrix_[laynum]->getFrameRect();
  vertola::point_t newPoints[4] = {
    { nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0 },
    { nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y + nShapeFrameRect.height / 2.0 },
    { nShapeFrameRect.pos.x + nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0 },
    { nShapeFrameRect.pos.x - nShapeFrameRect.width / 2.0, nShapeFrameRect.pos.y - nShapeFrameRect.height / 2.0 }
  };

  vertola::point_t matrixPoints[4] = {
    { mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0 },
    { mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y + mShapeFrameRect.height / 2.0 },
    { mShapeFrameRect.pos.x + mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0 },
    { mShapeFrameRect.pos.x - mShapeFrameRect.width / 2.0, mShapeFrameRect.pos.y - mShapeFrameRect.height / 2.0 }
  };

  for (int i = 0; i < 4; ++i)
  {
    if (((newPoints[i].x >= matrixPoints[0].x) && (newPoints[i].x <= matrixPoints[2].x)
         && (newPoints[i].y >= matrixPoints[3].y) && (newPoints[i].y <= matrixPoints[1].y))
        || ((matrixPoints[i].x >= newPoints[0].x) && (matrixPoints[i].x <= newPoints[2].x)
            && (matrixPoints[i].y >= newPoints[3].y) && (matrixPoints[i].y <= newPoints[1].y)))
    {
      return true;
    }
  }
  return false;
}


void vertola::Matrix::addElement(const shape_pointer fig)
{
  if (laycount_ == 0)
  {
    array_pointer newList(new shape_pointer[1]);
    ++laycount_;
    ++laysize_;
    matrix_.swap(newList);
    matrix_[0] = fig;
  }
  else
  {
    bool added = false;
    for (size_t i = 0; !added; ++i)
    {
      for (size_t j = 0; j < laysize_; ++j)
      {
        if (!matrix_[i * laysize_ + j])
        {
          matrix_[i * laysize_ + j] = fig;
          added = true;
          break;
        }
        else
        {
          if (overlapping(i * laysize_ + j, fig))
          {
            break;
          }
        }
        if (j == (laysize_ - 1))
        {
          array_pointer newList(new shape_pointer[laycount_ * (laysize_ + 1)]);
          ++laysize_;
          for (size_t n = 0; n < laycount_; ++n)
          {
            for (size_t m = 0; m < laysize_ - 1; ++m)
            {
              newList[n * laysize_ + m] = matrix_[n * (laysize_ - 1) + m];
            }
            newList[(n + 1) * laysize_ - 1] = nullptr; 
          }
          newList[(i + 1) * laysize_ - 1] = fig;
          matrix_.swap(newList);
          added = true;
          break;
        }
      }
      if ((i == laycount_ - 1) && !added)
      {
        array_pointer newList(new shape_pointer[(laycount_ + 1) * laysize_]);
        ++laycount_;
        for (size_t n = 0; n < ((laycount_ - 1) * laysize_); ++n)
        {
          newList[n] = matrix_[n];
        }
        for (size_t n = ((laycount_ - 1) * laysize_); n < (laycount_ * laysize_); ++n)
        {
          newList[n] = nullptr;
        }
        newList[(laycount_ - 1) * laysize_] = fig;
        matrix_.swap(newList);
        added = true;
      }
    }
  }
}



size_t vertola::Matrix::getLayCount() const
{
  return laycount_;
}

size_t vertola::Matrix::getMaxLaySize() const
{
  return laysize_;
}

size_t vertola::Matrix::getLaySize(size_t num) const
{
  size_t lsz = 0;
  for (size_t i = num; i < (num * laysize_); ++i)
  {
    if (matrix_ != nullptr)
    {
      ++lsz;
    }
  }
  return lsz;
}

void vertola::Matrix::getInfo() const
{
  for(size_t i = 0;i < laycount_; ++i)
  {
    std::cout << i + 1 << "Layer" << std::endl;
    for(size_t j = 0;j < laysize_; ++j)
    {
      if (matrix_[i * laysize_ + j])
      {
        matrix_[i * laysize_ + j]->getInfo();
      }
    }
  }
}
