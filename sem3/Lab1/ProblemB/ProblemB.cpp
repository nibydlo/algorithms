#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> batya, depth;
vector<vector<int> > dp;

int lca(int u, int v) {
    if(depth[u] > depth[v]) {
        swap(u, v);
    }

    int log = 19;
    for (int i = log - 1; i >= 0; i--) {
        if(depth[dp[v][i]] >= depth[u]) {
            v = dp[v][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = log - 1; i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return batya[u];
}

void add(int a, int b) {
    if (b >= batya.size()) {
        batya.resize(b + 1, -1);
        depth.resize(b + 1, -1);
    }
    batya[b] = a;
    depth[b] = depth[a] + 1;

    vector<int> row(19, 0);
    dp.push_back(row);
    dp[b][0] = a;
    int log = 19;
    for (int j = 1; j < log; j++) {
        dp[b][j] = dp[dp[b][j - 1]][j - 1];
    }
}

int main() {

    ifstream fin("lca.in");
    ofstream fout("lca.out");

    int k;
    fin >> k;

    batya.push_back(0);
    depth.push_back(0);
    vector<int> row(19, 0);
    dp.push_back(row);

    string command;
    int a, b;
    for (int i = 0; i < k; i++) {
        fin >> command >> a >> b;
        if (command == "ADD") {
            add(a - 1, b - 1);
        } else {
            fout << lca(a - 1, b - 1) + 1 << endl;
        }
    }


    fin.close();
    fout.close();

    return 0;
}
