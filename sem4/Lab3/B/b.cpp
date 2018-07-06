#include <bits/stdc++.h>
using namespace std;

int const m = 1000001;

vector<bool> isPrime(m, true);
vector<vector<int> > parts(m);

int main() {

	ios_base::sync_with_stdio(false);
    	cin.tie(0);
	cout.tie(0);

	isPrime[0] = false;
	isPrime[1] = false;

	for (int i = 2; pow(i, 2) < m; i++) {
		if (isPrime[i]) {
			for (int j = pow(i, 2); j < m; j += i) {
				isPrime[j] = false;
				parts[j].push_back(i);
			}
		}
	}

	int n;
	cin >> n;

	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (isPrime[x]) {
			cout << x << "\n";
			continue;
		}
		int first_x = x;
		for (int j = 0; j < parts[first_x].size(); j++) {
			while(!(x % parts[first_x][j])) {
				cout << parts[first_x][j] << " ";
				x /= parts[first_x][j];
			}
		}
		cout << (x == 1 ? "" : to_string(x)) << '\n';
	}

}
