int up(int a, int b) {
    return (a + b - 1) / b;
}

struct Q {
    int l, r, id;
};

int a[M], belong[M], cnt[M];

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int siz = (int)sqrt(n);
    for(int i = 0; i < n; i++) {
        belong[i] = i / siz;
    }
    auto cmp = [&](Q a, Q b) {
	   return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : ((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
    };
    int m;
    cin >> m;
    vector<Q> q(m);
    for(int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        --q[i].l, --q[i].r;
        q[i].id = i;
    }
    sort(all(q), cmp);
    int now = 0;
    int l = 1, r = 0;
    auto add = [&](int pos) {
        now += (cnt[a[pos]] == 0);
        cnt[a[pos]]++;
    };
    auto del = [&](int pos) {
        cnt[a[pos]]--;
        now -= (cnt[a[pos]] == 0);
    };
    vi ans(m);
    for(int i = 0; i < m; i++) {
        while(l < q[i].l) del(l++);
        while(l > q[i].l) add(--l);
        while(r < q[i].r) add(++r);
        while(r > q[i].r) del(r--);
        ans[q[i].id] = now;
    }
    for(int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
}