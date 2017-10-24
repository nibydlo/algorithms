#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <functional>
#include <math.h>

using namespace std;

class edge{
public:
    int start;
    int finish;
    double weight;

    edge(int a, int b, double c) {
        start = a;
        finish = b;
        weight = c;
    }
};

vector< vector <pair< int, double> > > edgeList;
vector <edge> edgeVector;
vector< double > d;
vector< bool > cycle;
const double doHuya = (double)pow(10, 40);

void markCycle(int curNode) {
    cycle[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i].first;
        if (!cycle[curNode]) {
            markCycle(nextNode);
        }
    }
}

int main() {

    ifstream fin("path.in");
    ofstream fout("path.out");

    int n, m, s, start, finish;
    double weight;
    fin >> n >> m >> s;
    edgeList.resize(n);
    d.assign(n, doHuya);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish >> weight;
        edgeList[start - 1].push_back(make_pair(finish - 1, weight));
        edgeVector.push_back(edge(start - 1, finish - 1, weight));
    }

    vector<bool> check(n, false);
    d[s - 1] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //if (d[edgeVector[j].start] < doHuya) {
                if (d[edgeVector[j].finish] > d[edgeVector[j].start] + edgeVector[j].weight) {
                    d[edgeVector[j].finish] = d[edgeVector[j].start] + edgeVector[j].weight;
                    if (i == n - 1) {
                        check[edgeVector[j].finish] = true;
                    }
                }
            //}
        }
    }

    cycle.assign(n, false);

    for (int i = 0; i < n; i++) {
        if (check[i]) {
            markCycle(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if(cycle[i]) {
            fout << "-" << endl;
        } else if (d[i] == doHuya) {
            fout << "*" << endl;
        } else {
            fout << (long long)d[i] << endl;;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
