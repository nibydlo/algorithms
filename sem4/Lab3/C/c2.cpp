#include <bits/stdc++.h>

using namespace std;

long long mnozh (long long x, long long y, long long mod){

	if(y == 1) {
		return x;
	}

	if(y % 2 == 0) {
		long long st = mnozh(x, y/2, mod);
		return (2 * st) % mod;
	}

	return (mnozh(x, y - 1, mod) + x) % mod;
}

long long step(long long x, long long y, long long mod){

	if (y == 0) {
		return 1;
	}

	if(y % 2 == 0) {
		long long st = step(x, y/2, mod);
		return mnozh(st, st, mod) % mod;
	}

	return (mnozh(step(x, y - 1, mod) , x, mod)) % mod;
}

long long nod (long long x, long long y) {

	if(y == 0) {
		return x;
	}
	return nod(y, x % y);
}


bool ferma(long long n1) {

	if (n1 == 1 || n1 % 2 == 0 || n1 % 3 == 0) {
		return false;
	}

	if(n1 == 2) {
		return true;
	}

	srand(time(NULL));
	for(int i = 0; i < 10; i++){
		long long a = (rand() % (n1 - 2)) + 2;
		if (nod(a, n1) != 1) {
			return false;
		}
		if (step(a, n1 - 1, n1) != 1) {
			return false;
		}
	}
	return true;
}

int main() {

	ios_base::sync_with_stdio(false);
    	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	long long x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		cout << (ferma(x) ? "YES" : "NO") << "\n";
	}

	return 0;
}
