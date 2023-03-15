const int mod = 998244353;

int add(int a, int b) {
     return (a + b) % mod;
}
void _add(int & a, int b) {
    a = add(a, b);
}
int sub(int a, int b) {
    return (a - b + mod) % mod;
}
int mul(int a, int b) {
     return (a * 1ll * b) % mod;
}

int power(int a, int b){
   int res = 1;
   while(b > 0) {
      if(b & 1) res = mul(res, a);
       a = mul(a, a);
       b >>= 1;
   }
   return res;
}
int INV[1000005];
int inv(int x) {
    if(INV[x]) return INV[x];
    return INV[x] = power(x, mod - 2);
}

int Div(int a, int b) {
    return mul(a, inv(b));
}
vector<int> fact(1, 1);
vector<int> inv_fact(1, 1);

int C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(mul(fact.back(), (int) fact.size()));
    inv_fact.push_back(Div(1, fact.back()));
  }
  return mul(mul(fact[n], inv_fact[k]), inv_fact[n - k]);
}

int fac(int n) {
    while((int) fact.size() < n + 1) {
         fact.push_back(mul(fact.back(), (int) fact.size()));
        inv_fact.push_back(Div(1, fact.back()));
    }
    return fact[n];
}
int C(long long x, int y)  {
    if (y < 0 || y > x) {
      return 0;
    }
    int c = 1;
    for (int i = 1; i <= y; i++) {
      c = mul(c, Div(x - i + 1, i));
    }
    return c;
}