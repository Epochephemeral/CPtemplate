const double eps = 1e-5;
int n; //可以跑 n=668的情况
double a[105][105];
void Gauss() {
	for (int i = 1; i <= n; ++i) {
		int p = i;
		for (int j = i + 1; j <= n; ++j) 
			if (fabs(a[j][i]) > fabs(a[j][p]))
				p = j;
		if (fabs(a[i][i]) < eps) {
			cout << "No Solution" << '\n';;
			return ;
		}
		for (int j = 1; j <= n + 1; ++j)
			swap(a[i][j], a[p][j]);
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			double t = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; ++k)
				a[j][k] -= a[i][k] * t;
		}
	}
    for(int i = 1; i <= n; i++) {
        a[i][n + 1] /= a[i][i];
    }
    for(int i = 1; i <= n; i++) {
        cout << fixed << setprecision(2) << a[i][n + 1] << '\n';
    }
}
void solve() {
    cin>> n;
    for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n + 1; ++j)
			cin >> a[i][j];
    Gauss();