#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "queue.hpp"

void add(std::stringstream &inputStream, QueueWithPriority<std::string> &queue);
void get(QueueWithPriority<std::string> &queue);

#endif // TOOLS_HPP
