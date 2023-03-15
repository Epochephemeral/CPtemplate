template<typename T>
class fenwick {
 public :
	int n;
	vector<T> c;
	vector<T> a;
	int lowbit(int x) {
		return x & (-x);
	}
	void add(int x, int d) {
		a[x] += d;
		for (int i = x; i <= n; i += lowbit(i))
			c[i] += d;
	}
	T sum(int x) {
		T ans = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ans += c[i];
		return ans;
	}
	T sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
	fenwick(const vector<T>& x) {
		a = x;
		n = (int)a.size() - 1;
		c.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			for (int j = i - lowbit(i) + 1; j <= i; j++) {
				c[i] = c[i] + a[j];
			}
		}
	}
	//1-indexed
};