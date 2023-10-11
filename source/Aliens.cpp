  ll lo = 0, hi = 1e15;
  while (lo + 1 < hi) {
    const ll mid = (lo + hi) / 2;
    auto [dp, cnt] = dec(mid); // the best DP[N][K] and its K value
    if (cnt < k) hi = mid;
    else lo = mid;
  }
  cout << (dec(lo).first - lo * k) / 2;