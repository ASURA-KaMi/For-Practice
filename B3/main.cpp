#include <iostream>
#include <string>

#include "tasks.hpp"

int main(int args, char *argv[])
{
  if (args != 2)
  {
    std::cerr << "Invalid parameter";
    return 1;
  }

  try
  {
    switch (std::stoi(argv[1]))
    {
    case 1:
      firstTask();
      break;
    
    case 2:
      secondTask();
      break;
    
    default:
      std::cerr << "Invalid parameter";
      return 1;
    }
  }

  catch (const std::exception & error)
  {
    std::cerr << error.what();
    return 1;
  }

  return 0;
}
