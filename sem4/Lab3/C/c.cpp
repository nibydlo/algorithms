#include <iostream>
#include <time.h>

using namespace std;

int n;


long long mnozh(long long x, long long y, long long mod) {

	if (y == 0 || x == 0) {
		return 0;
	}

	if (y == 1) {
		return x;
	}

	if (y % 2 == 0) {
		long long lolkek = mnozh(x, y / 2, mod);
		return (2 * lolkek) % mod;
	}
	//cout << "mnozh " << x << " " << y << " " << mod << " = " << (mnozh(x, y - 1, mod) + x) % mod << endl;
	return (mnozh(x, y - 1, mod) + x) % mod;
}



long long step(long long x, long long y, long long mod) {

	if (y == 0) {
		return 1;
	}

	if (x == 1) {
		return 1;
	}

	if ((y % 2) == 0) {
		long long st = step(x, y / 2, mod);
		long long ssst = mnozh(st, st, mod) % mod;

		//cout << "step2 " << x << " " << y << " " << mod << " = " << ssst << endl;
		return ssst;
	}

	//cout << "y - 1 = " << y - 1 << endl;
	long long sst = mnozh(step(x, y - 1, mod), x, mod) % mod;
	//cout << "step " << x << " " << y << " " << mod << " = " << sst << endl;

	return sst;
}

long long nod(long long x, long long y) {
	if (y == 0) {
		return x;
	}
	return nod(y, x % y);
}

bool ferm(long long n1) {

	if (n1 == 2 || n1 == 3 || n1 == 5 || n1 == 7 || n1 == 11){
		return true;
	}


	if (n1 == 1) {
		return false;
	}

	if (n1 % 2 == 0 || n1 % 3 == 0 || n1 % 5 == 0) {
		return false;
	}

	//srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		long long a = (rand() % (n1 - 3)) + 2;
		//cout << "a = " << a << " n1 = " << n1 << endl;
		if (nod(a, n1) != 1 /* || step(a, n - 1, n) != 1*/ ) {
			//cout << "first if" << endl;
			return false;
		}

		if (step(a, n1 - 1, n1) != 1 || ) {
			//cout << "second false, step == " << step(a, n1 - 1, n1) << endl;
			return false;
		}

	}

	return true;
}

int main() {

	ios_base::sync_with_stdio(false);
    	cin.tie(0);
	cout.tie(0);

	cin >> n;
	long long a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		cout << (ferm(a) ? "YES" : "NO") << "\n";
	}

	return 0;
}
