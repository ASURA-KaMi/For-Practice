#ifndef OUT_HPP
#define OUT_HPP

#include <list>
#include <iostream>

#include "symbols.hpp"

void printLine(const std::list<symbol_t> &line);
void formatting(const unsigned int lineWidth, const std::list<symbol_t> &list);

int reorganize(std::list<symbol_t> &line);
bool checkConditions(const std::list<symbol_t> &list);

#endif // OUT_HPP
