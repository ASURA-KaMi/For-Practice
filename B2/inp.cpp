#include "inp.hpp"

Input::Input() :
  read_(std::cin)
{}

std::list<symbol_t>::iterator Input::begin()
{
  return text_.begin();
}

std::list<symbol_t>::iterator Input::end()
{
  return text_.end();
}

void Input::inputHandling()
{
  while(read_)
  {
    symbol_ = read_.get();
    while(isspace(symbol_))
    {
      symbol_ = read_.get();
    }

    if(isalpha(symbol_))
    {
      read_.unget();
      readWord();
    }
    else if(symbol_ == '-')
    {
      if(read_.peek() == '-')
      {
        read_.unget();
        readDash();
      }
      else
      {
        read_.unget();
        readNumber();
      }
    }
    else if(symbol_ == '+' || isdigit(symbol_))
    {
      read_.unget();
      readNumber();
    }
    else if(ispunct(symbol_))
    {
      symbol_t phrase{ "", symbol_t::PUNCTUATION };
      phrase.value.push_back(symbol_);
      text_.push_back(phrase);
    }
  }
}

void Input::readWord()
{
  symbol_t phrase{ "", symbol_t::WORD };
  do
  {
    symbol_ = read_.get();
    phrase.value.push_back(symbol_);
    if(symbol_ == '-' && read_.peek() == '-')
    {
      phrase.value.pop_back();
      read_.unget();
      break;
    }
  }
  while(isalpha(read_.peek()) || (read_.peek() == '-'));

  text_.push_back(phrase);
}

void Input::readNumber()
{
  symbol_t phrase{ "", symbol_t::NUMBER };

  char decimalPoint = std::use_facet<std::numpunct<char>>(std::locale()).decimal_point();

  bool decimalPointRead = false;
  do
  {
    symbol_ = read_.get();
    if(symbol_ == decimalPoint)
    {
      if(decimalPointRead)
      {
        read_.unget();
        break;
      }
      decimalPointRead = true;
    }
    phrase.value.push_back(symbol_);
  }
  while(isdigit(read_.peek()) || read_.peek() == decimalPoint);

  text_.push_back(phrase);
}

void Input::readDash()
{
  symbol_t phrase{ "", symbol_t::DASH };
  while(read_.peek() == '-')
  {
    symbol_ = read_.get();
    phrase.value.push_back(symbol_);
  }

  text_.push_back(phrase);
}
