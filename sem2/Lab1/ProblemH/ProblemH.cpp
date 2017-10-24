#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

long long d[18][1 << 18];

int main() {

    ifstream fin("salesman.in");
    ofstream fout("salesman.out");

    int n, m;
    fin >> n >> m;
    //cout << n << m << endl;
    long long w[18][18];
    //cout << LLONG_MAX << endl;
    int a, b, tempW;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            w[i][j] = 1e15;
        }
    }
    for (int i = 0; i < m; i++) {
        fin >> a >> b >> tempW;
        //cout << a << " " << b << " " << tempW << endl;
        w[a - 1][b - 1] = tempW;
        w[b - 1][a - 1] = tempW;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            d[i][j] = 1e15;
        }
    }

    for (int i = 0; i < n; i++) {
        d[i][(1 << i)] = 0;
    }

    for (int mask = 1; mask < 1 << n; mask++) {
        //cout << "run1" << endl;
        for (int i = 0; i < n; i++) {
            //cout << "run2" << endl;
            for (int j = 0; j < n; j++) {
                //cout << "run3" << endl;
                //cout << "mask = " << mask << " i = " << i << " j = " << j << endl;
                if ((mask & (1 << j)) == 0) {
                    //cout << "run" << endl;
                    d[j][mask ^ (1 << j)] = min(d[i][mask] + w[i][j], d[j][mask ^ (1 << j)]);
                    //cout << "first = " << d[j][mask ^ (1 << j)] << " second = " << d[i][mask] + w[i][j] << endl;
                    //cout << " if mask = " << mask << " i = " << i << " j = " << j << " d = " <<
                    //d[j][mask ^ (1 << j)] << endl;
                }
            }
        }
    }

    long long answer = 1e15;
    for (int i = 0; i < n; i++) {
        if (d[i][(1 << n) - 1] < answer) answer = d[i][(1 << n) - 1];
    }

    if (answer < 1e15) fout << answer;
    else fout << -1;

    fin.close();
    fout.close();

    return 0;
}
