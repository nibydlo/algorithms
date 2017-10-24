#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int root;
vector<int> batya, depth, weight;
vector<vector<int> > dp, ways;

void depth_counter(int i) {
    if (depth[i] == -1) {
        if (depth[batya[i]] == -1) {
            depth_counter(batya[i]);
        }
        depth[i] = depth[batya[i]] + 1;
    }
}

void prep() {
    int n = batya.size();

    depth.assign(batya.size(), -1);
    depth[0] = 0;
    for (int i = 1; i < n; i++) {
        depth_counter(i);
    }

    int log = 19;
    dp.resize(n);
    ways.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].assign(19, 0);
        ways[i].assign(19, INT_MAX);
    }
    for (int i = 1; i < n; i++) {
        dp[i][0] = batya[i];
        ways[i][0] = weight[i];

    }

    for (int j = 1; j < log; j++) {
        for (int i = 0; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            ways[i][j] = min(ways[i][j - 1], ways[dp[i][j - 1]][j - 1]);
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < log; j++) {
            cout << ways[i][j] << " ";
        }
        cout << endl;
    }*/
}

int lca(int u, int v) {
    if(depth[u] > depth[v]) {
        swap(u, v);
    }

    //cout << "run1" << endl;

    int log = 19;
    int min_edge = INT_MAX;
    for (int i = log - 1; i >= 0; i--) {
        if(depth[dp[v][i]] >= depth[u]) {
            if(ways[v][i] < min_edge) {
                min_edge = ways[v][i];
            }
            v = dp[v][i];
        }
    }
    //cout << "run" << endl;
    if (u == v) {
        return min_edge;
    }

    for (int i = log - 1; i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) {
            if(ways[u][i] < min_edge) {
                min_edge = ways[u][i];
            }
            u = dp[u][i];
            if(ways[v][i] < min_edge) {
                min_edge = ways[v][i];
            }
            v = dp[v][i];
        }
    }

    int final_min = min(weight[u], weight[v]);
    return min(min_edge, final_min);
}

int main() {

    ifstream fin("minonpath.in");
    ofstream fout("minonpath.out");

    int n, m;
    fin >> n;

    batya.resize(n);
    weight.resize(n);
    batya[0] = 0;
    weight[0] = INT_MAX;

    int x, y;
    for (int i = 1; i < n; i++) {
        fin >> x >> y;
        batya[i] = x - 1;
        weight[i] = y;
    }

    /*cout << "batya vector: ";
    for (int i = 0; i < n; i++) {
        cout << batya[i] << " ";
    }
    cout << endl;*/

    /*cout << "weight vector: ";
    for (int i = 0; i < n; i++) {
        cout << weight[i] << " ";
    }
    cout << endl;*/

    prep();

    fin >> m;
    int a, b;
    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        fout << lca(a - 1 , b - 1) << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
