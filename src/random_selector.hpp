#ifndef RANDOM__SELECTOR__INC
#define RANDOM__SELECTOR__INC 1

#include<list>

#include "coelacanth_types.hpp"

template<typename T>
T random_selector(std::list<T> const &v)
{
//  LOG(INFO) << "ALAS, POOR YORICK I KNEW HIM WELL";
  auto it = v.cbegin();
  int random = rand() % v.size();
  std::advance(it, random);
  return *it;
}

#endif
