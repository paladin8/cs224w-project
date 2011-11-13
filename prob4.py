import networkx as nx;
import matplotlib.pyplot as plt;
import operator;
import random;
import math;

h_T = 10;
b = 2;
k = 5;

def edge_dist(G, i, alpha):
    dist = {};
    total = 0.0;
    for j in G.nodes_iter():
        if i == j:
            continue;
        numerator = pow(b, -1 * alpha * h(i,j));
        dist[j] = numerator;
        total += numerator;
    
    for j in dist.keys():
        dist[j] = dist[j] / total;
    
    return dist;

def random_neighbor(G, i, dist):
    prob = random.random();
    for j, p in dist.iteritems():
        prob = prob - p;
        if prob < 0:
            return j;
    
    raise Exception("ERROR: invalid probability distribution.");
    
def add_random_edges(G, i, alpha):
    dist = edge_dist(G, i, alpha);
    for e in range(k):
        G.add_edge(i, random_neighbor(G, i, dist));

def h(s, t):
    if s == t:
        return 0;
    else:
        return math.floor(math.log(s ^ t, 2)) + 1;

def decentralized_search(G, s, t):
    length = 0.0;
    while s != t:
        heights = [(i, h(i, t)) for i in G.neighbors(s)];
        _, min_height = min(heights, key=lambda (i, h): h);
        if min_height >= h(s, t):
            return None;

        min_heights = filter(lambda (i, h): h == min_height, heights);
        s = random.choice(min_heights)[0];
        length = length + 1;
    
    return length;

def random_pair(G):
    return random.sample(G.nodes(), 2);

def random_graph(alpha):
    G = nx.MultiDiGraph();
    G.add_nodes_from(range(pow(b,h_T)));
    
    for i in G.nodes_iter():
        add_random_edges(G, i, alpha);

    return G;

def random_searches(G):
    average = 0.0;
    success = 0.0;
    for _ in range(1000):
        i, j = random_pair(G);
        path_length = decentralized_search(G, i, j);
        if not path_length is None:
            average = average + path_length;
            success = success + 1.0;
    
    average = average / max(1, success);
    success = success / 1000.0;
    
    return average, success;
    
def part_h():
    alphas = [a * 0.1 for a in range(1, 100)];
    graphs = map(random_graph, alphas);
    results = map(random_searches, graphs);
    
    lengths = zip(*results)[0];
    success = zip(*results)[1];
    
    plt.clf();
    lh = plt.plot(alphas, lengths, 'bs-');
    
    plt.xlabel('alpha');
    plt.ylabel('average path length');
    plt.title('4.h Decentralized Search Average Path Length');

    plt.savefig('prob4h1.pdf');
    print "Plot saved to prob4h1.pdf";

    plt.clf();
    lh = plt.plot(alphas, success, 'bs-');
    
    plt.xlabel('alpha');
    plt.ylabel('success rate');
    plt.title('4.h Decentralized Search Success Rate');

    plt.savefig('prob4h2.pdf');
    print "Plot saved to prob4h2.pdf";
