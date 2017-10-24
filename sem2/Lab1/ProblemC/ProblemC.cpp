#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> result;

void findSet(int i, int j,int *w, int **d) {
    //cout << "run" << endl;
    if (d[i][j] == 0) {
        return;
    }
    if (d[i - 1][j] == d[i][j]){
        findSet(i - 1, j, w, d);
    } else {
        //cout << "run1" << endl;
        findSet(i - 1, j - w[i - 1], w, d);
        //cout << "run" << endl;
        result.push_back(i);
    }
}

int main() {

    ifstream fin("knapsack.in");
    ofstream fout("knapsack.out");

    int n, m;
    fin >> n >> m;

    int *w = new int[n];
    int *c = new int[n];

    for (int i = 0; i < n; i++) fin >> w[i];
    for (int i = 0; i < n; i++) fin >> c[i];

    int **d = new int*[n + 1];
    for (int i = 0; i <= n; i++) d[i] = new int[m + 1];
    for (int i = 0; i <= n; i++) d[i][0] = 0;
    for (int i = 0; i <= m; i++) d[0][i] = 0;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++) {
            if (j >= w[i - 1]) {
                d[i][j] = max(d[i - 1][j], d[i - 1][j - w[i - 1]] + c[i - 1]);
            } else {
                d[i][j] = d[i - 1][j];
            }
        }
    }

    /*for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }*/
    findSet(n, m, w, d);
    fout << result.size() << endl;
    for (int i = 0; i < result.size(); i++)
        fout << result[i] << " ";

    fin.close();
    fout.close();

    return 0;
}
