#include "detail.hpp"

void thirdEx()
{
  std::vector<int> vec1;
  int cap = 0;
  int value = 0;
  while (std::cin) 
  {
    if (std::cin >> value)
    {
      if (value % 3 == 0)
      {
        cap++;
      }
      if (value == 0)
      {
        break;
      }
      vec1.push_back(value);
    }
    else
    {
      if (std::cin.eof())
      {
        break;
      }
      else
      {
        throw std::invalid_argument ("Input error");
      }
    }
  }

  if ((!std::cin.eof()) && (value != 0)) 
  {
    throw std::invalid_argument ("Input error");
  }

  if (value != 0)
  {
    throw std::invalid_argument ("Missing zero");
  }
  
  if (vec1.empty())
  {
    return;
  }
 
  switch (vec1.back()) 
  {
    case 1:
    {
      std::vector<int>::iterator iterStart = vec1.begin();
      while (iterStart != vec1.end())
      {
        if (*iterStart % 2 == 0)
        {
          iterStart = vec1.erase(iterStart);
        }
        else 
        {
          ++iterStart;
        }
      }
      break;
    }
    case 2:
    {
      vec1.reserve(vec1.capacity() + 3 * cap);
      std::vector<int>::iterator iterStart = vec1.begin();
      while (iterStart != vec1.end())
      {
        if (*iterStart % 3 == 0)
        {
          iterStart = vec1.insert(iterStart + 1, 3, 1) + 2;
        }
        ++iterStart;
      }
      break;
    }
    default:
    {
    }
  }
  
  for(std::vector<int>::iterator i = vec1.begin(); i < vec1.end(); ++i)
  {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}
