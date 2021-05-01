# Competitive-Programming
Algorithms and data structures for competitive programming

I am trying to make this lib more "others-friendly" adding "How to use" documentations as some of the algorithms and data structures only i (or past i) knows what is going on the code;

Feel free to take and use whatever you want;

# Algorithms:

*all_point_pairs.cpp* = Algorithm that iterates over all pair of points and maintain the in a sorted order in O(N^2*logN);\
Can be used to find the smallest traingle given a set of points 

*chtdeque.cpp* = Convex hull trick for dynamic programming when functions and queries are in sorted order in O(N);

*cht_dinamico.cpp* = Convex hull trick for dynamic programming in O(N*logN);\
add = O(logN);\
query = O(logN);

*convex_hull.cpp* = Returns the convex hull of the points in O(N\*logN) [working but i will update];

*dinic.cpp* = Calculates the maximum flow in O(E\*V²) using dinic's algorithm;

*DCO.cpp* = Dynamic Connectivitiy Offline(DSU with remove) in O(Q\*log(Q)\*log(N)) where Q=queries and N=size;

*farthest_point_direction.cpp* = Given a set of points, calculates the farthest one following some direction in O(N*logN);

*Gaussian_XOR.cpp* = Gaussian elimination in <img src="https://render.githubusercontent.com/render/math?math=\mathbb{Z}_{2}"> using XOR in <img src="https://render.githubusercontent.com/render/math?math=O(\frac{N^3}{64})">;\
add - O(N²/64);\
query - O(N²/64);

*ford_fulkerson.cpp* = Calculates the maximum flow in O(E\*F) using ford fulkerson algorithm;

*hungarian.cpp* = Calculates the minimum cost bipartite matching in O(V³) using (~black magic of some sort~) the hungarian algorithm;

*linear_sieve.cpp* = Calculates the sieve of eratosthenes and primes up to N in O(N);

*point_inside_convex_hull.cpp* = Find if a point is inside a convex hull in O(logN);

*polar_sort.cpp* = Sort some points using the polar coordinates in O(N\*logN);

*rotating_calipers.cpp* = Calculates the pair of points with greatest euclidean distance (diameter) in O(N) [You will need O(N*logN) to sort but if it is sorted works in O(N)]


# Data structures:

*DSU.cpp* = Disjoint set union with path compression and union by rank;\
Create = O(N);\
Union = O(1);\
Find = O(1);\
~That's actually the inverse ackermann function but whatever~


*LazySegTree.cpp* = Segment tree with lazy propagation;\
Create = O(N);\
Range query = O(logN);\
Update = O(logN);

*Rollback_DSU.cpp* = Disjoint set union with option to undo some union;\
Create = O(N);\
Union = O(N);\
Find = O(logN);\
Persist = O(1);\
Rollback = O(1) [amortized];

*SegTree.cpp* = Normal Segment tree;\
Create = O(N);\
Query = O(logN);\
Update = O(logN);

*Sparse_table.cpp* = Sparse table\
Create = O(N\*logN);\
Query = O(1);

*ordered_set.cpp* = Ordered set\
find_by_order = O(logN);\
order_of_key = O(logN)
