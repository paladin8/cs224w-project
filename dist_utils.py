import math;
import random;

# normalizes a distribution (as a dictionary from key to probability)
def normalize(D):
    N = dict();
    total = 0.0;
    for p in D.values():
        total = total + p;
    
    for k in D.keys():
        N[k] = D[k] / total;
    
    return N;

# creates a softmax distribution while avoiding overflow
def softmax_dist(D):
    a = max(D.values());
    Z = 0.0;
    
    P = dict();
    for k in D.keys():
        P[k] = math.exp(D[k] - a);
    
    return normalize(P);

# picks a random item from the (normalized) probability distribution
def random_item(D):
    r = random.random();
    for k in D.keys():
        r = r - D[k];
        if r <= 0:
            return k;
    
    raise Exception("ERROR: probability distribution sums to < 1.");
