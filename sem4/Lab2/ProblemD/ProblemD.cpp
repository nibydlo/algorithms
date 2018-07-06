#include <bits/stdc++.h>

using namespace std;

int main() {

	ifstream fin("rps2.in");
	ofstream fout("rps2.out");

	int r1, s1, p1, r2, s2, p2;
	fin >>  r1 >> s1 >> p1 >> r2 >> s2 >> p2;
	fout << max(max(r1 - r2 - p2, s1 - s2 - r2), max(p1 - p2 - s2, 0)) << endl;

	fin.close();
	fout.close();

	return 0;
}
