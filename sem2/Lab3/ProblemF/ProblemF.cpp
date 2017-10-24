#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class edge{
public:
    int start;
    int finish;
    long long weight;

    edge(int a, int b, long long c) {
        start = a;
        finish = b;
        weight = c;
    }
};

const long long noEdge = 1000000000;
vector <vector <pair<int, int> > > edgeList;
vector <edge> edgeVector;
vector <long long> d, p;

int main() {

    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    int n, m = 0;
    long long t;
    fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            fin >> t;
            if (t != noEdge) {
                edgeVector.push_back(edge(i, j, t));
            }
        }
    }

    d.resize(n);
    p.assign(n, -1);

    int a = -1;
    for (int i = 0; i < n; i++) {
        a = -1;
        for(int j = 0; j < edgeVector.size(); j++) {
            if (d[edgeVector[j].finish] > d[edgeVector[j].start] + edgeVector[j].weight) {
                d[edgeVector[j].finish] = max(-LLONG_MAX, d[edgeVector[j].start] + edgeVector[j].weight);
                p[edgeVector[j].finish] = edgeVector[j].start;
                a = edgeVector[j].finish;
            }
        }
    }

    if (a == -1) {
        fout << "NO";
        return 0;
    } else {
        int b = a;
        for (int i = 0; i < n; i++) {
            b = p[b];
        }
        vector<int> ans;
        for (int i = b; ; i = p[i]) {
            ans.push_back(i);
            if (i == b && ans.size() > 1) {
                break;
            }
        }
        reverse (ans.begin(), ans.end());

        fout << "YES" << endl;
        fout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            fout << ans[i] + 1 << " ";
        }
    }


    fin.close();
    fout.close();

    return 0;
}
