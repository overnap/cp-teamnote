pii operator + (const pii& a, const pii& b) {
    return {a.first + b.first, a.second + b.second};
}
pii operator - (const pii& a, const pii& b) {
    return {a.first - b.first, a.second - b.second};
}
ll operator * (const pii& a, const pii& b) {
    return (ll)a.first * b.first + (ll)a.second * b.second;
}
ll operator / (const pii& a, const pii& b) {
    return (ll)a.first * b.second - (ll)a.second * b.first;
}
ll ccw(const pii& a, const pii& b, const pii& c) {
    return (b - a) / (c - b);
}
ll distsq(const pii& a, const pii& b) {
    return (a - b) * (a - b);
}
int sign(ll v) {
    return (v > 0) - (v < 0);
}
bool onsegment(pii a, pii b, pii c) {
    return ccw(a, b, c) == 0 && (a - c) * (b - c) <= 0;
}