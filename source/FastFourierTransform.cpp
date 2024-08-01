using cd = complex<double>;
void fft(vector<cd> &f, cd w) {
	int n = f.size();
	if (n == 1)
		return;
	vector<cd> odd(n/2), even(n/2);
	for (int i=0; i<n; ++i)
		(i%2 ? odd : even)[i/2] = f[i];
	fft(odd, w*w);
	fft(even, w*w);
	cd x(1, 0);
	for (int i=0; i<n/2; ++i) {
		f[i] = even[i] + x * odd[i];
		f[i+n/2] = even[i] - x * odd[i];
		x *= w; // get through power to better accuracy
	}
}
vector<cd> mult(vector<cd> a, vector<cd> b) {
	int n;
	for (n=1; n<a.size() || n<b.size(); n*=2);
	n *= 2;
	vector<cd> ret(n);
	a.resize(n);
	b.resize(n);
	static constexpr double PI = 3.1415926535897932384;
	cd w(cos(PI*2/n), sin(PI*2/n));
	fft(a, w);
	fft(b, w);
	for (int i=0; i<n; ++i)
		ret[i] = a[i] * b[i];
	fft(ret, cd(1, 0)/w);
	for (int i=0; i<n; ++i) {
		ret[i] /= cd(n, 0);
		ret[i] = cd(round(ret[i].real()), round(ret[i].imag()));
	}
	return ret;
}