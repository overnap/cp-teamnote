int l = 0, r = T;
while (l+2 < r) {
    int p = (2*l+r)/3, q = (l+2*r)/3;
    ll pd = calc(p, N, stars), qd = calc(q, N, stars);
    if (pd <= qd)
        r = q-1;
    else
        l = p+1;
} // check l..r