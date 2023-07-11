class Tree {
public:
    struct edge {
        int from;
        int to;
    };
    vector<edge> edges;
    vector< vector<int> > g;
    
    int n, root;

    vector<int> depth;
    vector<int> lg;
    vector<vector<int> > fa;
    bool pre = 0;

    Tree(int _n, int _r) : n(_n), root(_r) {
        g.resize(n);
        depth.resize(n);
        lg.resize(n);
        fa.assign(n, vector<int>(23, 0));
        
    }
    int add(int from, int to) {
        int id = (int)edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({ from, to });
        return id;
    }
    int LCA(int x, int y) {
        //1 - indexed
        if(!pre) {
            for(int i = 1; i <= n; i++) {
	            lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
            }
            function<void(int, int)> dfs = [&](int now, int fath) {
                fa[now][0] = fath; 
                depth[now] = depth[fath] + 1;
                for (int i = 1; i <= lg[depth[now]]; ++i) {
                    fa[now][i] = fa[fa[now][i - 1]][i - 1];
                }
                for(int id : g[now]) {
                    int v = edges[id].from ^ edges[id].to ^ now;
                    if (v != fath) dfs(v, now);
                }
            };
            dfs(root, 0);
            pre = 1;
        }
        if (depth[x] < depth[y]) swap(x, y);
        while (depth[x] > depth[y]) {
            x = fa[x][lg[depth[x] - depth[y]] - 1];
        }
        if (x == y) return x;
        for (int k = lg[depth[x]] - 1; k >= 0; --k) {
            if (fa[x][k] != fa[y][k]) {
                x = fa[x][k], y = fa[y][k];
            }
        }
        return fa[x][0];
    }
};