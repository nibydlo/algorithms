#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

    ifstream fin("lis.in");
    ofstream fout("lis.out");

    int n;
    fin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    int *d = new int[n];
    int *p = new int[n];
    for (int i = 0; i < n; i++) {
        d[i] = 1;
        p[i] = -1;
        for (int j = 0; j < i; j++){
            if (a[j] < a[i]) {
                if (1 + d[j] > d[i]){
                    d[i] = 1 + d[j];
                    p[i] = j;
                }
            }
        }
    }

    int result = d[0];
    int cur = 0;
    for (int i = 0; i < n; i++){
        if (d[i] > result) {
            result = d[i];
            cur = i;
        }
    }
    fout << result << endl;

    vector<int> path;
    while (cur != -1) {
        path.push_back(cur);
        cur = p[cur];
    }

    for (int i = (int)path.size() - 1; i >= 0; i--) {
        fout << a[path[i]] << " ";
    }

    fin.close();
    fout.close();

    return 0;
}
