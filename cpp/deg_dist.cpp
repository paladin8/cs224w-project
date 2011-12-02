#include <cstdlib>
#include <cmath>
#include <iostream>

#include "deg_dist.h"
using namespace std;

ConstantDegDist::ConstantDegDist(int value) {
  this->value = value;
}

int ConstantDegDist::rand_deg() {
  return this->value;
}

PowerLawDegDist::PowerLawDegDist(double gamma, int xmin, int xmax) {
  this->gamma = gamma;
  this->xmin = xmin;
  this->xmax = xmax;

  double tot = 0, prev = 0;
  for (int i = xmin; i <= xmax; i++) {
    double px = pow(1.0*i, -gamma);
    P.push_back(tot + px);
    tot += px;
  }
  for (int i = xmin; i <= xmax; i++) P[i-xmin] /= tot;
}

int PowerLawDegDist::rand_deg() {
  double r = 1.0*rand()/RAND_MAX;
  int low = xmin-1, hi = xmax;
  while (hi - low > 1) {
    int mid = (low + hi) / 2;
    if (P[mid-xmin] >= r) hi = mid;
    else low = mid;
  }
  return hi;
}
