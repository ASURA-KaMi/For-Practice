#include <random>

#include "detail.hpp"

void fillRandom(double * array, int quantity)
{
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<double> random(-1.0, 1.0);
  for (int i = 0; i < quantity; i++)
  {
    array[i] = random (generator);
  }
}

void fourthEx(const char *direction, const char *size_char)
{
  const int size = std::atoi(size_char); 
  if (size <= 0)
  {
    throw std::invalid_argument ("Invalid array size");
  }
  else
  {
    labNameSpace::sortType comparing = getDirection(direction);
    
    std::vector<double> vec1(size);
    fillRandom(&vec1[0], size);
    for(std::vector<double>::iterator i = vec1.begin(); i < vec1.end(); ++i)
    {
      std::cout << *i << " ";
    }
    std::cout << "\n";
    
    labNameSpace::sort<labNameSpace::SortIterator>(vec1, comparing);
    for(std::vector<double>::iterator i = vec1.begin(); i < vec1.end(); ++i)
    {
      std::cout << *i << " ";
    }
    std::cout << "\n";
  }
}
