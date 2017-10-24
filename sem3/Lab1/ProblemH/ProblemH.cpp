#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int root;
vector<int> batya, depth;
vector<vector<int> > dp;

void depth_counter(int i) {
    if (depth[i] == -1) {
        if (depth[batya[i]] == -1) {
            depth_counter(batya[i]);
        }
        depth[i] = depth[batya[i]] + 1;
    }
}

void prep() {
    if (batya.size() == 0) {
        return;
    }
    int n = batya.size();

    //depth.push_back(0);
    depth.assign(batya.size(), -1);
    depth[root] = 0;
    for (int i = 0; i < n; i++) {
        depth_counter(i);
    }

    int log = 19;
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].assign(19, root);
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = batya[i];
    }

    for (int j = 1; j < log; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
}

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

int main() {

    ifstream fin("ancestor.in");
    ofstream fout("ancestor.out");

    int n, m;
    fin >> n;

    batya.resize(n);

    int temp;
    for (int i = 0; i < n; i++) {
        fin >> temp;
        if (temp == 0) {
            root = i;
            batya[i] = root;
        } else {
            batya[i] = temp - 1;
        }
    }

    prep();

    fin >> m;
    int a, b;
    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        if (depth[a - 1] > depth[b - 1] || lca(a - 1, b - 1) + 1 != a) {
            fout << 0 << endl;
        } else {
            fout << 1 << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
