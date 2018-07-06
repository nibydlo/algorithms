#include <bits/stdc++.h>
using namespace std;

int const m = 1000001;

vector <bool> isPrime(m, true);

int main() {

	ios_base::sync_with_stdio(false);
    	cin.tie(0);

	isPrime[0] = false;
	isPrime[1] = false;

	for (int i = 2; i < m; i++) {
		if (isPrime[i]) {
			if (pow(i, 2) < m) {
				for (int j = pow(i, 2); j < m; j += i) {
					isPrime[j] = false;
				}
			}
		}
	}

	int n;
	cin >> n;

	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		cout << (isPrime[x] ? "YES" : "NO") << endl;
	}

}
