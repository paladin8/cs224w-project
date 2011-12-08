#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>

#include "dist_utils.h"

using namespace std;

// normalizes a distribution (as a map from key to probability)
void normalize(map<int,double>& D) {
  double total = 0.0;
  
  map<int,double>::iterator it;
  for (it = D.begin(); it != D.end(); it++) {
    total += (*it).second;
  }
  for (it = D.begin(); it != D.end(); it++) {
    D[(*it).first] = (*it).second / total;
  }
}

// creates a softmax distribution while avoiding overflow
void softmax_dist(map<int,double>& D) {
  map<int,double>::iterator it;
  
  double a = 0.0;
  for (it = D.begin(); it != D.end(); it++) {
    a = max((*it).second, a);
  }
  
  for (it = D.begin(); it != D.end(); it++) {
    D[(*it).first] = exp((*it).second - a);
  }

  normalize(D);
}

// picks a random item from the (normalized) probability distribution
int random_item(map<int,double>& D) {
  double r = ((double)rand() / (double)RAND_MAX);
  
  map<int,double>::iterator it;
  for (it = D.begin(); it != D.end(); it++) {
    r -= (*it).second;
    if (r <= 0) return (*it).first;
  }
  cout << "ERROR: probability distribution sums to < 1." << endl;
  exit(1);
}
