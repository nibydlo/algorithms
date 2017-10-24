#include <bits/stdc++.h>

using namespace std;

class Edge{
public:
    int start, finish;
    double weight;

    Edge(int a, int b, double c) {
        start = a;
        finish = b;
        weight = c;
    }
};

const double doHuya = pow(10, 40);

vector <Edge> edgeVector;
vector <vector <pair <int, double > > > edgeList;
vector <bool> cycle;

void markCycle(int curNode) {
    cycle[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i].first;
        if(!cycle[nextNode]) {
            markCycle(nextNode);
        }
    }
}

int main() {

    ifstream fin("path.in");
    ofstream fout("path.out");

    int n, m , s, start, finish;
    double weight;

    fin >> n >> m >> s;
    s--;
    edgeList.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish >> weight;
        edgeList[start - 1].push_back(make_pair(finish - 1, weight));
        edgeVector.push_back(Edge(start - 1, finish - 1, weight));
    }

    vector <bool> check(n, false);
    cycle.assign(n, false);
    vector <double> d(n, doHuya);

    d[s] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (d[edgeVector[j].finish] > d[edgeVector[j].start] + edgeVector[j].weight) {
                d[edgeVector[j].finish] = d[edgeVector[j].start] + edgeVector[j].weight;
                if (i == n - 1) {
                    check[edgeVector[j].finish] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if(check[i]) {
            markCycle(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if(cycle[i]) {
            fout << "-" << endl;
        } else if (d[i] == doHuya) {
            fout << "*" << endl;
        } else {
            fout << (long long)d[i] << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
