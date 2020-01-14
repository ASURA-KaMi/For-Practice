#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace vertola
{
  class CompositeShape:
    public Shape
  {
  public:
    CompositeShape(const std::shared_ptr <Shape> shape);
    CompositeShape(const CompositeShape & shapeCopy);
    CompositeShape(CompositeShape && shapeMove);

    CompositeShape & operator=(const CompositeShape & shapeCopy);
    CompositeShape & operator=(CompositeShape && shapeMove);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t & newPos) override;
    void scale(const double scf) override;
    void rotate(const double deg) override;
    double getAngle() const override;
    void getInfo() const override;
    void addShape(std::shared_ptr <Shape> shape);
    std::shared_ptr <Shape> getShape(size_t const index) const;
    void deleteShape(const size_t index);
    void clear();
    size_t getQuantity() const;
  private:
    std::unique_ptr <std::shared_ptr <Shape>[]> arr_;
    size_t quant_;
    double angle_;
  };
}
#endif
