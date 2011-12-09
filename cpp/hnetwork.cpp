#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

#include "hnetwork.h"

// initialize a hierarchical network with:
//   H   number of hierarchies
//   l   levels in tree
//   b   branching factor
//   g   group size
//   a   exponential decay factor
//   dd  degree distribution
HNetwork::HNetwork(int H, int l, int b, int g, double a, DegDist& dd) : dd(dd) {
  this->H = H;
  this->l = l;
  this->b = b;
  this->g = g;
  this->a = a;

  dim = 1;
  for (int i = 0; i < l; i++) dim *= b;
  N = g * dim;

  init_random_network();
}

// initialize random hierarchical network with the given parameters
void HNetwork::init_random_network() {
  srand(time(NULL));

  adj.resize(N);
  node_h.resize(N);

  // initialize hierarchy partitions
  //   self.hier[h][i] = list of nodes with coordinate i in hierarchy h
  //   self.hierct[h][i][j] = number of nodes under the j-th subtree
  //                          at level i in hierarchy h (level 0 = bottom)
  hier.resize(H, vector<vector<int> >(dim));
  hierct.resize(H, vector<vector<int> >(l));
  for (int i = 0; i < H; i++) {
    // there are b^{l-i} subtrees at level i, initialize counts to zero
    int subtrees = dim;
    for (int j = 0; j < l; j++) {
      hierct[i][j].resize(subtrees, 0);
      subtrees /= b;
    }
  }

  // randomly choose hierarchies for each node
  // average g nodes per coordinate per hierarchy
  for (int s = 0; s < N; s++)
    for (int h = 0; h < H; h++) {
      int i = rand() % dim;
      node_h[s].push_back(i);
      hier[h][i].push_back(s);
      for (int j = 0; j < l; j++) {
        hierct[h][j][i]++;
        i /= b;
      }
    }

  init_exp_dist();

  // randomly add edges from each node
  E = 0;
  for (int s = 0; s < N; s++)
    E += add_random_edges(s);
}

// initialize normalizing constant for exponential distribution
void HNetwork::init_exp_dist() {
  exp_norm = 0;
  for (int d = 0; d < l; d++) exp_norm += exp(-a*d);
}

// pick random degree from degree distribution, add edges randomly
// by choosing random hierarchy, then random distance, then random node
int HNetwork::add_random_edges(int s) {
  int num_edges = dd.rand_deg();
  for (int i = 0; i < num_edges; i++) {
    int h = rand() % H;
    int d = random_dist();
    int t = random_node(s, h, d);
    while (s == t) {
      h = rand() % H;
      d = random_dist();
      t = random_node(s, h, d);
    }
    adj[s].push_back(t);
  }
  return num_edges;
}

// random hierarchical distance according to p(x) = ce^{-a*x}
int HNetwork::random_dist() {
  double r = 1.0*rand()/RAND_MAX;
  for (int d = 0; d < l; d++) {
    r -= exp(-a*d)/exp_norm;
    if (r < 1e-8) return d;
  }
  cout << "ERROR: probability distribution sums to < 1." << endl;
  exit(1);
}

// random node in the graph which is at distance d in hierarchy h from s
int HNetwork::random_node(int s, int h, int d) {
  int si = node_h[s][h];
  if (d == 0) return get_node(h, 0, si, rand() % hierct[h][0][si]);

  // ci is the subtree at level d in hierarchy h which s is in
  // pi is the subtree at level d-1 in hierarchy h which s is in
  int pi = si;
  for (int i = 0; i < d-1; i++) pi /= b;
  int ci = pi / b;

  // number of nodes to randomly choose from, i.e. all nodes under ci
  // which are not under pi (the ones at distance d from s in hierarchy h)
  int num_nodes = hierct[h][d][ci] - hierct[h][d-1][pi];
  int r = rand() % num_nodes;
  for (int i = 0; i < b; i++) {
    int ni = ci*b + i;
    if (ni != pi) {
      if (r < hierct[h][d-1][ni]) return get_node(h, d-1, ni, r);
      r -= hierct[h][d-1][ni];
    }
  }
  return -1;
}

// get the idx-th node in the ci-th subtree of level d in hierarchy h
int HNetwork::get_node(int h, int d, int ci, int idx) {
  if (d == 0) return hier[h][ci][idx];

  // iterate over children of subtree to find which one the node is in
  for (int i = 0; i < b; i++) {
    int ni = ci*b + i;
    if (idx < hierct[h][d-1][ni]) return get_node(h, d-1, ni, idx);
    idx -= hierct[h][d-1][ni];
  }
  return -1;
}

// hierarchical distance between two nodes across all hierarchies
int HNetwork::dist(int s, int t) {
  int d = INF;
  for (int h = 0; h < H; h++) d = min(d, dist_single(s, t, h));
  return d;
}

// hierarchical distance between two nodes in a single hierarchy
int HNetwork::dist_single(int s, int t, int h) {
  int si = node_h[s][h], ti = node_h[t][h], d = 0;
  while (si != ti) {
    si /= b; ti /= b;
    d++;
  }
  return d;
}
