using ull = unsigned long long;
ull modmul(ull a, ull b, ull n) {
    return ((unsigned __int128)a * b) % n;
}
// if __int128 isn't available
ull modmul(ull a, ull b, ull n) {
   if (b == 0)
       return 0;
   if (b == 1)
       return a;
   ull t = modmul(a, b/2, n);
   t = (t+t)%n;
   if (b % 2)
       t = (t+a)%n;
   return t;
}
ull modpow(ull a, ull d, ull n) {
    if (d == 0)
        return 1;
    ull r = modpow(a, d/2, n);
    r = modmul(r, r, n);
    if (d % 2)
        r = modmul(r, a, n);
    return r;
}
ull gcd(ull a, ull b) {
    return b ? gcd(b, a%b) : a;
}