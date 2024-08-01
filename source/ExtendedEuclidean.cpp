pair<ll, ll> extGCD(ll a,ll b){
    if (b != 0) {
        auto tmp = extGCD(b, a % b);
        return {tmp.second, tmp.first - (a / b) * tmp.second};
    } else return {1ll, 0ll};
}
// code from MatthewChan
// Find a x + b y = d where d is (a,b).
int egcd(int a, int b, int& x, int &y) {
  if (!b) { x = 1; y = 0; return a; }
  int result = egcd(b, a%b, y, x);
  y -= x * (a/b);
  return result;
}
// Given a, b, c, >=0, find smallest x, y >=0 s.t. ax-by = c (if possible)
bool canon_egcd(int a, int b, int c, int& x, int& y) {
  int d = egcd(a, b, x, y);
  if (c%d) return false;
  y = ((-y*c/d)%(a/d) + (a/d))%(a/d);
  x = (c + b*y)/a;
  return true;
}
// Check Relative primeness egcd(a,b,dummy, dummy) == 1
// Modular Inverse of a (mod n)
if (egcd(a, b, x, y) == 1) return x;
else return ERROR;