#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"

using namespace vertola;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(Rotation_Tests)
  BOOST_AUTO_TEST_CASE(Circle_Rotate_Test)
  {
    Circle crcl(1, {2, 3});
    
    crcl.rotate(20);
    rectangle_t frame = crcl.getFrameRect();
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.x, 2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.y, 3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.width, 2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.height, 2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(crcl.getAngle(), 20, EPS);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_Rotate_Test)
  {
    Rectangle rctngl({5, 3, {10, 20}});
    
    rctngl.rotate(333);
    rectangle_t frame = rctngl.getFrameRect();
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.x, 10, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.y, 20, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.width, 5.817, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.height, 4.94297, EPS);
    BOOST_CHECK_CLOSE_FRACTION(rctngl.getAngle(), 333, EPS);
  }

  BOOST_AUTO_TEST_CASE(CompositeShape_Rotate_Test)
  {
    Circle crcl(1, {2, 3});
    Rectangle rctngl({5, 3, {10, 20}});
    CompositeShape compShp(std::make_shared <Circle>(crcl));
    compShp.addShape(std::make_shared <Rectangle>(rctngl));
    
    compShp.rotate(-45);
    rectangle_t frame = compShp.getFrameRect();
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.x, 5.48223, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.pos.y, 13.0178, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compShp.getShape(0)->getFrameRect().pos.x, 9.57843, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compShp.getShape(0)->getFrameRect().pos.y, 8.92157, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compShp.getShape(1)->getFrameRect().pos.x, 3.21447, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compShp.getShape(1)->getFrameRect().pos.y, 15.2855, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.width, 10.1924, EPS);
    BOOST_CHECK_CLOSE_FRACTION(frame.height, 10.1924, EPS);
    BOOST_CHECK_CLOSE_FRACTION(compShp.getAngle(), -45, EPS);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_Tests)
  BOOST_AUTO_TEST_CASE(Matrix_Constructor_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix(crclPtr);
    matrix.addElement(rctngl1Ptr);
    matrix.addElement(rctngl2Ptr);
    std::unique_ptr <std::shared_ptr <Shape>[]> layer1 = matrix[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> layer2 = matrix[1];
    BOOST_CHECK(layer1[0] == crclPtr);
    BOOST_CHECK(layer1[1] == rctngl2Ptr);
    BOOST_CHECK(layer2[0] == rctngl1Ptr);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.x, 7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 2, EPS);
    BOOST_CHECK_EQUAL(matrix.getLaySize(1), 1);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Constructor_Copy_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2(matrix1);
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix1Layer1 = matrix1[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix1Layer2 = matrix1[1];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix2Layer1 = matrix2[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix2Layer2 = matrix2[1];
    BOOST_CHECK(matrix1Layer1[0] == matrix2Layer1[0]);
    BOOST_CHECK(matrix1Layer1[1] == matrix2Layer1[1]);
    BOOST_CHECK(matrix1Layer2[0] == matrix2Layer2[0]);
    BOOST_CHECK(matrix1Layer2[1] == matrix2Layer2[1]);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Constructor_Move_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2(std::move(matrix1));
    std::unique_ptr <std::shared_ptr <Shape>[]> layer1 = matrix2[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> layer2 = matrix2[1];
    BOOST_CHECK(layer1[0] == crclPtr);
    BOOST_CHECK(layer1[1] == rctngl2Ptr);
    BOOST_CHECK(layer2[0] == rctngl1Ptr);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_EQUAL(matrix1.getLayCount(), 0);
    BOOST_CHECK_EQUAL(matrix1.getMaxLaySize(), 0);
    BOOST_CHECK_EQUAL(matrix2.getLayCount(), 2);
    BOOST_CHECK_EQUAL(matrix2.getMaxLaySize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Constructor_CompShape_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    CompositeShape compShp(crclPtr);
    compShp.addShape(rctngl1Ptr);
    compShp.addShape(rctngl2Ptr);
    
    Matrix matrix(compShp);
    std::unique_ptr <std::shared_ptr <Shape>[]> layer1 = matrix[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> layer2 = matrix[1];
    BOOST_CHECK(layer1[0] == crclPtr);
    BOOST_CHECK(layer1[1] == rctngl2Ptr);
    BOOST_CHECK(layer2[0] == rctngl1Ptr);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[0]->getFrameRect().pos.y, 0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.x, 7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer1[1]->getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.x, 1, EPS);
    BOOST_CHECK_CLOSE_FRACTION(layer2[0]->getFrameRect().pos.y, 2, EPS);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Operator_Copy_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2(rctngl2Ptr);
    
    matrix2 = matrix1;
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix1Layer1 = matrix1[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix1Layer2 = matrix1[1];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix2Layer1 = matrix2[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> matrix2Layer2 = matrix2[1];
    BOOST_CHECK(matrix1Layer1[0] == matrix2Layer1[0]);
    BOOST_CHECK(matrix1Layer1[1] == matrix2Layer1[1]);
    BOOST_CHECK(matrix1Layer2[0] == matrix2Layer2[0]);
    BOOST_CHECK(matrix1Layer2[1] == matrix2Layer2[1]);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Operator_Move_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2(rctngl2Ptr);
    
    matrix2 = std::move(matrix1);
    std::unique_ptr <std::shared_ptr <Shape>[]> layer1 = matrix2[0];
    std::unique_ptr <std::shared_ptr <Shape>[]> layer2 = matrix2[1];
    BOOST_CHECK(layer1[0] == crclPtr);
    BOOST_CHECK(layer1[1] == rctngl2Ptr);
    BOOST_CHECK(layer2[0] == rctngl1Ptr);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK_EQUAL(matrix1.getLayCount(), 0);
    BOOST_CHECK_EQUAL(matrix1.getMaxLaySize(), 0);
    BOOST_CHECK_EQUAL(matrix2.getLayCount(), 2);
    BOOST_CHECK_EQUAL(matrix2.getMaxLaySize(), 2);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Operator_Equality_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2 = matrix1;
    bool equal = (matrix1 == matrix2); 
    BOOST_CHECK(equal);
  }

  BOOST_AUTO_TEST_CASE(Matrix_Operator_Inequality_Test)
  {
    Circle crcl(2, {5,0});
    Rectangle rctngl1({4, 8, {1,2}});
    Rectangle rctngl2({4, 2, {7,7}});
    std::shared_ptr <Shape> crclPtr = std::make_shared <Circle> (crcl);
    std::shared_ptr <Shape> rctngl1Ptr = std::make_shared <Rectangle> (rctngl1);
    std::shared_ptr <Shape> rctngl2Ptr = std::make_shared <Rectangle> (rctngl2);
    
    Matrix matrix1(crclPtr);
    matrix1.addElement(rctngl1Ptr);
    matrix1.addElement(rctngl2Ptr);
    Matrix matrix2 = matrix1;
    bool inequal = (matrix1 != matrix2); 
    BOOST_CHECK(inequal);
  }
BOOST_AUTO_TEST_SUITE_END()
