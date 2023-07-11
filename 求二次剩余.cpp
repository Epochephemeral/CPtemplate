using ll = long long int;
#define int long long

ll qpow(ll x, ll n, ll mod) {
  ll res = 1;
  for (x %= mod; n > 0; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

// Tonelli-Shanks
ll ModSqrt(ll a, ll p) {
  if (a == 0 || p <= 2) return a;
  if (qpow(a, (p - 1) / 2, p) != 1) return -1;
  if (p % 4 == 3) return qpow(a, (p + 1) / 4, p);
  ll k = __builtin_ctz(p - 1), h = (p - 1) >> k;
  ll N = 2; while (qpow(N, (p - 1) / 2, p) == 1) N += 1;
  ll x = qpow(a, (h + 1) / 2, p), g = qpow(N, h, p), b = qpow(a, h, p);
  for (ll m = 0;; k = m) {
    ll t = b;
    for (m = 0; m < k && t != 1; m++) t = t * t % p;
    if (m == 0) return x;
    ll gs = qpow(g, 1 << (k - m - 1), p);
    g = gs * gs % p, b = b * g % p, x = x * gs % p;
  }
  return -1;//复杂度粗略估计为log^2(p)
}