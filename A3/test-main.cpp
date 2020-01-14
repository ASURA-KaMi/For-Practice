#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>

using unname = std::shared_ptr <vertola::Shape>;
using uniqueunname = std::unique_ptr<unname[]>;

const double ACCURACY = 0.00001;
const double scfactor = 2.7;

BOOST_AUTO_TEST_SUITE(TestRectangle)

  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    vertola::Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    vertola::rectangle_t frame = rect.getFrameRect();
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
    vertola::Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    vertola::rectangle_t frame = rect.getFrameRect();
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
    vertola::Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } }); 
    double area = rect.getArea();
    //scale
    rect.scale(scfactor);
    //Check
    BOOST_CHECK_CLOSE(area * scfactor * scfactor, rect.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(vertola::Rectangle({ -20.0, 40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(vertola::Rectangle({ 20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
    BOOST_CHECK_THROW(vertola::Rectangle({ -20.0, -40.0, { 30.0, 54.0 } }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidscaleFactor)
  {
    vertola::Rectangle rect({ 20.0, 40.0, { 30.0, 54.0 } });

    BOOST_CHECK_THROW(rect.scale(-scfactor), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)
  
  BOOST_AUTO_TEST_CASE(MoveToPoint) 
  {
    vertola::Circle circle(30.0, { -15.0, 36.0 }); 
    vertola::rectangle_t frame = circle.getFrameRect();
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
    vertola::Circle circle(30.0, { -15.0, 36.0 }); 
    vertola::rectangle_t frame = circle.getFrameRect();
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
    vertola::Circle circle(30.0, { -15.0, 36.0 }); 
    double area = circle.getArea();
    //scale
    circle.scale(scfactor);
    //Check
    BOOST_CHECK_CLOSE(area * scfactor * scfactor, circle.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameters)
  {
    BOOST_CHECK_THROW(vertola::Circle(-30.0, { -15.0, 36.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidscaleFactor)
  {
    vertola::Circle circle(30.0, { -15.0, 36.0 }); 

    BOOST_CHECK_THROW(circle.scale(-scfactor), std::invalid_argument);
  }
  
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MoveOperatorTest)
  {
    unname rect_1 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({1, 1, { 0,0 }}));
    unname rect_2 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({2, 2, { 0,0 }}));
    vertola::CompositeShape Comp_1(rect_1);
    vertola::CompositeShape Comp_2(rect_2);
    vertola::rectangle_t frame = Comp_1.getFrameRect();
    Comp_2 = std::move(Comp_1);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, ACCURACY);
  }


  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    unname rect_1 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({1, 1, { 0,0 }}));
    unname rect_2 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({2, 2, { 0,0 }}));
    vertola::CompositeShape Comp_1(rect_1);
    vertola::rectangle_t frame = Comp_1.getFrameRect();
    vertola::CompositeShape Comp_2(std::move(Comp_1));
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    unname rect_1 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({1, 1, { 0,0 }}));
    unname rect_2 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({2, 2, { 0,0 }}));
    vertola::CompositeShape Comp_1(rect_1);
    vertola::CompositeShape Comp_2(Comp_1);
    vertola::rectangle_t frame = Comp_1.getFrameRect();
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().width, frame.width, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().height, frame.height, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.x, frame.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE_FRACTION(Comp_2.getFrameRect().pos.y, frame.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(CorrectCopyOperator)
  {
    unname rect_1 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({1,1, { 0,0 }}));
    unname rect_2 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({2, 2, { 0,0 }}));
    unname rect_3 = std::make_shared<vertola::Rectangle>(vertola::Rectangle({3, 3, { 0,0 }}));
    vertola::CompositeShape Comp_1(rect_1);
    Comp_1.addShape(rect_2);
    vertola::CompositeShape Comp_2(rect_2);
    Comp_2.addShape(rect_3);
    Comp_1 = Comp_2;
    BOOST_CHECK_CLOSE(Comp_2.getArea(), Comp_1.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    unname rect = std::make_shared<vertola::Rectangle>(vertola::Rectangle({4, 4, { 0,0 }}));
    unname circ = std::make_shared<vertola::Circle>(vertola::Circle(2, { 0,0 }));
    vertola::CompositeShape Comp(rect);
    Comp.addShape(circ);
    double height = Comp.getFrameRect().height;
    double width = Comp.getFrameRect().width;
    double area = Comp.getArea();
    Comp.move(2, 2);
    BOOST_CHECK_CLOSE(height, Comp.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(width, Comp.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(area, Comp.getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.x, 2.0, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.y, 2.0, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(MoveCompositeShapeTest)
  {
    unname rect = std::make_shared<vertola::Rectangle>(vertola::Rectangle({4, 4, { 0,0 }}));
    unname circ = std::make_shared<vertola::Circle>(vertola::Circle(2, { 0,0 }));
    vertola::CompositeShape Comp(rect);
    Comp.addShape(circ);
    double height = Comp.getFrameRect().height;
    double width = Comp.getFrameRect().width;
    double area = Comp.getArea();
    Comp.move({ 2, 2 });
    BOOST_CHECK_CLOSE(height, Comp.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(width, Comp.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(area, Comp.getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.x, 2.0, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().pos.y, 2.0, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(CorrectScale)
  {
    vertola::Rectangle rect({4, 4, { 2,2 }});
    vertola::Circle circ(2, { -2,-2 });
    unname rectptr = std::make_shared<vertola::Rectangle>(rect);
    unname circptr = std::make_shared<vertola::Circle>(circ);
    vertola::CompositeShape Comp(rectptr);
    Comp.addShape(circptr);
    vertola::rectangle_t frame = Comp.getFrameRect();
    Comp.scale(2);
    BOOST_CHECK_CLOSE(4.0*(rect.getArea()+circ.getArea()), Comp.getArea(), ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().height, frame.height * 2, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getFrameRect().width, frame.width * 2, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().pos.x, 4.0, ACCURACY); //Rectangle
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().pos.y, 4.0, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().width, 8.0, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getShape(0)->getFrameRect().height, 8.0, ACCURACY);
    BOOST_CHECK_CLOSE(Comp.getShape(1)->getFrameRect().pos.x, -4.0, ACCURACY); //Circle
    BOOST_CHECK_CLOSE(Comp.getShape(1)->getFrameRect().pos.y, -4.0, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(IncorrectScaleTest)
  {
    unname rect = std::make_shared<vertola::Rectangle>(vertola::Rectangle({4, 4, { 0,0 }}));
    unname circ = std::make_shared<vertola::Circle>(vertola::Circle(2, { 0,0 }));
    vertola::CompositeShape Comp(rect);
    Comp.addShape(circ);
    BOOST_CHECK_THROW(Comp.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
