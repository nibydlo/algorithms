#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Edge {
    int b;
    int e;
    double w;
};

bool compareByWeight(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {

    ifstream fin("transport.in");
    ofstream fout("transport.out");

    int n, tempB, tempE;
    fin >> n;
    double R, A, tempW;
    int* x = new int[n];
    int* y = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        fin >> y[i];
    }
    fin >> R >> A;

    int it = 0;
    vector<Edge> edgeVector(n * (n - 1)/2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edgeVector[it].b = i;
            edgeVector[it].e = j;
            edgeVector[it].w = R*sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
            it++;
        }
    }
    sort(edgeVector.begin(), edgeVector.end(), compareByWeight);
    double sum = 0;
    int* treeNum = new int[n];
    for (int i = 0; i< n; i++) {
        treeNum[i] = i;
    }
    for (int i = 0; i < n*(n - 1)/2; i++) {
        tempB = edgeVector[i].b;
        tempE = edgeVector[i].e;
        tempW = edgeVector[i].w;
        if (treeNum[tempB] != treeNum[tempE]) {
            sum += tempW;
            int newNum = treeNum[tempB];
            int oldNum = treeNum[tempE];
            for (int j = 0; j < n; j++) {
                if (treeNum[j] == oldNum) {
                    treeNum[j] = newNum;
                }
            }
        }
    }
    //cout << "first sum " << sum << endl;
    double sum2 = 0;
    int* treeNum2 = new int[n + 1];
    //cout << "run" << endl;
    vector<Edge> edgeVector2(n*(n - 1)/2 + n);
    for (int i = 0; i < n*(n - 1)/2; i++) {
        edgeVector2[i].b = edgeVector[i].b;
        edgeVector2[i].e = edgeVector[i].e;
        edgeVector2[i].w = edgeVector[i].w;
    }
    for (int i = n*(n - 1)/2; i < n*(n - 1)/2 + n; i++) {
        edgeVector2[i].b = i - n*(n - 1)/2;
        edgeVector2[i].e = n;
        edgeVector2[i].w = A;
    }
    sort(edgeVector2.begin(), edgeVector2.end(), compareByWeight);
    for (int i = 0; i < n*(n - 1)/2 + n; i++) {
        tempB = edgeVector2[i].b;
        tempE = edgeVector2[i].e;
        tempW = edgeVector2[i].w;
        if (treeNum2[tempB] != treeNum2[tempE]) {
            sum2 += tempW;
            int newNum = treeNum2[tempB];
            int oldNum = treeNum2[tempE];
            for (int j = 0; j <= n; j++) {
                if (treeNum2[j] == oldNum) {
                    treeNum2[j] = newNum;
                }
            }
        }
    }
    //cout << "second sum " << sum2 << endl;
    fout << fixed << setprecision(13) << min(sum, sum2);

    fin.close();
    fout.close();

    return 0;
}
