#include <bits/stdc++.h>

using namespace std;

int n, true_root;
vector<bool> used;
vector<int> depth, s, batya;
vector<vector<int> > g;
bool first_centr;

int dfs(int cur_v, int prev_v) {

    used[cur_v] = true;
    //depth[cur_v] = cur_depth;
    batya[cur_v] = prev_v;

    int ans = 0;
    for (int i = 0; i < g[cur_v].size(); i++) {
        if (!used[g[cur_v][i]]) {
            ans += dfs(g[cur_v][i], cur_v);
        }
    }

    ans++;
    s[cur_v] = ans;
    return ans;
}

int rehang(int cur_v, int prev_v, int forbidden) {
    used[cur_v] = true;
    cout << "start rehang; forbidden = " << forbidden << "   cur_v = " << cur_v << endl;
    batya[cur_v] = prev_v;
    //cout << "new batya[" << cur_v << "] = " << prev_v << endl;
    int ans = 0;
    for (int i = 0; i < g[cur_v].size(); i++) {
        if(/*g[cur_v][i] != prev_v*/ !used[g[cur_v][i]] && g[cur_v][i] != forbidden) {
            ans += rehang(g[cur_v][i], cur_v, forbidden);
        }
    }

    ans++;
    s[cur_v] = ans;
    for (int i = 0; i < n; i++) {
        if (i == true_root) {
            cout << 0 << " ";
        } else {
            cout << batya[i] + 1 << " ";
        }
    }
    cout << endl;
    return ans;
}

void build_cd(int cur_v, int cur_root, int prev_v/*, int prev_root*/) {

    cout << endl << endl << "statr bcd" << endl << endl;


    //finding centroid
    int heavy = cur_v;

    for (int i = 0; i < g[cur_v].size(); i++) {
        if (g[cur_v][i] != prev_v && s[g[cur_v][i]] >= s[cur_v] - s[g[cur_v][i]]) {
            cout << "s[g[cur_v][i]] = " << s[g[cur_v][i]] << "   s[cur_v] - s[g[cur_v][i]] " << s[cur_v] - s[g[cur_v][i]] << endl;
            heavy = g[cur_v][i];
            cout << "heavy1 = " <<  heavy << endl;
        }
    }

    while (heavy != cur_v) {
        int temp_cur_v = heavy;
        int new_heavy = heavy;
        for (int i = 0; i < g[heavy].size(); i++) {
            if (g[heavy][i] != cur_v && s[g[heavy][i]] >= s[cur_root] - s[g[heavy][i]]) {
                cout << "s[g[heavy][i]] = " << s[g[heavy][i]] << "   s[cur_root] - s[g[heavy][i]] " << s[cur_root] - s[g[heavy][i]] << endl;
                cout << "g[heavy][i] = " << g[heavy][i] << endl;
                new_heavy = g[heavy][i];
            }
        }
        heavy = new_heavy;
        cur_v = temp_cur_v;
        //prev_v = batya[cur_v];
        //cout << "root = " << root << endl;
        cout << "heavy = " << heavy << "   cur_v = " << cur_v << endl;
    }
    int centroid = heavy;
    cout << "centroid = " << centroid << endl;
    //int save_centroid = -1;
    if (first_centr) {
        //save_centroid = centroid;
        true_root = centroid;
        first_centr = false;
    }


    //rehanging upper subtree
    used.clear();
    used.assign(n, false);
    if(centroid != cur_root) {
        rehang(batya[centroid], centroid, cur_root);
    }
    //statring recurs
    for (int i = 0; i < g[centroid].size(); i++) {
        if (g[centroid][i] != batya[centroid]) {
            build_cd(g[centroid][i], g[centroid][i] ,centroid);
        }
    }

    /*if(save_centroid != -1) {
        true_root = save_centroid;
        batya[save_centroid] = 0;
        first_centr = false;
    }*/

    batya[true_root] = 0;
}

int main() {

    ifstream fin("smth.in");

    fin >> n;
    g.resize(n);

    int u, v;

    for (int i = 0; i < n - 1; i++) {
        fin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    batya.resize(n);
    depth.resize(n);
    s.resize(n);
    used.assign(n, false);

    //int root = rand() % n;
    int root = 0;
    dfs(root, root);

    /*cout << "s : ";
    for (int i = 0; i < n; i++) {
        cout << s[i] << " ";
    }
    cout << endl;*/

    used.clear();
    used.assign(n, false);

    cout << "old batya : ";
    for (int i = 0; i < n; i++) {
        cout << batya[i] << " ";
    }
    cout << endl;

    first_centr = true;
    build_cd(root, root, root);

    //cout << "new batya : ";
    for (int i = 0; i < n; i++) {
        if (i == true_root) {
            cout << 0 << " ";
        } else {
            cout << batya[i] + 1 << " ";
        }
    }
    cout << endl;

    return 0;
}
