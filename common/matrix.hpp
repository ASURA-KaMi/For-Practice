#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace vertola
{
  using shape_pointer = std::shared_ptr <vertola::Shape>;
  using array_pointer = std::unique_ptr<shape_pointer[]>;
  
  class Matrix

  {
  public:
    Matrix(const shape_pointer &fig);
    Matrix(const Matrix &copy_m);
    Matrix(Matrix && move_m);
    Matrix(const vertola::CompositeShape & composite_shape);

    ~Matrix();

    Matrix & operator=(const Matrix & copy_m);
    Matrix & operator=(Matrix && move_m);
    bool operator == (const Matrix & copy_m) const;
    bool operator != (const Matrix & copy_m) const;
    array_pointer operator[](size_t laynum) const;
    
    void addElement(const shape_pointer fig);
    void getInfo() const;
    size_t getLayCount() const;
    size_t getMaxLaySize() const;
    size_t getLaySize(size_t num) const;
  private:
    array_pointer matrix_;
    size_t laycount_;
    size_t laysize_;
    bool overlapping(size_t laynum, const  shape_pointer fig) const;
  };
} 
#endif
