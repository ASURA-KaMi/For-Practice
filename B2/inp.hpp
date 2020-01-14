#ifndef INP_HPP
#define INP_HPP

#include <list>
#include <iostream>
#include <memory>

#include "symbols.hpp"

class Input
{
  public:
    Input();
    void inputHandling();

    std::list<symbol_t>::iterator begin();
    std::list<symbol_t>::iterator end();

  private:
    std::istream & read_;
    std::list<symbol_t> text_;
    char symbol_;

    void readWord();
    void readNumber();
    void readDash();
};

#endif // INP_HPP
