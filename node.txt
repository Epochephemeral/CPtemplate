struct node {
    int v, id;
    node () {};
    node (int a, int b) : v(a), id(b) {};
    bool operator < (const node & x) const {
        return v < x.v;
    }
};
string to_string(const node & x) {
    return "{" + to_string(x.v) + ", " + to_string(x.id) + "}";
}