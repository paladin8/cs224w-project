import hnetwork as hn
import deg_dist as dd
import random
import time

random.seed();

start = time.clock()
N = hn.HNetwork(2, 7, 3, 30, 1, dd.ConstantDegDist(20));
diff = time.clock() - start

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
