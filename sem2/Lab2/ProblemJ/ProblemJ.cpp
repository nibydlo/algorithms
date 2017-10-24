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

    int n, m, tempB, tempE, oldNum, newNum;
    double R, A, tempW;
    fin >> n;
    //cout << n << endl;
    double* x = new double[n];
    double* y = new double[n];
    for (int i = 0; i < n; i++) {
        fin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        fin >> y[i];
    }
    fin >> R >> A;

    vector<Edge> edgeVector(n * (n - 1)/2);
    int it = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edgeVector[it].b = i;
            edgeVector[it].e = j;
            edgeVector[it].w = R*sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
            //cout << edgeVector[it].b << " " << edgeVector[it].e << " " << edgeVector[it].w << endl;
            it++;
        }
    }

    sort(edgeVector.begin(), edgeVector.end(), compareByWeight);

    int* treeNum = new int[n];
    for (int i = 0; i < n; i++) {
        treeNum[i] = i;
    }
    double sumWeight = 0;
    for (int i = 0; i < n*(n-1)/2; i++) {
        tempB = edgeVector[i].b;
        tempE = edgeVector[i].e;
        tempW = edgeVector[i].w;
        //cout << tempB << " " << tempE << " " << tempW << endl;
        if (treeNum[tempB] != treeNum[tempE]) {
            //cout << "run if" << endl;
            //cout << tempW << endl;
            sumWeight += tempW;
            oldNum = treeNum[tempE];
            newNum = treeNum[tempB];
            for (int j = 0; j < n; j++) {
                if (treeNum[j] == oldNum) {
                    treeNum[j] = newNum;
                }
            }
        }
    }
    //cout << sumWeight << endl;
    //double firstCase = sumWeight;
    double sumWeight2 = 0;
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

    /*for (int i = 0; i < n*(n - 1)/2 + n; i++) {
        cout << edgeVector2[i].b << " " << edgeVector2[i].e << " " << edgeVector2[i].w << endl;
    }*/
    //cout << "run" << endl;
    sort(edgeVector2.begin(), edgeVector2.end(), compareByWeight);

    int* treeNum2 = new int[n + 1];
    for (int i = 0; i <= n; i++) {
        treeNum2[i] = i;
    }
    //cout << " run " << endl;
    //sumWeight2 = 0;
    for (int i = 0; i < n*(n-1)/2 + n; i++) {
        int tB = edgeVector2[i].b;
        int tE = edgeVector2[i].e;
        double tW = edgeVector2[i].w;
        //cout << tempB << " " << tempE << " " << tempW << endl;
        if (treeNum2[tB] != treeNum2[tE]) {
            //cout << "run if" << endl;
            //cout << "tw = " << tW << endl;
            sumWeight2 += tW;
            oldNum = treeNum2[tE];
            newNum = treeNum2[tB];
            for (int j = 0; j <= n; j++) {
                if (treeNum2[j] == oldNum) {
                    treeNum2[j] = newNum;
                }
            }
        }
    }
    //cout <<  sumWeight2 << endl;
    fout << fixed << setprecision(13) << min(sumWeight, sumWeight2);

    fin.close();
    fout.close();

    return 0;
}
