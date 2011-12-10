#include <iostream>
#include <ctime>
#include <cstdlib>

#include "deg_dist.h"
#include "hnetwork.h"
#include "search.h"

using namespace std;

#define NUM_SEARCHES 100000
#define P 0.25

static void test_search(DecentralizedSearch& S, HNetwork& N);

int main() {
  srand(time(NULL));

  clock_t start = clock();
  ConstantDegDist dd(99);
  // PowerLawDegDist dd(2.5, 40, 1500);
  HNetwork hn(2, 13, 2, 100, 1, dd);
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

  cout << endl << "Perfect Decentralized Search:" << endl;
  PerfectDecentralizedSearch p;
  test_search(p, hn);

  /* double beta = 6;
  cout << endl << "Imperfect Decentralized Search (beta = "
       << beta << "):" << endl;
  SoftmaxDecentralizedSearch d(beta);
  test_search(d, hn); */

  return 0;
}

static void test_search(DecentralizedSearch& S, HNetwork& N) {
  double total_cost = 0.0;
  int num_successes = 0;

  clock_t start = clock();
  int i;
  for (i = 0; i < NUM_SEARCHES; i++) {
    int s = rand() % N.getN();
    int t = rand() % N.getN();
    int cost = S.search(N, s, t, P);
    if (cost != INF) {
      total_cost += cost;
      num_successes++;
    }
  }
  double diff = (1.0*clock() - start) / CLOCKS_PER_SEC;
  double avg_length = INF;
  if (num_successes > 0) {
    avg_length = total_cost / num_successes;
  }

  cout << "\tsuccess rate = " << 1.0*num_successes / NUM_SEARCHES << endl;
  cout << "\taverage search length = " << avg_length << endl;
  cout << "\tTook " << diff << " seconds for "
       << NUM_SEARCHES << " searches" << endl;
}
