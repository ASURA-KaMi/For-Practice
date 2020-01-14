#include <iostream>
#include <sstream>
#include <string>

#include "queue.hpp"
#include "tasks.hpp"

void firstTask()
{
  QueueWithPriority<std::string> queue;

  std::stringstream stream;
  std::string line;
  while (std::getline(std::cin, line))
  {
    stream.clear();
    stream << line;
    std::string command;
    stream >> command;
    if (command == "add")
    {
      add(stream, queue);
    }
    else if (command == "get" && stream.eof())
    {
      get(queue);
    }
    else if (command == "accelerate")
    {
      queue.accelerate();
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
}
