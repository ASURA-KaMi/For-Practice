#include <iostream>
#include <cstring>

#include "inp.hpp"
#include "out.hpp"

const size_t MIN_STRING_LENGTH = 24;
const size_t DEFAULT_STRING_LENGTH = 40;

int main(int argc, char* argv[])
{
  try
  {
    size_t string_length = DEFAULT_STRING_LENGTH;
    if(argc > 1)
    {
      if(argc != 3 || strcmp(argv[1], "--line-width") != 0)
      {
        throw std::invalid_argument("Invalid arguments");
      }
      else
      {
        string_length = atoi(argv[2]);
        if(string_length < MIN_STRING_LENGTH)
        {
          throw std::length_error("Invalid string length");
        }
      }
    }

    Input parser;
    parser.inputHandling();
    std::list<symbol_t> list(parser.begin(), parser.end());

    if(!checkConditions(list))
    {
      std::cerr << "Input error detected" << std::endl;
      return 1;
    }
    formatting(string_length, list);
  }
  catch(std::exception &error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
