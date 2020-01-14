#include <list>

#include "out.hpp"

void printLine(const std::list<symbol_t> &line)
{
  for(auto i = line.begin(); i != line.end(); i++)
  {
    std::cout << (*i).value;
  }
  std::cout << std::endl;
}

int reorganize(std::list<symbol_t> &line)
{
  std::size_t width = 0;
  std::list<symbol_t> newLine;
  while(!line.empty())
  {
    newLine.push_front(line.back());
    width += line.back().value.size();
    line.pop_back();
    if(newLine.front().type == symbol_t::WORD || newLine.front().type == symbol_t::NUMBER)
    {
      break;
    }
  }
  printLine(line);
  line = newLine;
  return width;
}

void formatting(const unsigned int lineWidth, const std::list<symbol_t> &list)
{
  std::size_t currentWidth = 0;
  std::list<symbol_t> line;
  for(auto it = list.begin(); it != list.end(); it++)
  {
    switch((*it).type)
    {
    case symbol_t::PUNCTUATION:
      if(currentWidth + 1 > lineWidth)
      {
        currentWidth = reorganize(line);
      }
      line.push_back(*it);
      currentWidth += (*it).value.size();
      break;
    case symbol_t::DASH:
      if(currentWidth + 4 > lineWidth)
      {
        currentWidth = reorganize(line);
      }
      line.push_back(symbol_t{ " ", symbol_t::SPACE_SYMBOLS });
      line.push_back(*it);
      currentWidth += (*it).value.size() + 1;
      break;
    case symbol_t::WORD:
    case symbol_t::NUMBER:
      if(currentWidth + (*it).value.size() + 1 > lineWidth)
      {
        printLine(line);
        line.clear();
        currentWidth = 0;
      }
      else if(!line.empty())
      {
        line.push_back(symbol_t{ " ", symbol_t::SPACE_SYMBOLS });
        currentWidth++;
      }
      line.push_back(*it);
      currentWidth += (*it).value.size();
      break;
    case symbol_t::SPACE_SYMBOLS:
      break;
    }

  }
  if(!line.empty())
  {
    printLine(line);
  }
}

bool checkConditions(const std::list<symbol_t> &list)
{
  if(!list.empty() && (list.front().type != symbol_t::WORD) && (list.front().type != symbol_t::NUMBER))
  {
    return false;
  }
  for(auto it = list.begin(); it != list.end(); ++it)
  {
    switch((*it).type)
    {
    case symbol_t::WORD:
    case symbol_t::NUMBER:
      if((*it).value.size() > 20)
      {
        return false;
      }
      break;
    case symbol_t::DASH:
      if((*it).value.size() != 3)
      {
        return false;
      }
      if(it != list.begin())
      {
        const symbol_t &prev = *std::prev(it);
        if((prev.type == symbol_t::DASH) || ((prev.type == symbol_t::PUNCTUATION) && (prev.value != ",")))
        {
          return false;
        }
      }
      break;
    case symbol_t::PUNCTUATION:
      if(it != list.begin())
      {
        const symbol_t &prev = *std::prev(it);
        if((prev.type == symbol_t::DASH) || (prev.type == symbol_t::PUNCTUATION))
        {
          return false;
        }
      }
      break;
    case symbol_t::SPACE_SYMBOLS:
      break;
    }
  }
  return true;
}
