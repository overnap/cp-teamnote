struct basis {
	const static int n = 30; // log2(1e9)
	array<int, n> data{};
	void insert(int x) {
		for (int i=0; i<n; ++i) {
			if (data[i] && (x >> (n-1-i) & 1))
				x ^= data[i];
		}
		int y;
		for (y=0; y<n; ++y) {
			if (!data[y] && (x >> (n-1-y) & 1))
				break;
		}
		if (y < n) {
			for (int i=0; i<n; ++i) {
				if (data[i] >> (n-1-y) & 1)
					data[i] ^= x;
			}
			data[y] = x;
		}
	}
	basis operator+(const basis &other) {
		basis ret{};
		for (int x : data)
			ret.insert(x);
		for (int x : other.data)
			ret.insert(x);
		return ret;
	}
};