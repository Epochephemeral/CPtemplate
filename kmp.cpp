vector<int> kmp_table(const string& s) {
    int n = (int)s.size();
    vector<int> p(n, 0);
    int k = 0;
    for (int i = 1; i < n; i++) {
        while (k > 0 && !(s[i] == s[k])) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
    // p[i] = max{k : s[0...k - 1] = s[i - (k - 1)...i]} for any k from 0 to i;
}