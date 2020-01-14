#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <string>

struct symbol_t
{
  std::string value;
  enum type_t
  {
    WORD,
    NUMBER,
    PUNCTUATION,
    DASH, 
    SPACE_SYMBOLS
  };
  
  type_t type;
};

#endif // SYMBOLS_HPP
