//给定 n 个整数（数字可能重复），求在这些数中选取任意个，使得他们的异或和最大
typedef long long ll;
const ll N = 55, bit = 50;
ll n, a, p[N];
void insert(ll k) {
	for(ll i=bit;i>=0;i--) {
		if(!(k&(1LL<<i))) continue;
		if(!p[i]) return p[i] = k, void();
		k ^= p[i];
	}
}
ll maxXor() {
	ll res = 0;
	for(ll i=bit;i>=0;i--) res = max(res, (res^p[i]));
	return res;
}

void solve() {
    scanf("%lld", &n);
	while(n--) {scanf("%lld", &a); insert(a);}
	printf("%lld\n", maxXor());
}
