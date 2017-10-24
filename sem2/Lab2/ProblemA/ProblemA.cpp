#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int b;
    int e;
    int w;
};

bool compareByWeight(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {

    ifstream fin("spantree2.in");
    ofstream fout("spantree2.out");

    int n, m, tempB, tempE, tempW, oldNum, newNum;
    fin >> n >> m;

    vector<Edge> edgeVector(m);
    for (int i = 0; i < m; i++) {
        fin >> tempB >> tempE >> tempW;
        edgeVector[i].b = tempB;
        edgeVector[i].e = tempE;
        edgeVector[i].w = tempW;
    }

    sort(edgeVector.begin(), edgeVector.end(), compareByWeight);

    /*for (int i = 0; i < m; i++) {
        cout << edgeVector[i].b << " " << edgeVector[i].e << " " << edgeVector[i].w << endl;
    }*/
    int* treeNum = new int[n];
    for (int i = 0; i < n; i++) {
        treeNum[i] = i + 1;
    }
    int sumWeight = 0;
    for (int i = 0; i < m; i++) {
        tempB = edgeVector[i].b;
        tempE = edgeVector[i].e;
        tempW = edgeVector[i].w;
        if (treeNum[tempB - 1] != treeNum[tempE - 1]) {
            sumWeight += tempW;
            oldNum = treeNum[tempE - 1];
            newNum = treeNum[tempB - 1];
            for (int j = 0; j < n; j++) {
                if (treeNum[j] == oldNum) {
                    treeNum[j] = newNum;
                }
            }
        }
    }

    fout << sumWeight;

    fin.close();
    fout.close();

    return 0;
}
