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