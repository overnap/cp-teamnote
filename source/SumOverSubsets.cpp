for (int i=0; i<(1<<n); i++)
    f[i] = a[i];
for (int j=0; j<n; j++)
    for(int i=0; i<(1<<N); i++)
	    if (i & (1<<j))
            f[i] += f[i ^ (1<<j)];