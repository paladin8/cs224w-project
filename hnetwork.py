import networkx as nx;
import random;
import math;

class HNetwork:
    
    # initialize a heirarchical network with:
    #   H   number of heirarchies
    #   l   levels in tree
    #   b   branching factor
    #   g   group size
    #   a   exponential decay factor
    #   dd  degree distribution
    def __init__(self, H, l, b, g, a, dd):
        self.H = H;
        self.l = l;
        self.b = b;
        self.g = g;
        self.a = a;
        self.dd = dd;

        # dimension size of each heirarchy
        self.dim = pow(self.b, self.l);
        
        self.init_random_network()
    
    # initialize random heirarchical network with the given parameters
    def init_random_network(self):
        self.G = nx.MultiDiGraph();
        self.G.add_nodes_from(xrange(self.dim * self.g));

        # initialize heirarchy partitions
        # self.heir[h][i] = list of nodes with coordinate i in heirarchy h
        # self.heirct[h][i][j] = number of nodes under the j-th subtree
        #                        at level i in heirarchy h (level 0 = bottom)
        self.heir = {};
        self.heirct = {};
        for h in xrange(self.H):
            self.heir[h] = {};
            for i in xrange(self.dim):
                self.heir[h][i] = [];

            # there are b^{h-i} subtrees at level i, initialize counts to zero
            self.heirct[h] = {};
            subtrees = self.dim;
            for i in xrange(self.l):
                self.heirct[h][i] = {};
                for j in xrange(subtrees):
                    self.heirct[h][i][j] = 0;
                subtrees = subtrees / self.b;

        # randomly choose heirarchies for each node
        # average g nodes per coordinate per heirarchy
        for s in self.G.nodes_iter():
            node_h = []
            for h in xrange(self.H):
                i = random.randrange(self.dim);
                node_h.append(i);
                self.heir[h][i].append(s);
                for j in xrange(self.l):
                    self.heirct[h][j][i] = self.heirct[h][j][i] + 1;
                    i = i / self.b;
            self.G.add_node(s, h = node_h);

        # randomly add edges from each node
        self.init_exp_dist()
        for s in self.G.nodes_iter():
            self.add_random_edges(s);

    # initialize normalizing constant for exponential distribution
    def init_exp_dist(self):
        self.exp_norm = 0;
        for d in xrange(self.l):
            self.exp_norm = self.exp_norm + math.exp(-self.a*d);

    # pick random degree from degree distribution, add edges randomly
    # by choosing random heirarchy, then random distance, then random node
    def add_random_edges(self, s):
        num_edges = self.dd.rand();
        for i in xrange(num_edges):
            h = random.randrange(self.H);
            d = self.random_dist();
            t = self.random_node(s, h, d);
            while s == t:
                h = random.randrange(self.H);
                d = self.random_dist();
                t = self.random_node(s, h, d);
            self.G.add_edge(s, t);

    # random heirarchical distance according to p(x) = ce^{-a*x}
    def random_dist(self):
        r = random.random();
        for d in xrange(self.l):
            r = r - math.exp(-self.a*d) / self.exp_norm;
            if r <= 0:
                return d;

    # random node in the graph which is at distance d in heirarchy h from s
    def random_node(self, s, h, d):
        si = self.G.node[s]['h'][h];
        if d == 0:
            idx = random.randrange(self.heirct[h][0][si]);
            return self.get_node(h, 0, si, idx);

        # ci is the subtree at level d in heirarchy h which s is in
        # pi is the subtree at level d-1 in heirarchy h which s is in
        pi = si;
        for i in xrange(d-1):
            pi = pi / self.b;
        ci = pi / self.b;

        # number of nodes to randomly choose from, i.e. all nodes under ci
        # which are not under pi (the ones at distance d from s in heirarchy h)
        num_nodes = self.heirct[h][d][ci] - self.heirct[h][d-1][pi];
        r = random.randrange(num_nodes);
        for i in xrange(self.b):
            ni = ci * self.b + i;
            if ni != pi:
                if r < self.heirct[h][d-1][ni]:
                    return self.get_node(h, d-1, ni, r);

    # get the idx-th node in the ci-th subtree of level d in heirarchy h
    def get_node(self, h, d, ci, idx):
        if d == 0:
            return self.heir[h][ci][idx];

        # iterate over children of subtree to find which one the node is in
        for i in xrange(self.b):
            ni = ci * self.b + i;
            if idx < self.heirct[h][d-1][ni]:
                return self.get_node(h, d-1, ni, idx);
            idx = idx - self.heirct[h][d-1][ni];

    # heirarchical distance between two nodes
    def dist(self, s, t, h):
        si = self.G.node[s]['h'][h]
        ti = self.G.node[t]['h'][h]
        d = 0
        while si != ti:
            si = si / self.b;
            ti = ti / self.b;
            d = d + 1;
        return d
