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
        //g[to].push_back(id);
        edges.push_back({ from, to, cost });
        return id;
    }
};