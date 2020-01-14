#include <fstream>
#include <memory>

#include "detail.hpp"

void secondEx(const char *filename)
{
  const int const_size = 4096;
  int size = 0;
  
  std::ifstream file1(filename);
  if (!file1)
  {
    throw std::invalid_argument ("Incorrect file");
  }
  
  int lenght = const_size;
  std::unique_ptr<char[], decltype(&free)> arr (static_cast<char *>(malloc(lenght)), &free);
  while (file1) 
  {
    file1.read(arr.get() + size, const_size);
    size += file1.gcount();
    if (file1) 
    {
      lenght += size;
      std::unique_ptr<char[], decltype(&free)>
          new_arr (static_cast<char *>(realloc(arr.get(), lenght)), &std::free);
      if (new_arr) 
      {
        arr.release();
        std::swap(arr, new_arr);
      } else 
      {
        throw std::bad_alloc();
      }
    }
  }

  std::vector<char> vec (&arr[0], &arr[size]);
  std::cout.write(&vec[0], vec.size());
}
