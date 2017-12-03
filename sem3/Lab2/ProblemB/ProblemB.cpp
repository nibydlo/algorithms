#include <bits/stdc++.h>

using namespace std;

int n, root, ways_count;
vector<bool> used;
vector<int> heights, depth, batya, s, place, place_in_way;
vector<vector<int> > g, dp, hld, segment_trees;

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
    //cout << "run build way = " << cur_way << " cur_v = " << cur_v << " tl = " << tl << " tr = " << tr << endl;
    if (tl == tr) {
        segment_trees[cur_way][cur_v] = heights[hld[cur_way][tl]];
    } else {
        int tm = (tl + tr) / 2;
        build(cur_way, cur_v * 2 + 1, tl, tm);
        build(cur_way, cur_v * 2 + 2, tm + 1, tr);
        segment_trees[cur_way][cur_v] = max(segment_trees[cur_way][cur_v * 2 + 1], segment_trees[cur_way][cur_v * 2 + 2]);
    }
}

void prep_segment_trees() {
    for (int i = 0; i < ways_count; i++) {
        segment_trees[i].resize(hld[i].size() * 4);
        build(i, 0, 0, hld[i].size() - 1);
    }
}

int sum(int cur_way, int cur_v, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }

    if (l == tl && r == tr) {
        return segment_trees[cur_way][cur_v];
    }

    int tm = (tl + tr) / 2;
    return max(sum(cur_way, cur_v * 2 + 1, tl, tm, l, min(r, tm)), sum(cur_way, cur_v * 2 + 2, tm + 1, tr, max(l, tm + 1), r));
}

void upd(int cur_way, int cur_v, int tl, int tr, int plac, int nv) {
    if (tl == tr) {
        segment_trees[cur_way][cur_v] = nv;
    } else {
        int tm = (tl + tr) / 2;
        if (plac <= tm) {
            upd(cur_way, cur_v * 2 + 1, tl, tm, plac, nv);
        } else {
            upd(cur_way, cur_v * 2 + 2, tm + 1, tr, plac, nv);
        }
        segment_trees[cur_way][cur_v] = max(segment_trees[cur_way][cur_v * 2 + 1], segment_trees[cur_way][cur_v * 2 + 2]);
    }
}

void modify(int v, int nv) {
    upd(place[v], 0, 0, hld[place[v]].size() - 1, place_in_way[v], nv);
    heights[v] = nv;
}

int calc_rope(int u, int v) {
    int l = lca(u, v);

    int ans = max(heights[u], heights[v]);
    while(place[u] != place[l]) {
        int temp_l = hld[place[u]][0];
        ans = max(sum(place[u], 0, 0, hld[place[u]].size() - 1, place_in_way[temp_l], place_in_way[u]), ans);
        u = batya[temp_l];
    }

    while(place[v] != place[l]) {
        int temp_l = hld[place[v]][0];
        ans = max(sum(place[v], 0, 0, hld[place[v]].size() - 1, place_in_way[temp_l], place_in_way[v]), ans);
        v = batya[temp_l];
    }

    int deepest = (depth[u] > depth[v]) ? u : v;
    ans = max(sum(place[deepest], 0, 0, hld[place[deepest]].size() - 1, place_in_way[l], place_in_way[deepest]), ans);

    return ans;
}

int main() {

    ifstream fin("mail.in");
    ofstream fout("mail.out");

    fin >> n;
    heights.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> heights[i];
    }

    g.resize(n);
    int u, v;
    for (int i = 0; i < n - 1; i++) {

        fin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    root = rand() % n;
    //cout << "root = " << root << endl;
    //root = 5;
    batya.resize(n);
    depth.resize(n);
    s.resize(n);
    used.assign(n, false);
    dfs(root, 0, root);

    /*cout << "s : " << endl;
    for (int i = 0; i < n; i++) {
        cout << s[i] << " ";
    }
    cout << endl;*/

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
    prep_segment_trees();

    /*cout << "segment trees: " << endl;
    for (int i = 0; i < ways_count; i++) {
        for (int j = 0; j < segment_trees[i].size(); j++) {
            cout << segment_trees[i][j] << " ";
        }
        cout << endl;
    }*/

    /*cout << "place : " << endl;
    for (int i = 0; i < n; i++) {
        cout << place[i] << " ";
    }
    cout << endl;*/

    int k, ii, h;
    char sign;
    fin >> k;
    for (int j = 0; j < k; j++) {

        fin >> sign >> ii >> h;

        if (sign == '!') {
            modify(ii - 1, h);

        /*cout << "segment trees: " << endl;
        for (int i = 0; i < ways_count; i++) {
            for (int j = 0; j < segment_trees[i].size(); j++) {
                cout << segment_trees[i][j] << " ";
            }
            cout << endl;
        }*/

        } else if (sign == '?') {
            fout << calc_rope(ii - 1, h - 1) << endl;
        }
    }

    fin.close();
    fout.close();
}
