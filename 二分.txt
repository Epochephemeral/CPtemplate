while(l < r) {
	int mid = l + r >> 1;
	if(check(mid)) {
		r = mid;
	}
	else {
		l = mid + 1;
	}
}
ret = l;
// find the minimum feasible solution

while(l <= r) {
	int mid = l + r >> 1;
	if(check(mid)) {
		l = mid + 1;
	}
	else {
		r = mid - 1;
	}
}
ret = r;
//find the maximum feasible solution 