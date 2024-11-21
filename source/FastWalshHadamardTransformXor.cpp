void fwht_xor(vector<ll> &a, bool inv = false) {
  ll n = a.size();
  for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
    for (int l = 0; l < n; l += s) {
      for (int i = 0; i < h; i++) {
        ll t = a[l + h + i];
        a[l + h + i] = a[l + i] - t;
        a[l + i] += t;
        if (inv)
          a[l + h + i] /= 2, a[l + i] /= 2;
      }
    }
  }
}

vector<ll> a, b, c;
fwht_xor(a);
fwht_xor(b);
for (int i = 0; i < sz; i++)
  c[i] = a[i] * b[i];
fwht_xor(c, true);