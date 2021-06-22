#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*
How to use
ordered_set<int> acts as Set
ordered_set<int,int> acts as Map
//change less<int> to less_equal<int> to work as a multiset
*/
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main(){
    ordered_set ss;
    ss.find_by_order(2);//returns an interator to the second element
    ss.order_of_key(2);//returns how many elements are smaller than 2
}
