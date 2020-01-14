#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using vertola::shape_pointer;

/*int main()
{

  vertola::Circle testcircle({10.01, { 5.32, 27.63 } });
  vertola::Rectangle testrectangle({7.13, 4.82 , { 25.04, 6.12 } });
  shape_pointer circlePtr = std::make_shared<vertola::Circle >(testcircle);
  shape_pointer rectanglePtr = std::make_shared<vertola::Rectangle >(testrectangle);


  vertola::Circle testcircle1({1.0 , { -2.0, -2.0 } });
  vertola::Rectangle testrectangle1({2.0, 2.0,  { 2.0, 2.0 }});
  shape_pointer circlePtr1 = std::make_shared<vertola:: Circle >(testcircle);
  shape_pointer rectanglePtr1 = std::make_shared<vertola:: Rectangle >(testrectangle);
  vertola::CompositeShape compositeShape;
  compositeShape.addShape(circlePtr1);
  testcircle.getInfo();
  testrectangle.getInfo();

  compositeShape.addShape(rectanglePtr1);
  compositeShape.rotate(45);
  compositeShape.scale(2.0);
  compositeShape.addShape(rectanglePtr);

  vertola::Circle testcircleM({ 2.0 , { -2.0, -2.0 }});
  vertola::Rectangle testrectangleM1({2.0, 2.0 , { -2.0, 0.0 } });
  vertola::Rectangle testrectangleM2({ 6.0, 3.0, { 1.0, 1.0 } });
  vertola::Rectangle testrectangleM3({ 2.0, 4.0 ,{ 3.0, 1.0 } });
  vertola::Rectangle testrectangleM4({4.0, 4.0,  { 3.0, 3.0 } });
  compositeShape.getInfo();
  shape_pointer comp = std::make_shared< vertola::CompositeShape >(compositeShape);
  shape_pointer testcirclePtrM = std::make_shared<vertola:: Circle >(testcircleM);
  shape_pointer testrectanglePtrM1 = std::make_shared<vertola:: Rectangle >(testrectangleM1);
  shape_pointer testrectanglePtrM2 = std::make_shared<vertola:: Rectangle >(testrectangleM2);
  shape_pointer testrectanglePtrM3 = std::make_shared<vertola:: Rectangle >(testrectangleM3);
  shape_pointer testrectanglePtrM4 = std::make_shared<vertola:: Rectangle >(testrectangleM4);

  vertola::Matrix matrix(testcirclePtrM);
  matrix.addElement(comp);
  matrix.addElement(testrectanglePtrM1);
  matrix.addElement(testrectanglePtrM2);
  matrix.addElement(testrectanglePtrM3);
  matrix.addElement(testrectanglePtrM4);

  std::cout << "Matrix:" << std::endl;
  matrix.getInfo();

  return 0;
}
*/
using namespace vertola;

void printShapeInfo(const Shape & shape)
{
  std::cout << "Area = " << shape.getArea() << std::endl;
  std::cout << "Angle = " << shape.getAngle() << std::endl;
  const rectangle_t frame = shape.getFrameRect();
  std::cout << "FrameRectangle: " << std::endl;
  std::cout << "  Center: (" << frame.pos.x << ", " << frame.pos.y << ")" << std::endl;
  std::cout << "  Width = " << frame.width << std::endl;
  std::cout << "  Height = " << frame.height << std::endl << std::endl;
}

int main()
{
  try
  {
    std::cout << "Creating the Circle(3.33, {60, 60})..." << std::endl;
    Circle crcl(3.33, {60, 60});
    std::cout << "Circle info: " << std::endl;
    printShapeInfo(crcl);

    std::cout << "Rotating the Circle(50 degrees)..." << std::endl;
    crcl.rotate(50);
    std::cout << "Circle info: " << std::endl;
    printShapeInfo(crcl);
  
    std::cout << "Creating the Rectangle(8.25, 3.14, {25.0, 25.0})..." << std::endl;
    Rectangle rctngl({8.25, 3.14, {25.0, 25.0}});
    std::cout << "Rectangle info: " << std::endl;
    printShapeInfo(rctngl);

    std::cout << "Rotating the Rectangle(-198 degrees)..." << std::endl;
    rctngl.rotate(-198);
    std::cout << "Rectangle info: " << std::endl;
    printShapeInfo(rctngl);

    std::cout << "Creating the CompositeShape(Circle)..." << std::endl;
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle>(crcl);
    CompositeShape compShp(crclPtr);
    std::cout << "CompositeShape info: " << std::endl;
    printShapeInfo(compShp);
  
    std::cout << "Adding the Rectangle to the CompositeShape..." << std::endl;
    std::shared_ptr <Shape> rctnglPtr = std::make_shared <Rectangle>(rctngl);
    compShp.addShape(rctnglPtr);
    std::cout << "CompositeShape info: " << std::endl;
    printShapeInfo(compShp);

    std::cout << "Rotating the CompositeShape(3333 degrees)..." << std::endl;
    compShp.rotate(3333);
    std::cout << "CompositeShape info: " << std::endl;
    printShapeInfo(compShp);
    std::cout << "move in (30,40)" << std::endl;
    compShp.move({30,40});
    std::cout << "CompositeShape info: " << std::endl;
    printShapeInfo(compShp);
  }
  catch(std::invalid_argument & ia)
  {
    std::cerr << ia.what() << std::endl;
    return 1;
  }
  catch(std::out_of_range & oor)
  {
    std::cerr << oor.what() << std::endl;
    return 2;
  }
  return 0;
}
