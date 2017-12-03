#include <bits/stdc++.h>

using namespace std;

int n, root, ways_count;
vector<bool> used;
vector<int> grasses, depth, batya, s, place, place_in_way;
vector<vector<int> > g, dp, hld;
vector<vector< int>  > segment_trees;

int dfs(int cur_v, int dep, int prev_v) {

    used[cur_v] = true;
    depth[cur_v] = dep;
    batya[cur_v] = prev_v;

    int sum = 0;

    for (int i = 0; i < g[cur_v].size(); i++) {
        if (!used[g[cur_v][i]]) {
            sum += dfs(g[cur_v][i], dep + 1, cur_v);
        }
    }

    sum += 1;
    s[cur_v] = sum;

    return sum;
}

void prep_lca() {

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

    if (depth[u] > depth[v]) {
        swap(u, v);
    }

    int log = 19;
    for (int i = log - 1; i >= 0; i--) {
        if (depth[dp[v][i]] >= depth[u]) {
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

void prep_hld(int cur_v) {
    //cout << "prep_hld; cur_v = " << cur_v << endl;
    used[cur_v] = true;
    int cur_way = ways_count;
    ways_count++;
    hld.resize(ways_count);
    hld[cur_way].push_back(cur_v);
    place[cur_v] = cur_way;
    place_in_way[cur_v] = hld[cur_way].size() - 1;

    int new_cur_v = 0;
    while(new_cur_v != -1) {
        //cout << "while: cur_v = " << cur_v << endl;
        new_cur_v = -1;
        for (int i = 0; i < g[cur_v].size(); i++) {
            if (!used[g[cur_v][i]]) {
                if (s[g[cur_v][i]] >= ((s[cur_v] + 1) / 2)) {
                    new_cur_v = g[cur_v][i];
                } else {
                    prep_hld(g[cur_v][i]);
                }
            }
        }

        if (new_cur_v != -1) {
            cur_v = new_cur_v;
            hld[cur_way].push_back(cur_v);
            place[cur_v] = cur_way;
            place_in_way[cur_v] = hld[cur_way].size() - 1;
            used[cur_v] = true;
        }
    }
}

void build(int cur_way, int cur_v, int tl, int tr) {
    if (tl == tr) {
        segment_trees[cur_way][cur_v] = 0;
        //segment_trees[cur_way][cur_v].second = 0;
    } else {
        int tm = (tl + tr) / 2;
        build(cur_way, cur_v * 2 + 1, tl, tm);
        build(cur_way, cur_v * 2 + 2, tm + 1, tr);
        segment_trees[cur_way][cur_v] = 0;
        //segment_trees[cur_way][cur_v].second = 0;
    }
}

void prep_segment_trees() {
    //hld[0].pop_front();

    for (int i = 0; i < ways_count; i++) {
        //cout << " i = " << i << endl;
        segment_trees[i].resize(hld[i].size() * 4);
        build(i, 0, 0, hld[i].size() - 1);
    }
}

void push(int cur_way, int cur_v) {
    //cout << "run push" << endl;
    //cout << "run" << endl;
    if (cur_v * 2 + 2 >= segment_trees[cur_way].size()) {
        return;
    }
    if (segment_trees[cur_way][cur_v] != 0) {
        /*segment_trees[cur_way][cur_v *2 + 1].second += segment_trees[cur_way][cur_v].second;
        segment_trees[cur_way][cur_v *2 + 2].second += segment_trees[cur_way][cur_v].second;
        segment_trees[cur_way][cur_v].first += segment_trees[cur_way][cur_v].second;
        segment_trees[cur_way][cur_v].second = 0;*/
        segment_trees[cur_way][cur_v * 2 + 1] += segment_trees[cur_way][cur_v];
        segment_trees[cur_way][cur_v * 2 + 2] += segment_trees[cur_way][cur_v];
        segment_trees[cur_way][cur_v] = 0;
    }
    /*cout << "now tree: " ;
    for (int i = 0; i < segment_trees[cur_way].size(); i++) {
        cout << segment_trees[cur_way][i] << " ";
    }
    cout << endl;*/
}

void upd(int cur_way, int cur_v, int tl, int tr, int l, int r, int new_add) {
    //cout << "start upd" << endl;
    if (l > r) {
        //cout << "run2" << endl;
        return;
    }

    if (l == tl && r == tr) {
        //cout << "run 3" << endl;
        segment_trees[cur_way][cur_v] += new_add;
    } else {
        //cout << "run4" << endl;
        push(cur_way, cur_v);
        int tm = (tl + tr) / 2;
        upd(cur_way, cur_v*2 + 1, tl, tm, l, min(r, tm), new_add);
        upd(cur_way, cur_v*2 + 2, tm + 1, tr, max(l, tm + 1), r, new_add);
    }
}

int sum(int cur_way, int cur_v, int tl, int tr, int l, int r) {
    //cout << "run sum" << endl;
    if (l > r) {
        return 0;
    }

    if (l == tl && r == tr) {
        return segment_trees[cur_way][cur_v];
    }
    push(cur_way, cur_v);
    int tm = (tl + tr) / 2;
    return sum(cur_way, cur_v * 2 + 1, tl, tm, l, min(r, tm)) + sum(cur_way, cur_v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
}

int calc(int u, int v) {
    int deepest = (depth[u] > depth[v]) ? u : v;
    //cout << "run culc; deepest == " << deepest << endl;
   // cout << "tl = 0; tr = " <<  hld[place[deepest]].size() - 1 << endl;
    //cout << "place_in_way[deepest] = " << place_in_way[deepest] << endl;
    return sum(place[deepest], 0, 0, hld[place[deepest]].size() - 1, place_in_way[deepest], place_in_way[deepest]);
}

void modify(int u, int v) {

    int l = lca(u, v);
    if (l == u || l == v) {
        int deepest = (depth[u] > depth[v]) ? u : v;
        int up = (depth[u] < depth[v]) ? u : v;
        while(place[deepest] != place[up]) {
            int temp_l = hld[place[deepest]][0];
            upd(place[deepest], 0, 0, hld[place[deepest]].size() - 1, place_in_way[temp_l], place_in_way[deepest], 1);
            deepest = batya[temp_l];
        }

        if (deepest == up) {
            return;
        } else {
            //cout << "place_in_way[up] + 1 == " << place_in_way[deepest] << endl;
            //cout << "hld[place[deepest]].size() - 1 = " << hld[place[deepest]].size() - 1 << endl;
            //cout << "place_in_way[up] + 1 = " << place_in_way[up] + 1 << endl;
            //cout << "place_in_way[deepest] = " << place_in_way[deepest] << endl;
            upd(place[deepest], 0, 0, hld[place[deepest]].size() - 1, place_in_way[up] + 1, place_in_way[deepest], 1);
        }
    } else {

        while(place[u] != place[l]) {
            int temp_l = hld[place[u]][0];
            upd(place[u], 0, 0, hld[place[u]].size() - 1, place_in_way[temp_l], place_in_way[u], 1);
            u = batya[temp_l];
        }

        while(place[v] != place[l]) {
            int temp_l = hld[place[v]][0];
            upd(place[v], 0, 0, hld[place[v]].size() - 1, place_in_way[temp_l], place_in_way[v], 1);
            v = batya[temp_l];
        }

        int deepest = (depth[u] > depth[v]) ? u : v;
        upd(place[deepest], 0, 0, hld[place[deepest]].size() - 1, place_in_way[l] + 1, place_in_way[deepest], 1);
    }

}


int main() {


    //ifstream fin("smth2.in");

    int m, a, b;
    cin >> n >> m;

    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    root = rand() % n;
    //root = 4;

    batya.resize(n);
    depth.resize(n);
    s.resize(n);
    used.assign(n, false);

    dfs(root, 0, root);
    //cout << "root = " << root << endl;
    prep_lca();

    place.resize(n);
    place_in_way.resize(n);
    ways_count = 0;
    used.clear();
    used.assign(n, false);

    prep_hld(root);
    /*cout << "hld: " << endl;
    for (int i = 0; i < ways_count; i++) {
        for (int j = 0; j < hld[i].size(); j++) {
            cout << hld[i][j] << " ";
        }
        cout << endl;
    }*/

    segment_trees.resize(ways_count);

    /*cout << "place: ";
    for (int i = 0; i < n; i++) {
        cout << place[i] << " ";
    }
    cout << endl;*/

    prep_segment_trees();
    char sign;
    for (int i = 0; i < m; i++) {
        cin >> sign >> a >> b;
        if (sign == 'P') {
            modify(a - 1, b - 1);
            /*cout << "modify: a - 1 = " << a - 1 << "; b - 1 = " << b - 1 << endl;
            cout << "segment_trees: " << endl;
            for (int i = 0; i < ways_count; i++) {
                for (int j = 0; j < segment_trees[i].size(); j++) {
                    cout << segment_trees[i][j] << " ";
                }
                cout << endl;
            }*/
        } else {
            cout << calc(a - 1, b - 1) << endl;
        }
    }

    return 0;
}
