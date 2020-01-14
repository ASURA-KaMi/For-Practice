#include "detail.hpp"

labNameSpace::sortType getDirection(const std::string &st)
{
  if(st == "ascending")
  {
    return labNameSpace::sortType::ascending;
  }
  else if (st == "descending")
  {
    return labNameSpace::sortType::descending;
  }
  else
  {
     throw std::invalid_argument ("Input error");
  }
}
