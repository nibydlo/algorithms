#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream fin("bookshelf.in");
    ofstream fout("bookshelf.out");

    int n, l;
    fin >> n >> l;

    int *h = new int[n];
    int *w = new int[n];

    for (int i = 0; i < n; i++) {
        fin >> h[i] >> w[i];
    }

    int *d = new int[n + 1];
    d[0] = 0;

    for (int i = 1; i <= n; i++) {
        //cout << "run 1 i = " << i << endl;
        int tempMin = INT_MAX;
        int j = i - 1;
        int tempWeight = 0;
        while (tempWeight + w[j] <= l && j >= 0) {
            //cout << "run 2 i = " << i << " j = " << j;
            tempWeight += w[j];
            int tempMax = 0;
            for (int k = j; k < i; k++) {
                if (h[k] > tempMax) tempMax = h[k];
            }
            tempMax += d[j];
            if (tempMax < tempMin) tempMin = tempMax;
            j--;
            //cout << " tempMin = " << tempMin << " tempWeight " << tempWeight << endl;
        }
        d[i] = tempMin;
    }

    /*for (int i = 0; i <= n; i++) {
        cout << d[i] << " ";
    }
    cout << endl;*/


    fout << d[n];
    fin.close();
    fout.close();

    return 0;
}
