#include <bits/stdc++.h>

using namespace std;

const int part = 8192;
vector<bool> isPrime;

int main() {

	ios_base::sync_with_stdio(false);
   	cin.tie(0);
   	cout.tie(0);

	long n, x, h = 0;
	vector<int> p;

	cin >> n >> x;
   	long t = floor(sqrt(n)) + 1;
   	isPrime.assign(t, true);
   	isPrime[0] = false;
   	isPrime[1] = false;
   	for (int i = 2; i < t; i++) {
	 	if (isPrime[i]) {
			p.push_back(i);
		 	for (int j = pow(i, 2); j < t; j += i) {
				isPrime[j] = false;
			}
	  	}
	}

   	for (int k = 0; k <= n / part; k++) {

		vector <bool> b(part, false);
	 	int point = k * part;
	 	for (int i = 0; i < p.size(); i++) {
			int z = (point + p[i] - 1) / p[i];
			for (int j = max(z, 2) * p[i] - point; j < part; j += p[i]) {
				b[j] = true;
			}
	  	}

		if (k == 0) {
		 	b[0] = b[1] = true;
		}

	  	for (int i = 0; (point + i <= n) && (i < part); i++) {
		 	if (!b[i]) {
				h = h * x + point + (long) i;
			}
		}
   	}

   	cout << h;
}
