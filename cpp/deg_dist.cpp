#include "deg_dist.h"

ConstantDegDist::ConstantDegDist(int value) {
  this->value = value;
}

int ConstantDegDist::rand() {
  return this->value;
}
