#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

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

    depth.push_back(0);
    for (int i = 1; i < n; i++) {
        depth.push_back(-1);
    }
    for (int i = 1; i < n; i++) {
        depth_counter(i);
    }

    int log = 19;
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].assign(19, 0);
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = batya[i];
    }

    for (int j = 1; j < log; j++) {
        for (int i = 1; i < n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < log; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
}

int lca(int u, int v) {
    //cout << "run1" << endl;
    if(depth[u] > depth[v]) {
        swap(u, v);
    }
    //cout << "run1" << endl;
    //int log = log2(batya.size()) + 1;
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

    ifstream fin("lca.in");
    ofstream fout("lca.out");

    int n, m;
    fin >> n;


    //batya.assign(n, -1);
    if (n != 0) {
        batya.push_back(0);
    }
    int temp;
    for (int i = 0; i < n - 1; i++) {
        //fin >> batya[i + 1];
        fin >> temp;
        temp--;
        batya.push_back(temp);
        //batya[i + 1]--;
    }

    /*cout << "batya vector: ";
    for (int i = 0; i < n; i++) {
        cout << batya[i] << " ";
    }
    cout << endl;*/
    prep();

    fin >> m;
    string s;
    //getline(fin, s);
    int a, b;
    for (int i = 0; i < m; i++) {
        fin >> a >> b;
        //cout << s << endl;
        //cout << s[0] - '0' - 1 << " " << s[2] - '0' - 1 << endl;
        fout << lca(a - 1, b - 1) + 1 << endl;
    }


    fin.close();
    fout.close();

    return 0;
}
