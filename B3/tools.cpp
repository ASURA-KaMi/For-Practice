#include <iostream>
#include <sstream>

#include "tools.hpp"

void add(std::stringstream &inputStream, QueueWithPriority<std::string> &queue)
{
  std::string priority;
  inputStream >> priority;

  inputStream.ignore();
  std::string data;
  std::getline(inputStream, data);

  if (data.empty())
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
  }
  else if (priority == "high")
  {
    queue.putElementToQueue(data, HIGH);
  }
  else if (priority == "normal")
  {
    queue.putElementToQueue(data, NORMAL);
  }
  else if (priority == "low")
  {
    queue.putElementToQueue(data, LOW);
  }
  else
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
  }
}

void get(QueueWithPriority<std::string> &queue)
{
  if (queue.isEmpty())
  {
    std::cout << "<EMPTY>" << std::endl;
  }
  else
  {
    std::cout << queue.getElementFromQueue() << std::endl;
  }
}
