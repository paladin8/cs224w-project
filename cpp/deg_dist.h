#ifndef DEG_DIST_H
#define DEG_DIST_H

class DegDist {
public:
  virtual int rand() = 0;
};

class ConstantDegDist : public DegDist {
public:
  ConstantDegDist(int value);
  int rand();

private:
  int value;
};

#endif
