#include <iostream>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

using namespace std;

void viewInfo(const Shape & shp)
{
  cout << "Area = " << shp.getArea()<< endl;
  const rectangle_t frame = shp.getFrameRect();
  cout << "FrameRectangle: " << endl;
  cout << "Center: " << frame.pos.x <<", "<< frame.pos.y << endl
       << "Width = " << frame.width << endl
       << "Height = " << frame.height << endl;
}

int main()
{
  //Rectangle
  point_t pnt = { 20.0, 30.0 };
  rectangle_t initRect = { 20.0, 40.0, pnt };
  Rectangle rect = Rectangle(initRect);
  //Take info
  viewInfo(rect);
  //move
  pnt = { 50.0, 80.0 };
  rect.move(pnt);
  viewInfo(rect);
  //Circle
  pnt = { 40.0, 90.0 };
  Circle circ = Circle(20.0, pnt);
  //Area
  viewInfo(circ);
  //move
  circ.move(10.0, -30.0);
  cout << "Circle is moved" << endl;
  viewInfo(circ);
  return 0;
}
