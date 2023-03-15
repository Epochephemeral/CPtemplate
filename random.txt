mt19937_64 rg(std::chrono::steady_clock::now().time_since_epoch().count());
int rng(int l, int r){
    return l + rg() % (r - l + 1);
}