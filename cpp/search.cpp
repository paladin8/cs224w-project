#include <cmath>
#include <cstdlib>
#include <iostream>

#include "dist_utils.h"
#include "hnetwork.h"
#include "search.h"

// returns the number of steps used in a decentralied search:
//   S    searcher (with next_hop function)
//   N    network (with dist function + graph G)
//   s    start node
//   t    goal node    
//   p    probability at each step of dropped message
int DecentralizedSearch::search(HNetwork& N, int s, int t, double p) {
  int steps = 0;
  
  while (s != t) {
    s = next_hop(N, s, t);
    steps = steps + 1;
    if (rand() < p) return INF;
  }
  
  return steps;
}

SoftmaxDecentralizedSearch::SoftmaxDecentralizedSearch(double alpha) {
  this->alpha = alpha;
}

// determines the next hop in a decentralied search:
//   N    network (with dist + graph)
//   s    start node
//   t    goal node
int SoftmaxDecentralizedSearch::next_hop(HNetwork& N, int s, int t) {
  map<int,double> D;
  vector<int> nbrs = N.get_neighbors(s);
  vector<int>::iterator v;
  for (v = nbrs.begin(); v < nbrs.end(); v++) {
    D[*v] = -1 * alpha * N.dist(*v, t);
  }
  
  softmax_dist(D);
  return random_item(D);
}


// determines the next hop in a decentralied search:
//   N    network (with dist + graph)
//   s    start node
//   t    goal node
int PerfectDecentralizedSearch::next_hop(HNetwork& N, int s, int t) {
  vector<int> min_v;
  int min_d = INF;
  
  vector<int> nbrs = N.get_neighbors(s);
  vector<int>::iterator v;
  
  for (v = nbrs.begin(); v < nbrs.end(); v++) {
    int d = N.dist(*v, t);
    if (d < min_d) {
      min_v.clear();
      min_v.push_back(*v);
      min_d = d;
    } else if (d == min_d) {
      min_v.push_back(*v);
    }
  }
  
  return min_v[rand() % min_v.size()];
}
