//当我们想知道A选不选，只需要比较A和!A所属联通块的编号就OK了
//选择那个编号更大，即拓扑序更靠后的决策
     int n, m;
    cin >> n >> m;
    graph<int> g(2 * n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g.add(u, cus(v));
        g.add(v, cus(u));
    }
    auto v = find_scc(g);
    for(int i = 0; i < 2 * n; i += 2) {
        if(v[i] == v[i + 1]) {
            cout << "NIE" << '\n';  return ;
        }
    }
    for(int i = 0; i < 2 * n; i += 2) {
        if(v[i] > v[i + 1]) {
            cout << i + 1 << '\n';
        }
        else {
            cout << i + 2 << '\n';
        }
    }