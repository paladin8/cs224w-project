import dist_utils;
import math;
import hnetwork;
import random;

# returns the number of steps used in a decentralied search:
#   S    searcher (with next_hop function)
#   N    network (with dist function + graph G)
#   s    start node
#   t    goal node    
#   p    probability at each step of dropped message
def search(S, N, s, t, p):
    steps = 0;
    
    while s != t:
        s = S.next_hop(N, s, t);
        steps = steps + 1;
        if random.random() < p:
            return float("inf");
    
    return steps;

class SoftmaxDecentralizedSearch:
    
    def __init__(self, alpha):
        self.alpha = alpha;

    # determines the next hop in a decentralied search:
    #   N    network (with dist + graph)
    #   s    start node
    #   t    goal node
    def next_hop(self, N, s, t):
        D = dict();
        for v in N.G.neighbors(s):
            D[v] = -self.alpha * N.dist(v, t);
        P = dist_utils.softmax_dist(D);
        return dist_utils.random_item(P);
    
class PerfectDecentralizedSearch:
    
    # determines the next hop in a decentralied search:
    #   N    network (with dist + graph)
    #   s    start node
    #   t    goal node
    def next_hop(self, N, s, t):
        min_v = float("inf");
        min_d = float("inf");
        for v in N.G.neighbors(s):
            d = N.dist(v, t);
            if d < min_d:
                min_v = v;
                min_d = d;
        
        return v;
