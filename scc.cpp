template <typename T> class graph {
public:
    struct edge {
        int from;
        int to;
        T cost;
    };
    vector<edge> edges;
    vector< vector<int> > g;
    vector<int> deg;
    int n;
    function<bool(int)> ignore;
    graph(int _n) : n(_n) {
        g.resize(n);
        deg.resize(n);
        ignore = nullptr;
    }
    int add(int from, int to, T cost = 1) {
        int id = (int)edges.size();
        g[from].push_back(id);
        deg[to]++;
        //g[to].push_back(id);
        edges.push_back({ from, to, cost });
        return id;
    }
    graph<T> reverse() const {
        graph<T> rev(n);
        for (auto &e : edges) {
            rev.add(e.to, e.from, e.cost);
        }
        return rev;
    }
    vector<int> topo() {
        vector<int> ret(n);
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(deg[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int id : g[u]) {
                int v = edges[id].to;
                if(--deg[v] == 0) {
                    q.push(v);
                    ret[v] = ret[u] + 1;
                }
            }
        }
        return ret;
    }
};
template <typename T> vector<int> find_scc(const graph<T> &g) {
  graph<T> g_rev = g.reverse();
  vector<int> order;
  vector<bool> was(g.n, false);
  function<void(int)> dfs1 = [&](int v) {
    was[v] = true;
    for (int id : g.g[v]) {
      if (g.ignore != nullptr && g.ignore(id)) {
        continue;
      }
      auto &e = g.edges[id];
      int to = e.to;
      if (!was[to]) {
        dfs1(to);
      }
    }
    order.push_back(v);
  };
  for (int i = 0; i < g.n; i++) {
    if (!was[i]) {
      dfs1(i);
    }
  }
  vector<int> c(g.n, -1);
  function<void(int)> dfs2 = [&](int v) {
    for (int id : g_rev.g[v]) {
      if (g_rev.ignore != nullptr && g_rev.ignore(id)) {
        continue;
      }
      auto &e = g_rev.edges[id];
      int to = e.to;
      if (c[to] == -1) {
        c[to] = c[v];
        dfs2(to);
      }
    }
  };
  int cnt = 0;
  for (int id = g.n - 1; id >= 0; id--) {
    int i = order[id];
    if (c[i] != -1) {
      continue;
    }
    c[i] = cnt++;
    dfs2(i);
  }
  return c;
  // c[i] <= c[j] for every edge i -> j
}
template <typename T> graph<T> Shrink(graph<T>& g) {
    auto s = find_scc(g);
    int N = *max_element(s.begin(), s.end()) + 1;
    graph<int> G(N);
    vector<int> vis(N, 0);
    for(int i = 0; i < g.n; i++) {
        for(auto& id : g.g[i]) {
            auto& [u, v, c] = g.edges[id];
            if(s[u] == s[v] || vis[s[v]] ) continue;
            G.add(s[u], s[v]);
            vis[s[v]] = 1;
        }
        for(auto& id : g.g[i]) {
            auto& [u, v, c] = g.edges[id];
            vis[s[v]] = 0;
        }
    }
    return G;
}