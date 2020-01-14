#include <iostream>
#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

using unname = std::shared_ptr <vertola::Shape>;

int main()
{
  vertola::Rectangle testRect({40, 20, {100, 100}});
  vertola::Circle testCircle(20, {150, 150});
  unname rectptr = std::make_shared <vertola::Rectangle>(testRect);
  unname circptr = std::make_shared <vertola::Circle>(testCircle);
  vertola::CompositeShape Comp(rectptr);
  Comp.addShape(circptr);
  std::cout << "Composite Shape" << std::endl;
  Comp.getInfo();
  Comp.scale(2);
  std::cout << std::endl << "Scale factor 2" << std::endl;
  Comp.getInfo();
  Comp.deleteShape(2);
  std::cout << std::endl << "Deleting circle" << std::endl;
  Comp.getInfo();
  return 0;
}
