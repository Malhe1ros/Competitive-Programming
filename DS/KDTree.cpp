#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1<<17;
const long long INF = 2000000000000000007;
 
struct point {
	int p[2];
	bool operator !=(const point &a) const {
		return !(p[0]==a.p[0] && p[1]==a.p[1]);
	}
};
 
struct kd_node {
	int axis,value;
	point p;
	kd_node *left, *right;
};
 
struct cmp_points {
	int axis;
	cmp_points(){}
	cmp_points(int x): axis(x) {}
	bool operator () (const point &a, const point &b) const {
		return a.p[axis]<b.p[axis];
	}
};
 
typedef kd_node* node_ptr;
 
int tests,n;
point arr[N],pts[N];
node_ptr root;
long long ans;
 
long long squared_distance(point a, point b) {
	long long ans=0;
	for(int i=0;i<2;i++) ans+=(a.p[i]-b.p[i])*1ll*(a.p[i]-b.p[i]);
	return ans;
}
 
void build_tree(node_ptr &node, int from, int to, int axis) {
	if(from>to) {
		node=NULL;
		return;
	}
 
	node=new kd_node();
 
	if(from==to) {
		node->p=arr[from];
		node->left=NULL;
		node->right=NULL;
		return;
	}
 
	int mid=(from+to)/2;
 
	nth_element(arr+from,arr+mid,arr+to+1,cmp_points(axis));
	node->value=arr[mid].p[axis];
	node->axis=axis;
	build_tree(node->left,from,mid,axis^1);
	build_tree(node->right,mid+1,to,axis^1);
}
 
void nearest_neighbor(node_ptr node, point q, long long &ans) {
	if(node==NULL) return;
 
	if(node->left==NULL && node->right==NULL) {
		if(q!=node->p) ans=min(ans,squared_distance(node->p,q));
		return;
	}
 
	if(q.p[node->axis]<=node->value) {
		nearest_neighbor(node->left,q,ans);
		if(q.p[node->axis]+sqrt(ans)>=node->value) nearest_neighbor(node->right,q,ans);
	}
 
	else {
		nearest_neighbor(node->right,q,ans);
		if(q.p[node->axis]-sqrt(ans)<=node->value) nearest_neighbor(node->left,q,ans);
	}
}
 
int main() {
	int i;
 
	scanf("%d", &tests);
	while(tests--) {
		scanf("%d", &n);
		for(i=1;i<=n;i++) {
			scanf("%d %d", &arr[i].p[0], &arr[i].p[1]);
			pts[i]=arr[i];
		}
 
		build_tree(root,1,n,0);
 
		for(i=1;i<=n;i++) {
			ans=INF;
			nearest_neighbor(root,pts[i],ans);
			printf("%lld\n", ans);
		}
	}
 
	return 0;
}
 
