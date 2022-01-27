//r is the point where the floor(n/i) changes;
for(int l = 1, r; l <= n; l = r + 1) {
	r = n / (n / l);
}
