#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <functional>

void firstEx(const char *direction);
void secondEx(const char *filename);
void thirdEx();
void fourthEx(const char *direction, const char *size);

namespace labNameSpace
{
  template<typename T>
  struct SortAt
  {
    typedef std::size_t indexType;
    static typename T::value_type& getCollection(T&collection, size_t i)
    {
      return collection.at(i);
    }
    static size_t getStart(const T&)
    {
      return 0;
    }
    static size_t getEnd(const T&collection)
    {
      return collection.size();
    }
  };
  
  template<typename T>
  struct SortIndex
  {
    typedef std::size_t indexType;
    static typename T::value_type& getCollection(T&collection, size_t i)
    {
      return collection[i];
    }
    static size_t getStart(const T&)
    {
      return 0;
    }
    static size_t getEnd(const T&collection)
    {
      return collection.size();
    }
  };

  template<typename T>
  struct SortIterator
  {
    typedef typename T::iterator indexType;
    static typename T::value_type& getCollection(T&, typename T::iterator &i)
    {
      return *i;
    }
    static typename T::iterator getStart(T&collection)
    {
      return collection.begin();
    }
    static typename T::iterator getEnd(T&collection)
    {
      return collection.end();
    }
  };

  template<typename T>
  void print(T &vec)
  {
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }
  
  enum sortType { ascending, descending };

  template<template<typename T> class AccessSort, typename T>
  void sort(T&container, sortType direction)
  {
    std::function<bool(typename T::value_type, typename T::value_type)> comparing;
    if(direction == ascending)
    {
      comparing = std::greater<typename T::value_type>();
    }
    else
    {
      comparing = std::less<typename T::value_type>();
    }

    for(typename AccessSort<T>::indexType i = AccessSort<T>::getStart(container); i != AccessSort<T>::getEnd(container); i++)
    {
      for(typename AccessSort<T>::indexType j = i; j != AccessSort<T>::getEnd(container); j++)
      {
        if(comparing(AccessSort<T>::getCollection(container, i), AccessSort<T>::getCollection(container, j)))
        {
          std::swap(AccessSort<T>::getCollection(container, i), AccessSort<T>::getCollection(container, j));
        }
      }
    }
  }
}

labNameSpace::sortType getDirection(const std::string &param);

#endif
