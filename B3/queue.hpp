#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <stdexcept>
#include <iostream>

enum ElementPriority
{
  LOW,
  NORMAL,
  HIGH
};

template<typename T>
class QueueWithPriority
{
public:
  QueueWithPriority() = default;

  void putElementToQueue(const T& element, ElementPriority priority);

  T getElementFromQueue();

  void accelerate();

  size_t getSize() const;

  bool isEmpty() const;

private:
  std::list<std::pair<T, ElementPriority>> queue_;
};

template<typename T>
void QueueWithPriority<T>::putElementToQueue(const T& element, ElementPriority priority)
{
  queue_.push_back(std::make_pair(element, priority));
};

template<typename T>
T QueueWithPriority<T>::getElementFromQueue()
{
  if (queue_.empty())
  {
    throw std::invalid_argument("Queue is empty");
  }
  else
  {
    auto forReturn = queue_.begin();

    for (auto i = queue_.begin(); i != queue_.end(); i++)
    {
      if (i->second > forReturn->second)
      {
        forReturn = i;
      }
      if (forReturn->second == HIGH)
      {
        break;
      }
    }

    T temp = forReturn->first;
    queue_.erase(forReturn);
    return temp;
  }
}

template<typename T>
size_t QueueWithPriority<T>::getSize() const
{
  return queue_.size();
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  return queue_.empty();
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  for (auto i = queue_.begin(); i != queue_.end(); i++)
  {
    if (i->second == LOW)
    {
      i->second = HIGH;
      queue_.splice(queue_.end(),queue_,i);
      i = queue_.begin();
    }
  }
}

#endif // QUEUE_HPP
