template <typename T>
class graph {
public:
    struct edge {
        int from;
        int to;
        T cost;
    };
    vector<edge> edges;
    vector< vector<int> > g;
    int n;
    function<bool(int)> ignore;
    graph(int _n) : n(_n) {
        g.resize(n);
        ignore = nullptr;
    }
    int add(int from, int to, T cost = 1) {
        int id = (int)edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({ from, to, cost });
        return id;
    }
};

vector<array<int, 2> > brige(const graph<int>& g) {
    vector<int> dfn(g.n, 0), low(g.n, 0), fa(g.n, 0);
    vector<array<int, 2> > res;
    int cnt = 0;
    function<void(int, int)> Tarjan = [&](int u, int father) {
        fa[u] = father;       
        low[u] = dfn[u] = ++cnt; 
        int child = 0;
        for (int id : g.g[u]) { 
            auto [x, y, _] = g.edges[id];
            int v = u ^ x ^ y;
            if (!dfn[v]) {
                Tarjan(v, u);                  
                low[u] = min(low[u], low[v]); 
                if (low[v] > dfn[u]) {
                    res.push_back({u, v});
                }
            } 
            else if (dfn[v] < dfn[u] && v != father) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    for (int i = 0; i < g.n; i++)  {
        if (!dfn[i]) {
            cnt = 0; 
            Tarjan(i, -1); 
        }
    }
    return res;
}