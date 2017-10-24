#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int dynamics(int **d, int** prev, int l, int r, int *c) {
    //cout << "run " << endl;
    if (d[l][r] == -1) {
        if (l + 1 == r) {
            d[l][r] = 0;
            return 0;
        } else {
            d[l][r] = INT_MAX;
            for (int i = l + 1; i < r; i++) {
                int temp = c[l]*c[i]*c[r] + dynamics(d, prev, l, i, c) + dynamics(d, prev, i, r, c);
                if (d[l][r] > temp) {
                    prev[l][r] = i;
                    d[l][r] = temp;
                }
            }
        }
    }

        return d[l][r];
}

string result = "";
void answerGen(int **prev, int l, int r) {
    if (l + 1 == r) {
        result += "A";
        return;
    } else if (l + 2 == r) {
        result += "(AA)";
        return;
    }
    result += "(";
    answerGen(prev, l, prev[l][r]);
    answerGen(prev, prev[l][r], r);
    result += ")";
}


int main() {

    ifstream fin("matrix.in");
    ofstream fout("matrix.out");

    int n;
    fin >> n;

    int *a = new int[n];
    int *b = new int[n];
    int *c = new int[n + 1];

    for (int i = 0; i < n; i++) {
        fin >> a[i] >> b[i];
    }

    for (int i = 0; i < n; i++) {
        c[i] = a[i];
    }
    c[n] = b[n - 1];

    int **d = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) {
            d[i] = new int[n + 1];
            for (int j = 0; j <= n; j++) {
                d[i][j] = -1;
            }
    }
    //cout << "run 1" << endl;
    int **prev = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) {
            prev[i] = new int[n + 1];
            for (int j = 0; j <= n; j++) {
                prev[i][j] = 0;
            }
    }
    //cout << "run 2" << endl;

    int x = dynamics(d, prev, 0, n, c);
    //cout << x << endl;
    answerGen(prev, 0, n);
    /*for (int i = 0; i < (int)result.size(); i++) {
        fout << result[i];
    }*/
    fout << result;
    //cout << endl;

    fin.close();
    fout.close();

    return 0;
}
