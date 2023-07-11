 int n = rng(1, 5), m = (0, n * (n - 1) / 2);
    cout << n << ' ' << m << '\n';
    vector<vector<int> > used(n + 1, vector<int>(n + 1, 0));
    for(int i = 0; i < m; i++) {
        int u = rng(1, n);
        int v = rng(1, n);
        while(used[u][v] || v == u) {
            u = rng(1, n), v = rng(1, n);
        }
        used[u][v] = 1;
        cout << u << ' ' << v << '\n';
    }