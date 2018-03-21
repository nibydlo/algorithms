#include <bits/stdc++.h>

using namespace std;

vector<long long> p;
vector<long long> h;

void prep(string s) {

    p.resize(s.length());
    h.resize(s.length());
    p[0] = 1;
    for (int i = 1; i < s.length(); i++) {
        p[i] = p[i - 1] * 127;
    }
    h[0] = s[0];
    for (int i = 1; i < s.length(); i++) {
        h[i] = h[i - 1] + s[i] * p[i];
    }
}

void eq(int a, int b, int c, int d) {

    long long h1 = h[b];
    if (a != 0) {
        h1 -= h[a - 1];
    }

    long long h2 = h[d];
    if (c != 0) {
        h2 -= h[c - 1];
    }

    if (h1 * p[c] == h2 * p[a] || (a == c && b == d)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

int main() {

    string s;
    cin >> s;

    prep(s);
    int m, a, b, c, d;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        eq(a - 1, b - 1, c - 1, d - 1);
    }
}
