#include <bits/stdc++.h>

using namespace std;

int n, true_root;
vector<bool> used, used2;
vector<int> s, batya, new_batya;
vector<vector<int> > g;

int dfs(int cur_v, int prev_v) {

    used[cur_v] = true;
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

int first_rehang(int cur_v, int prev_v) {
    used[cur_v]= true;
    used[prev_v] = true;
    new_batya[cur_v] = prev_v;
    int ans = 0;
    for (int i = 0; i < g[cur_v].size(); i++) {
        if (!used[g[cur_v][i]]) {
            ans += first_rehang(g[cur_v][i], cur_v);
        }
    }

    ans++;
    s[cur_v] = ans;
    return ans;
}

void find_true_root(int cur_v) {

    int cur_root = cur_v;
    int heavy = cur_v;
    int temp_cur_v = cur_v;

    for (int i = 0; i < g[cur_v].size(); i++) {
        if (s[g[cur_v][i]] > s[cur_v] - s[g[cur_v][i]]) {
            heavy = g[cur_v][i];
        }
    }

    used.clear();
    used.assign(n, false);

    while (heavy != temp_cur_v) {
        //cout << "run" << endl;
        used[heavy]= true;
        int new_heavy = heavy;
        //int save_temp_cur_v = temp_cur_v;
        for (int i = 0; i < g[heavy].size(); i++) {

            //cout << "s[g[heavy][i] = " << s[g[heavy][i]] << "   s[cur_root] = " << s[cur_root] << endl;
            if (g[heavy][i] != temp_cur_v && s[g[heavy][i]] > s[cur_root] - s[g[heavy][i]] && !used[g[heavy][i]]) {
                new_heavy = g[heavy][i];
                //cout << "new heavy = " << new_heavy << endl;
            }
        }
        temp_cur_v = heavy;
        heavy = new_heavy;
        //temp_cur_v = save_temp_cur_v;
    }

    true_root = heavy;

    used.clear();
    used.assign(n, false);
    if (true_root != cur_root) {
        first_rehang(batya[true_root], true_root);
    }

    //new_batya[true_root] = 1;
    s[true_root] = n;
}

int rehang(int cur_v, int prev_v, int prev_root) {
    used[cur_v]= true;
    used[prev_v] = true;
    new_batya[cur_v] = prev_v;
    int ans = 0;
    for (int i = 0; i < g[cur_v].size(); i++) {
        if (!used[g[cur_v][i]] && g[cur_v][i] != prev_root) {
            ans += rehang(g[cur_v][i], cur_v, prev_root);
        }
    }

    ans++;
    s[cur_v] = ans;
    return ans;
}

void build_cd(int cur_v, int prev_root) {
    //cout << "run build cd cur_v = " << cur_v << "   prev_v = " << prev_root << endl;
    int cur_root = cur_v;
    int heavy = cur_v;
    int temp_cur_v = cur_v;

    for (int i = 0; i < g[cur_v].size(); i++) {
        if (s[g[cur_v][i]] > s[cur_v] - s[g[cur_v][i]] && g[cur_v][i] != prev_root && !used2[g[cur_v][i]]) {
            heavy = g[cur_v][i];
        }
    }

    used.clear();
    used.assign(n, false);

    while (heavy != temp_cur_v) {
        used[heavy]= true;
        int new_heavy = heavy;
        for (int i = 0; i < g[heavy].size(); i++) {
            if (g[heavy][i] != temp_cur_v && s[g[heavy][i]] > s[cur_root] - s[g[heavy][i]] && !used[g[heavy][i]] && !used2[g[heavy][i]]) {
                new_heavy = g[heavy][i];
            }
        }
        temp_cur_v = heavy;
        heavy = new_heavy;
    }

    int new_root = heavy;

    used.clear();
    used.assign(n, false);
    if (new_root != cur_root) {
        s[new_root] += rehang(batya[new_root], new_root, prev_root);
    }
    new_batya[new_root] = prev_root;
    used2[new_root] = true;
    for (int i = 0; i < g[new_root].size(); i++) {
        if (g[new_root][i] != prev_root && !used2[g[new_root][i]]) {
            build_cd(g[new_root][i], new_root);
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

    /*cout << endl << "g: " << endl;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;*/

    used.assign(n, false);
    batya.resize(n);
    s.resize(n);

    int root = 0;
    dfs(root, root);

    /*cout << "s : ";
    for (int i = 0; i < n; i++) {
        cout << s[i] << " ";
    }
    cout << endl;*/

    true_root = root;

    //cout << "batya: " << endl;
    /*for (int i = 0; i < n; i++) {
        if (i == true_root) {
            cout << 0 << " ";
        } else {
            cout << batya[i] + 1 << " ";
        }
    }
    cout << endl;*/
    new_batya.resize(n);
used2.assign(n, false);
    find_true_root(root);
    new_batya[true_root] = 0;
    for (int i = 0; i < g[true_root].size(); i++) {
        build_cd(g[true_root][i], true_root);
    }

    for (int i = 0; i < n; i++) {
        if (i == true_root) {
            cout << 0 << " ";
        } else {
            cout << new_batya[i] + 1 << " ";
        }
    }
    cout << endl;

    return 0;
}
