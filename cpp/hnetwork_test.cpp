#include <iostream>
#include <ctime>

#include "deg_dist.h"
#include "hnetwork.h"
using namespace std;

int main() {
  clock_t start = clock();
  ConstantDegDist dd(300);
  HNetwork hn(2, 10, 2, 100, 1, dd);
  double diff = (1.0*clock() - start) / CLOCKS_PER_SEC;

  cout << "Random HNetwork generated:" << endl;
  cout << "\tH = " << hn.getH() << endl;
  cout << "\tl = " << hn.getl() << endl;
  cout << "\tb = " << hn.getb() << endl;
  cout << "\tg = " << hn.getg() << endl;
  cout << "\ta = " << hn.geta() << endl;
  cout << "\tnumber_of_nodes = " << hn.getN() << endl;
  cout << "\tnumber_of_edges = " << hn.getE() << endl;
  cout << endl << "Took " << diff << " seconds" << endl;

  return 0;
}
