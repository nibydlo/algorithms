#include <bits/stdc++.h>

using namespace std;

int main() {

	int a, b, n, m;
	cin >> a >> b >> n >> m;
	int x = a;
	while (x % m != b) {
		x += n;
	}
	cout << x;
}
