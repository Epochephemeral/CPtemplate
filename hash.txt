const int base = 323131;
    for(int i = 1; i <= n; i++) {
        hashb[i] = add(mul(base , hashb[i - 1]) , b[i]);
    }
    for(int i = 1; i <= 2 * n; i++) {
        hashc[i] = add(mul(base , hashc[i - 1]) , c[i]);
    }
    auto isequal = [&](int bl, int br, int cl, int cr) { 
        if(bl < 1 || br > n || cl < 1 || cr > 2 * n) return false;
        int xb = sub(hashb[br], mul(power(base, br - bl + 1), hashb[bl - 1]));
        int xc = sub(hashc[cr], mul(power(base, cr - cl + 1), hashc[cl - 1]));
        return xb == xc;
    };