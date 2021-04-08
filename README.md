# Competitive-Programming
Algorithms and data structures for competitive programming

I am trying to make this lib more "others-friendly" adding "How to use" documentations as some of the algorithms and data structures only i (or past i) knows what is going on the code;

Feel free to take and use whatever you want;

# Algorithms:
*chtdeque.cpp* = Convex hull trick for dynamic programming when functions and queries are in sorted order in O(N);

*convex_hull.cpp* = Returns the convex hull of the points in O(N\*logN) [working but i will update];

*dinic.cpp* = Calculates the maximum flow in O(E\*V²) using dinic's algorithm;

*ford_fulkerson.cpp* = Calculates the maximum flow in O(E\*F) using ford fulkerson algorithm;

*hungarian.cpp* = Calculates the minimum cost bipartite matching in O(V³) using (~black magic of some sort~) the hungarian algorithm;\

*linear_sieve.cpp* = Calculates the sieve of eratosthenes and primes up to N in O(N);

*polar_sort.cpp* = Sort some points using the polar coordinates in O(N\*logN);

# Data structures:

*DSU.cpp* = Disjoint set union with path compression and union by rank;\
Create = O(N);
Union = O(1);\
Find = O(1);\
~That's actually the inverse ackermann function but whatever~

*LazySegTree.cpp* = Segment tree with lazy propagation;\
Create = O(N);\
Range query = O(logN);\
Update = O(logN);\

*SegTree.cpp* = Normal Segment tree;\
Create = O(N);\
Query = O(logN);\
Update = O(logN);

*Sparse_table.cpp* = Sparse table\
Create = O(N\*logN);\
Query = O(1);\
