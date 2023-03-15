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

vector<int> cutpoint(const graph<int>& g) {
    vector<int> dfn(g.n, 0), low(g.n, 0);
    vector<int> is(g.n, 0), vis(g.n, 0);
    int cnt = 0;
    function<void(int, int)> Tarjan = [&](int u, int father) {
        vis[u] = 1;       
        low[u] = dfn[u] = ++cnt; 
        int child = 0;
        for (int id : g.g[u]) { 
            auto [x, y, _] = g.edges[id];
            int v = u ^ x ^ y;
            if (!vis[v]) {
                child++;                       
                Tarjan(v, u);                  
                low[u] = min(low[u], low[v]); 
                if (father != u && low[v] >= dfn[u] && !is[u]) {
                    is[u] = 1;
                }
            } 
            else if (v != father) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (father == u && child >= 2 && !is[u]) {
            is[u] = 1;
        }
    };
    for (int i = 0; i < g.n; i++)  {
        if (!vis[i]) {
            cnt = 0; 
            Tarjan(i, i); 
        }
    }
    return is;
}