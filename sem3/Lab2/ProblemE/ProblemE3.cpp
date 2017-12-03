#include <bits/stdc++.h>

using namespace std;

int n, true_root;
vector<int> batya2, depth;
vector<vector<int> > g;
vector<bool> used;

int dfs(int cur_v, int cur_size, int* centroid, int prev_v) {

    int s = 1;
    for (int i = 0; i < g[cur_v].size(); i++) {
        if (depth[g[cur_v][i]] == -1 && g[cur_v][i] != prev_v) {
            s += dfs(g[cur_v][i], cur_size, centroid, cur_v);
        }
    }

    if (*centroid == -1 && (s * 2 >= cur_size || prev_v == -1)) {
        *centroid = cur_v;
    }

    return s;
}

void build_cd(int cur_v, int cur_size, int deep, int prev_root) {

    int centroid = -1;
    dfs(cur_v, cur_size, &centroid, centroid);
    //cout << "centroid = " << centroid << endl;
    depth[centroid] = deep;
    batya2[centroid] = prev_root;

    if (true_root == -1) {
        true_root = centroid;
    }

    for (int i = 0; i < g[centroid].size(); i++) {
        if (depth[g[centroid][i]] == -1) {
            build_cd(g[centroid][i], cur_size / 2, deep + 1, centroid);
        }
    }
}

int main() {

    ifstream fin("smth.in");

    cin >> n;
    g.resize(n);

    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int root = 0;
    true_root = -1;
    batya2.resize(n);
    depth.assign(n, -1);
    build_cd(root, n, 0, -1);

    for (int i = 0; i < n; i++) {
        /*if (i == true_root) {
            cout << 0 << " ";
        }*/
        cout << batya2[i]  + 1<< " ";
    }
    cout << endl;

    used.resize(n, false);

    return 0;
}
