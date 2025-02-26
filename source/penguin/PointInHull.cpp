bool onsegment(pii a, pii b, pii c) {
    return ccw(a, b, c) == 0 && (a - c) * (b - c) <= 0;
}
bool pointinhull(pii* H, int n, pii p, bool strict = true) {
    int a = 1, b = n - 1, r = !strict;
    if (n < 3) return r && onsegment(H[0], H[n - 1], p);
    if (sign(ccw(H[0], H[a], H[b])) > 0) swap(a, b);
    if (sign(ccw(H[0], H[a], p)) >= r || sign(ccw(H[0], H[b], p) <= -r))
        return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sign(ccw(H[0], H[c], p)) > 0 ? b : a) = c;
    }
    return sign(ccw(H[a], H[b], p)) < r;
}