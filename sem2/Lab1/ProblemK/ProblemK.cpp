#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int binSearchLeft(int *a, int l, int r, int sought) {
    while (r - 1 > l) {
        int m = l + (r - l)/2;
        if (a[m] >= sought) {
            r = m;
        } else {
            l = m;
        }
    }
    return l;
}

int binSearchRight(int *a, int l, int r, int sought) {
    while (r - 1 > l) {
        int m = l + (r - l)/2;
        if (a[m] >= sought) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main() {

    ifstream fin("ski.in");
    ofstream fout("ski.out");

    int n, k, m;
    fin >> n >> k >> m;

    int *days = new int[m];
    for (int i = 0; i < m; i++) {
        fin >> days[i];
    }

    sort(days, days + m);
    int *d = new int[m];

    for (int i = 0; i < m; i++) {
        int j = binSearchLeft(days, -1, i, days[i] - k + 1);
        if (j != -1) {
            d[i] = d[j] + days[i] - k - days[j];
        } else {
            d[i] = max(days[i] - k, 0);
        }
    }

    /*for (int i = 0; i < m; i++) {
        cout << d[i] << " ";
    }
    cout << endl;*/

    int result = d[m - 1] + n - days[m - 1];
    //cout << "result = " << result << endl;

    int flday = binSearchRight(days, -1, m, days[m - 1] - k + 1);
    //cout << "flday = " << flday << endl;

    for (int i = flday; i < m; i++) {
        int temp;
        if (i < 1) {
            temp = days[i] - 1 + max(0, n - days[i] - k + 1);
            //cout << "days[i] = " << days[i] << endl;
        } else {
            temp = d[i - 1] + days[i] - days[i - 1] - 1 + max(0, n - days[i] - k + 1);
        }
        //cout << "temp = " << temp << " i = " << i << endl;
        result = max(temp, result);
    }

    fout << result;

    fin.close();
    fout.close();

    return 0;
}
