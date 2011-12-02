#ifndef DEG_DIST_H
#define DEG_DIST_H

#include <vector>
using namespace std;

class DegDist {
public:
  virtual int rand_deg() = 0;
};

class ConstantDegDist : public DegDist {
public:
  ConstantDegDist(int value);
  int rand_deg();

private:
  int value;
};

class PowerLawDegDist : public DegDist {
public:
  PowerLawDegDist(double gamma, int xmin, int xmax);
  int rand_deg();

private:
  double gamma;
  int xmin, xmax;

  vector<double> P;
};

#endif
