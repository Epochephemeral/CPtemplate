class segtree {
public:
    struct node {
        int sum = 0;
        int add = 0;
        void apply(int l, int r, int v) {
            add += v;
            sum += (r - l + 1) * v;
        }
    };
    node unite(const node& a, const node& b) const {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }
    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (tree[x].add != 0) {
            tree[x + 1].apply(l, y, tree[x].add);
            tree[z].apply(y + 1, r, tree[x].add);
            tree[x].add = 0;
        }
    }
    inline void pulL(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }
    int n;
    vector<node> tree;
    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pulL(x, z);
    }
    template <typename M>
    void build(int x, int l, int r, const vector<M>& v) {
        if (l == r) {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pulL(x, z);
    }
    node get(int x, int l, int r, int lL, int rr) {
        if (lL <= l && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res{};
        if (rr <= y) {
            res = get(x + 1, l, y, lL, rr);
        }
        else {
            if (lL > y) {
                res = get(z, y + 1, r, lL, rr);
            }
            else {
                res = unite(get(x + 1, l, y, lL, rr), get(z, y + 1, r, lL, rr));
            }
        }
        pulL(x, z);
        return res;
    }
    template <typename... M>
    void modify(int x, int l, int r, int lL, int rr, const M&... v) {
        if (lL <= l && r <= rr) {
            tree[x].apply(l, r, v...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (lL <= y) {
            modify(x + 1, l, y, lL, rr, v...);
        }
        if (rr > y) {
            modify(z, y + 1, r, lL, rr, v...);
        }
        pulL(x, z);
    }
    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
        if (l == r) {
            return l;
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[x + 1])) {
            res = find_first_knowingly(x + 1, l, y, f);
        } else {
            res = find_first_knowingly(z, y + 1, r, f);
        }
        pulL(x, z);
        return res;
    }
   int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
    if (ll <= l && r <= rr) {
        if (!f(tree[x])) {
            return -1;
        }
            return find_first_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res = -1;
    if (ll <= y) {
        res = find_first(x + 1, l, y, ll, rr, f);
    }
    if (rr > y && res == -1) {
        res = find_first(z, y + 1, r, ll, rr, f);
    }
    pulL(x, z);
    return res;
  }
  int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
    if (l == r) {
        return l;
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res;
    if (f(tree[z])) {
        res = find_last_knowingly(z, y + 1, r, f);
    } else {
        res = find_last_knowingly(x + 1, l, y, f);
    }
    pulL(x, z);
    return res;
  }
  int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[x])) {
        return -1;
      }
      return find_last_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res = -1;
    if (rr > y) {
      res = find_last(z, y + 1, r, ll, rr, f);
    }
    if (ll <= y && res == -1) {
      res = find_last(x + 1, l, y, ll, rr, f);
    }
    pulL(x, z);
    return res;
  }
    template <typename M>
    segtree(const vector<M>& v) {
        n = v.size();
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    node get(int lL, int rr) {
        assert(0 <= lL && lL <= rr && rr <= n - 1);
        return get(0, 0, n - 1, lL, rr);
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(0, 0, n - 1, p, p);
    }
   int find_first(int ll, int rr, const function<bool(const node&)> &f) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return find_first(0, 0, n - 1, ll, rr, f);
    }
    int find_last(int ll, int rr, const function<bool(const node&)> &f) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return find_last(0, 0, n - 1, ll, rr, f);
    }
    template <typename... M>
    void modify(int lL, int rr, const M&... v) {
        assert(0 <= lL && lL <= rr && rr <= n - 1);
        modify(0, 0, n - 1, lL, rr, v...);
    }
};