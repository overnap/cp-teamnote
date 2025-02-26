int gethull(pii* hull, int n) {
    sort(hull, hull + n);
    stable_sort(hull + 1, hull + n, [&](pii a, pii b) {
        return ccw(hull[0], a, b) > 0;
    });
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (m > 1 && ccw(hull[m - 2], hull[m - 1], hull[i]) <= 0) m--;
        hull[m++] = hull[i];
    }
    if (m > 2 && ccw(hull[0], hull[m - 1], hull[m - 2]) == 0) m--;
    return m;
}