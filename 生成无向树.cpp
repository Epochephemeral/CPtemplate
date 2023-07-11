class dsu {
public:
    vector<int> p;
    int n;
    vector<int> rank;
    dsu(int _n) : n(_n) {
        p.resize(n);
        rank.resize(n);
        fill(rank.begin(), rank.end(), 0);
        iota(p.begin(), p.end(), 0);
    }

    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    inline bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (rank[x] <= rank[y])
            p[x] = y;
        else
            p[y] = x;
        if (p[x] == p[y] && x != y)
            rank[y]++;
        return true;
    }
};
void solve() {

    int n = rng(1, 10);
    cout << n << '\n';
    dsu d(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int u = rng(1, n);
        int v = rng(1, n);
        while(!d.unite(u, v)) {
            u = rng(1, n), v = rng(1, n);
        }
        cout << u << ' ' << v << '\n';
    }

}