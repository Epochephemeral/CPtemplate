namespace Hjt {
    #define ls lson[now_]
    #define rs rson[now_]
    const int MAXN = 1e5 + 5;
    int root[MAXN];
    int lson[MAXN << 5], rson[MAXN << 5], val[MAXN << 5], node_num = 0;
    void Insert(int &now_, int pre_, int l, int r, int pos, int val_) {
        now_ = ++ node_num;
        val[now_] = val[pre_] + val_; 
        ls = lson[pre_], rs = rson[pre_];
        if(l == r) return ;
        int mid = (l + r) >> 1;
        if(pos <= mid) Insert(ls, lson[pre_], l, mid, pos, val_);
        else Insert(rs, rson[pre_], mid + 1, r, pos, val_);
    }
    int Query(int now_, int pre_, int l, int r, int L, int R) {
        if(!(val[now_] - val[pre_])) return 0;
        if(L <= l && r <= R) return val[now_] - val[pre_];
        int mid = (l + r) >> 1, res = 0;
        if(mid >= L) res += Query(ls, lson[pre_], l, mid, L, R);
        if(mid < R) res += Query(rs, rson[pre_], mid + 1, r, L, R);
        return res;
    }
}
