ll floor_sum(ll a, ll b, ll c, ll n) {
  ll ans = 0;
  if (a < 0) {
    ans -= (n * (n + 1) / 2) * ((a % c + c - a) / c);
    a = a % c + c;
  }
  if (b < 0) {
    ans -= (n + 1) * ((b % c + c - b) / c);
    b = b % c + c;
  }
  if (a == 0) return ans + b / c * (n + 1);
  if (a >= c or b >= c)
    return ans + (n * (n + 1) / 2) * (a / c) + (n + 1) * (b / c) +
           floor_sum(a % c, b % c, c, n);
  ll m = (a * n + b) / c;
  return ans + m * n - floor_sum(c, c - b - 1, a, m - 1);
}