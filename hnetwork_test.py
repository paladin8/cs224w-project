import hnetwork as hn;
import decentral_search as ds;
import deg_dist as dd;
import random;
import time;

def test_search(S):
    num_searches = 5000;
    total_cost = 0.0;
    num_successes = 0.0;
    p = 0.25;
    
    start = time.clock();
    for i in xrange(num_searches):
        s = random.choice(N.G.nodes());
        t = random.choice(N.G.nodes());
        cost = ds.search(S, N, s, t, p);
        if cost != float("inf"):
            total_cost = total_cost + cost;
            num_successes = num_successes + 1.0;

    diff = time.clock() - start;
    avg_length = total_cost / num_successes if num_successes > 0 else \
                float("inf");
    
    print "\tsuccess rate =", num_successes / num_searches;
    print "\taverage search length =", avg_length;
    print 
    print "Took", diff, "seconds for", num_searches, "searches";

random.seed();

start = time.clock();
N = hn.HNetwork(2, 5, 2, 100, 1, dd.ConstantDegDist(300));
diff = time.clock() - start;

# print "Nodes =", N.G.nodes(data = True);
# print "Edges =", N.G.edges();
# print

print "Random HNetwork generated:";
print "\tH =", N.H;
print "\tl =", N.l;
print "\tb =", N.b;
print "\tg =", N.g;
print "\ta =", N.a;
print "\tnumber_of_nodes =", N.G.number_of_nodes();
print "\tnumber_of_edges =", N.G.number_of_edges();
print
print "Took", diff, "seconds";

print
print "Perfect Decentralized Search:";
test_search(ds.PerfectDecentralizedSearch());

alpha = 100000;
print
print "Imperfect Decentralized Search:";
print "\talpha =", alpha;
test_search(ds.SoftmaxDecentralizedSearch(alpha));
