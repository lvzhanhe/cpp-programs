#ifndef __KNAPSACK
#define __KNAPSACK

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include "package.h"

class Knapsack{
private:
  Package *data_ = nullptr;
  long weight_limit_ = 0;
  long capacity_ = 10;
  long size_ = 0;
  void swap(Knapsack&);
  
public:
  Knapsack() = default;
  Knapsack(size_t wlimit);
  Knapsack(size_t wlimit, size_t cap);  
  Knapsack(const Knapsack&);
  ~Knapsack();
  Knapsack& operator=(const Knapsack);
  

  long priority() const;
  long capacity() const;
  long size() const;
  long weight_limit() const;
  bool empty() const;
  long weight() const;
  bool add(const Package&);  
  friend ostream& operator<<(ostream&, Knapsack &);
  friend void solve_KS(string, Knapsack&);
};

#endif