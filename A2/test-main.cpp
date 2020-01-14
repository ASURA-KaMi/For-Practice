#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.00001;
const double scfactor = 2.7;

using namespace vertola;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Move to point
    rect.move({ 60.8, 71.0 });
    //Check
    BOOST_CHECK_CLOSE(frame.width, rect.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, rect.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    rectangle_t frame = rect.getFrameRect();
    double area = rect.getArea();
    //Relative move
    rect.move(30.1, -5.2);
    //Check
    BOOST_CHECK_CLOSE(frame.width, rect.getFrameRect().width,ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, rect.getFrameRect().height,ACCURACY);
    BOOST_CHECK_CLOSE(area, rect.getArea(), ACCURACY);
  }
  
  BOOST_AUTO_TEST_CASE(scale)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    double area = rect.getArea();
    //scale
    rect.scale(scfactor);
    //Check
    BOOST_CHECK_CLOSE(area * scfactor * scfactor, rect.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(Rectangle({ -20.0, 40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({ 20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({ -20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidscaleFactor)
  {
    Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } });

    BOOST_CHECK_THROW(rect.scale(-scfactor), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move({ -92.2, 68.0 });
    //Check
    BOOST_CHECK_CLOSE(frame.width, circle.getFrameRect().width,ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height,ACCURACY);
    BOOST_CHECK_CLOSE(area, circle.getArea(),ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove) 
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    //Move to point
    circle.move(-64.3, 15.2);
    //Check
    BOOST_CHECK_CLOSE(frame.width, circle.getFrameRect().width,ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, circle.getFrameRect().height,ACCURACY);
    BOOST_CHECK_CLOSE(area, circle.getArea(),ACCURACY);
  }
  
  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle(30.0, { -15.0, 36.0 }); 
    double area = circle.getArea();
    //scale
    circle.scale(scfactor);
    //Check
    BOOST_CHECK_CLOSE(area * scfactor * scfactor, circle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(Circle(-30.0, { -15.0, 36.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidscaleFactor)
  {
    Circle circle(30.0, { -15.0, 36.0 }); 

    BOOST_CHECK_THROW(circle.scale(-scfactor), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

