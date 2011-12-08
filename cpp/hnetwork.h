#ifndef H_NETWORK_H
#define H_NETWORK_H

#include <vector>
#include <set>

#include "deg_dist.h"
using namespace std;

#define INF 1000000000

class HNetwork {
public:
  HNetwork(int H, int l, int b, int g, double a, DegDist& dd);
  const vector<int>& get_neighbors(int s) { return adj[s]; }
  
  int dist(int s, int t);
  int dist_single(int s, int t, int h);

  int getH() { return H; }
  int getl() { return l; }
  int getb() { return b; }
  int getg() { return g; }
  double geta() { return a; }

  int getN() { return N; }
  int getE() { return E; }

private:
  void init_random_network();
  void init_exp_dist();

  int add_random_edges(int s);
  int random_dist();
  int random_node(int s, int h, int d);
  int get_node(int h, int d, int ci, int idx);

  int H, l, b, g, dim, N, E;
  double a, exp_norm;
  DegDist& dd;

  vector<vector<int> > adj, node_h;
  vector<vector<vector<int> > > hier, hierct;
};

#endif
