#ifndef DIST_UTILS_H
#define DIST_UTILS_H

#include <cstdlib>
#include <map>

using namespace std;

void normalize(map<int,double>& D);
void softmax_dist(map<int,double>& D);
int random_item(map<int,double>& D);

#endif
