#ifndef SEARCH_H
#define SEARCH_H

#include "hnetwork.h"

class DecentralizedSearch {
 public:
  int search(HNetwork& N, int s, int t, double p);

 protected:
  virtual int next_hop(HNetwork& N, int s, int t) = 0;
};

class SoftmaxDecentralizedSearch : public DecentralizedSearch {
 public:
  SoftmaxDecentralizedSearch(double alpha);

 protected:
  double alpha;
  int next_hop(HNetwork& N, int s, int t);
};

class PerfectDecentralizedSearch : public DecentralizedSearch {
 protected:
  int next_hop(HNetwork& N, int s, int t);
};

#endif
