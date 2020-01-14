#include <iostream>
#include <list>
#include <stdexcept>

#include "queue.hpp"
#include "tasks.hpp"

void secondTask()
{
  std::list<int> list;

  size_t number;
  while (std::cin >> number)
  {
    if (number < 1 || number > 20)
    {
      throw std::invalid_argument("Invalid number");
    }
    list.push_back(number);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Invalid input");
  }

  if (list.size() > 20)
  {
    throw std::invalid_argument("Too many numbers");
  }

  auto i = list.begin();

  if (list.size() == 1)
  {
    std::cout << *i;
  }
  else
  {
    auto j = --list.end();
    while (i != j)
    {
      std::cout << *i << " " << *j << " ";
      i++;
      if (i == j)
      {
        break;
      }
      j--;
      if (i == j)
      {
        std::cout << *i;
        break;
      }
    }
  }

  std::cout << std::endl;
}
