#include "detail.hpp"

void firstEx (const char *direction)
{  
  labNameSpace::sortType comparing = getDirection(direction);
  std::vector<int> vec1;
  int i = 0;

  while (std::cin >> i)
  {
    vec1.push_back(i);
  }
  
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument ("Input error");
  }
  
  if(!vec1.empty())
  {
    std::vector<int> vec2 = vec1;
    std::vector<int> list1 = vec1;

    labNameSpace::sort<labNameSpace::SortIndex>(vec1, comparing);
    labNameSpace::sort<labNameSpace::SortAt>(vec2, comparing);
    labNameSpace::sort<labNameSpace::SortIterator>(list1, comparing);

    labNameSpace::print(vec1);
    labNameSpace::print(vec2);
    labNameSpace::print(list1);
  }
}
