#include "detail.hpp"

int main(int argc, char **argv)
{
  try
  {    
    if(argc >= 2)
    {
      switch(std::stoi(argv[1]))
      { 
        case 1:
          if(argc == 3)
          {
            firstEx(argv[2]);
          }
          else
          {
            throw std::invalid_argument("Invalid argument");
          }
          break;

        case 2:
          if(argc == 3)
          {
            secondEx(argv[2]);
          }
          else
          {
            throw std::invalid_argument("Invalid argument");
          }
          break;

        case 3:
          if(argc == 2)
          {
            thirdEx();
          }
          else
          {
            throw std::invalid_argument("Invalid argument");
          }
          break;

        case 4:
          if (argc == 4)
          {
            fourthEx(argv[2], argv[3]);
          }
          else
          {
            throw std::invalid_argument("Invalid argument");
          }
          break;

        default:
          std::cerr << "Invalid argument" << std::endl;
          return 1;
      }
      return 0;
    }
    else
    {
      std::cerr << "Invalid argument" << std::endl;
      return 1; 
    }
  }
  catch (std::exception &err)
  {
    std::cerr << err.what() << std::endl;
    return 2;
  }
  return 0;
}
