import hnetwork as hn
import deg_dist as dd
import random

random.seed();

N = hn.HNetwork(2, 10, 2, 10, 1, dd.ConstantDegDist(20));

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
