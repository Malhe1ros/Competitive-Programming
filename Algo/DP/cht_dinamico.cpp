#include <bits/stdc++.h>
using namespace std;


/*
THIS A CONVEX HULL TRICK FOR MAXIMUM
TO GET MIN: INSERT LINES WITH NEGATIVE SIGNS AND NEGATE THE QUERY ANSWER
HOW TO USE
ADD(M,B) - INSERTS LINE M*X+B IN CONVEX HULL
QUERY(X) - RETURNS THE MAXIMUM VALUE AT X;
*/


// https://github.com/pauloamed/Training/blob/master/PD/cht.cpp
#define int long long



const int inf = LLONG_MAX; // ATENCAO

struct Line{
	// Line equation defined as y = x * m + b
  // m: slope, b: intersect/bias
  // p: x-pos where the line stops being the maximum
	mutable int m, b, p;

  // comparator to other Lines, uses slopes for comparison
  // used for ordering the container (insertion)
	bool operator <(const Line &o) const {
    if(m == o.m) return b < o.b;
    else return m < o.m;
  }

  // comparator to scalars, used in querying best line for a given value
	bool operator <(const int x) const { return p < x;}

  // evals scalar for this line
  int eval(int x) const { return x*m + b;}

  int intersect (const Line &o) const{
    // floor division (works for negative values) (eg. floor(-1/2) = -1 , c++ returns 0)
    // note that (a^b) < 0 iff a*b<0 (there is a bit indicating if x is negative)
    // if a/b < 0 and it isnt a integer, add -1 to c++ result
    int x = b - o.b, y = o.m - m;
    return (x/y) - ((x^y) < 0 && x % y);
  }
};


// Inheriting an order container for mantaining the line orders
// note that both comparators yield the same order, so querying using a scalar is ok
// less<> (transparent) allowing the usage of both comparators
// Lines are ordered by slope. i < j => slope(line_i) < slope(line_j)
struct DynamicCHT : multiset<Line,less<>> {

  // Insertion of y = m * x + b, may remove now unecessary lines and also
  // will update the ending position for the added line.
  // Also, the added line may be useless and wont modify the structure
  // Note that the lines from both direcitons (before and after) the recently
  // added may be removed.
	void add(int m, int b){
    // y: iterator for the added line
    // z: iterator for the next line (in order)
		auto z = insert({m, b, inf}), y = z++;
    // y << z


    // Note that the structure always mantain only one Line with slope m.
    // If the added line has same slope than the next one, it is useless.
    // By ordering, it will have a lower bias, so it will always produce
    // smaller results
    if(z != end() && y->m == z->m){ erase(y); return; }
    if(y != begin()){
      auto x = --y; y++;
      if(x->m == y->m) x = erase(x);
    }

    // y: added line, z: line to the right
    // erasing now useless lines to the right
    while(true){
      // take lines A and B where B is best until R and slope(A) < slope(B)
      // if intersect(A,B) > R, A starts being a better line before B
      // (slope is better) and ends after B ends itself. I.e. B is now useless

      // if there is no z, the limit is inf
      if(z == end()){ y->p = inf; break;}

      // else z is valid and may be removed
      y->p = y->intersect(*z);
      if(y->p < z->p) break;
      else z = erase(z);
    }

    if(y == begin()) return; // wont remove anynone to the left
    // cerr << size() << endl;

    // erasing lines to the left of the added one, using the same idea that is
    // used when removing from the right
    // take lines A, B and C, where C is the added one. we can test A against B
    // and, if needed, remove B
    // Note that begin() wont be removed, since it has smaller slope

    z = y; // z will keep the added line
    auto x = --y;
    while(true){
      // updating endpos of the line to the left of Z
    	int newIntersect = x->intersect(*z);
      // cerr << newIntersect << " " << x->p << endl;
    	if(newIntersect <= x->p) x->p = newIntersect; // updating x endpos
    	else{
        // cerr << newIntersect << " " << x->p << endl;
    		// the added line is useless if it only intersects
    		// to the one to the left afther the one on the left
    		// stops being maximum
    		erase(z); break;
    	}
      if(x == begin()) break;
      y = x--; // now x << y << z
      if(x->p < y->p) break;
      else erase(y); // y is useless
    }
	}

	// Querying
	int query(int x){
    assert(!empty());
    // lower bound for (Line comparator using scalar)
    // first Line y in Set s.t. !(p(y) < x). that is, first line in which x fits it
		return lower_bound(x)->eval(x);
	}
};
