void fwht(vector<ll> &f) {
	const int n = f.size();
	if (n == 1)
		return;
	vector<ll> odd(n/2), even(n/2);
	for (int i=0; i<n; ++i)
		(i&1 ? odd : even)[i/2] = f[i];
	fwht(odd);
	fwht(even);
	for (int i=0; i<n/2; ++i) {
		f[i*2] = even[i] + odd[i];
		f[i*2+1] = even[i] - odd[i];
	}
}