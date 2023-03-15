#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 2e18;
int add(int a, int b)
{
    return (a + b) % mod;
}
int mul(int a, int b)
{
    return (a * 1ll * b) % mod;
}
class segtree
{
public:
    struct node
    {
        long long sum = 0;
        long long Add = 0;
        void apply(int l, int r, long long v)
        {
            Add = add(Add, v);
            sum = add(sum, mul((r - l + 1), v));
        }
    };
    node unite(const node &a, const node &b) const
    {
        node res;
        res.sum = add(a.sum, b.sum);
        return res;
    }
    inline void push(int x, int l, int r)
    {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (tree[x].Add != 0)
        {
            tree[x + 1].apply(l, y, tree[x].Add);
            tree[z].apply(y + 1, r, tree[x].Add);
            tree[x].Add = 0;
        }
    }
    inline void pulL(int x, int z)
    {
        tree[x] = unite(tree[x + 1], tree[z]);
    }
    int n;
    vector<node> tree;
    void build(int x, int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pulL(x, z);
    }
    template <typename M>
    void build(int x, int l, int r, const vector<M> &v)
    {
        if (l == r)
        {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pulL(x, z);
    }
    node get(int x, int l, int r, int lL, int rr)
    {
        if (lL <= l && r <= rr)
        {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res{};
        if (rr <= y)
        {
            res = get(x + 1, l, y, lL, rr);
        }
        else
        {
            if (lL > y)
            {
                res = get(z, y + 1, r, lL, rr);
            }
            else
            {
                res = unite(get(x + 1, l, y, lL, rr), get(z, y + 1, r, lL, rr));
            }
        }
        pulL(x, z);
        return res;
    }
    template <typename... M>
    void modify(int x, int l, int r, int lL, int rr, const M &...v)
    {
        if (lL <= l && r <= rr)
        {
            tree[x].apply(l, r, v...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (lL <= y)
        {
            modify(x + 1, l, y, lL, rr, v...);
        }
        if (rr > y)
        {
            modify(z, y + 1, r, lL, rr, v...);
        }
        pulL(x, z);
    }
    segtree(int _n) : n(_n)
    {
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    template <typename M>
    segtree(const vector<M> &v)
    {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    node get(int lL, int rr)
    {
        return get(0, 0, n - 1, lL, rr);
    }
    node get(int p)
    {
        return get(0, 0, n - 1, p, p);
    }
    template <typename... M>
    void modify(int lL, int rr, const M &...v)
    {
        modify(0, 0, n - 1, lL, rr, v...);
    }
};

//------segtree-------//
const int MaxN = 100005;

struct graph_t
{
    int cnte = 0;
    int head[MaxN], to[MaxN * 2 + 5], next[MaxN * 2 + 5];

    inline void add_edge(int u, int v)
    {
        to[++cnte] = v;
        next[cnte] = head[u];
        head[u] = cnte;
    }
};

int A[MaxN]; // i节点的点权
int Fa[MaxN], Dep[MaxN], Siz[MaxN], Wson[MaxN];
// i的父亲，i的深度，以i为根的子树的节点个数，i节点的重儿子
int Id[MaxN], Top[MaxN], Dfc;
// i的dfn序的下标，i所在的重链的起点

graph_t Gr;

void dfs1(int u)
{
    Siz[u] = 1;
    for (int i = Gr.head[u]; i; i = Gr.next[i])
    {
        int v = Gr.to[i];
        if (v == Fa[u])
            continue;
        Fa[v] = u;
        Dep[v] = Dep[u] + 1;
        dfs1(v);
        Siz[u] += Siz[v];
        if (Siz[v] > Siz[Wson[u]])
            Wson[u] = v;
    }
}

void dfs2(int u, int chain)
{
    Top[u] = chain;
    Id[u] = ++Dfc;
    if (Wson[u] != 0)
        dfs2(Wson[u], chain);
    for (int i = Gr.head[u]; i; i = Gr.next[i])
    {
        int v = Gr.to[i];
        if (v == Fa[u] || v == Wson[u])
            continue;
        dfs2(v, v);
    }
}

inline int getLca(int u, int v)
{
    while (Top[u] != Top[v])
    {
        if (Dep[Top[u]] < Dep[Top[v]])
            std::swap(u, v);
        u = Fa[Top[u]];
    }
    return Dep[u] < Dep[v] ? u : v;
}

void solve() {

    int n, m, r;
    cin >> n >> m >> r >> mod;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    segtree st(MaxN);
    auto sum = [&](int x,int y) {
        long long ans = 0;
        int fx = Top[x], fy = Top[y];
        while(fx != fy)
        {
            if(Dep[fx] >= Dep[fy])
            {
                ans = add(ans, st.get(Id[fx],Id[x]).sum);
                x = Fa[fx], fx = Top[x];
            }
            else
            {
                ans = add(ans, st.get(Id[fy],Id[y]).sum);
                y = Fa[fy], fy = Top[y];
            }
        }
        
        ans = add(ans, st.get(min(Id[x], Id[y]), max(Id[x], Id[y])).sum);
    
        return ans;
    };
    auto updates = [&](int x,int y,int c)
    {
        int fx = Top[x], fy = Top[y];
        while(fx != fy)
        {
            if(Dep[fx] >= Dep[fy])
            {
                st.modify(Id[fx], Id[x], c);
                x = Fa[fx], fx = Top[x];
            }
            else
            {
                st.modify(Id[fy], Id[y], c);
                y = Fa[fy], fy = Top[y];
            }
        }
        st.modify(min(Id[x], Id[y]), max(Id[x], Id[y]), c);
    };
    for(int i = 0; i < n - 1; i++) {
        int u , v;
        cin >> u >> v;
        Gr.add_edge(u, v);
        Gr.add_edge(v, u);
    }
    dfs1(r);
    dfs2(r, r);
    for(int i = 1; i <= n; i++) {
        st.modify(Id[i], Id[i], A[i]);
    }
    for(int i = 0; i < m; i++) {
        int op; cin >> op;
        if(op == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            updates(x, y, z);
        }
        else if(op == 2) {
            int x, y;
            cin >> x >> y;
            cout << sum(x, y) << '\n';
        }
        else if(op == 3) {
            int x, z;
            cin >> x >> z;
            st.modify(Id[x], Id[x] + Siz[x] - 1, z);
        }
        else {
            int x;
            cin >> x;
            cout << st.get(Id[x], Id[x] + Siz[x] - 1).sum << '\n';
        }
    }

}

signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int _ = 1; //cin >> _;
    while(_--) solve(); 
    return 0;
}