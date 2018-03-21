#include <bits/stdc++.h>

using namespace std;

class Tube
{
public:
    int id, from, to, f, c, reversed;

    Tube(){}

    Tube(int from, int to, int c, int id, int reversed)
    {
        this->id = id;
        this->from = from;
        this->to = to;
        this->f = 0;
        this->c = c;
        this->reversed = reversed;
    }

    Tube reverse() {
        return * new Tube(to, from, c, reversed, id);
    }
};

vector<Tube> tubes;
vector<vector<pair<int, int> > > g;
vector<bool> used;

int n, m;

int dfs(int cur_v, int max_flow)
{
    if (used[cur_v]) {
        return 0;
    }
    used[cur_v] = true;
    if (cur_v == n - 1) {
        return max_flow;
    }

    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];

        if (!used[next.first] && tubes[next.second].c - tubes[next.second].f > 0) {
            int d = dfs(next.first, min(max_flow, tubes[next.second].c - tubes[next.second].f));
            if (d > 0) {
                tubes[next.second].f += d;
                tubes[tubes[next.second].reversed].f -= d;
                return d;
            }
        }
    }

    return 0;
}


vector<bool> lef;
set<int> dVerts, deleted_id, did;

void dfs1_5(int cur_v) {
    //cout << "run dfs1.5 cur_v = " << cur_v << endl;
    if (lef[cur_v]) {
        return;
    }

    lef[cur_v] = true;
    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];
        if (!lef[next.first] && tubes[next.second].c - tubes[next.second].f > 0) {
            dfs1_5(next.first);
        }
    }
}

void dfs2(int cur_v) {
    //cout << "run df2 cur_v = " << cur_v << endl;
    if (used[cur_v]) {
        return;
    }

    used[cur_v] = true;
    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];
        if (tubes[next.second].c - tubes[next.second].f == 0 && !lef[tubes[next.second].to]) {
            deleted_id.insert(next.second);
        }
    }

    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];
        if (!used[next.first] && tubes[next.second].c - tubes[next.second].f > 0) {
            dfs2(next.first);
        }
    }
}

int main()
{

    ifstream cin("cut.in");
    ofstream cout("cut.out");

    int a, b, c;
    cin >> n;
    cin >> m;
    g.resize(n);
    tubes.resize(0);
//g size is n
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;

        Tube tempTube = * new Tube(a - 1, b - 1, c, tubes.size(), tubes.size() + 1);
        tubes.push_back(tempTube);
        g[a - 1].push_back(make_pair(b - 1, tempTube.id));
        tempTube = tempTube.reverse();
        tubes.push_back(tempTube);
        g[b - 1].push_back(make_pair(a - 1, tempTube.id));
    }
//tubes size is 2*m

    /*cout << "tubes.size = " << tubes.size() << endl;
    cout << "tubes: " << endl;
    for (int i = 0; i < tubes.size(); i++) {
        Tube e = tubes[i];
        cout << "from = " <<  e.from << "  to = " << e.to << "  c = " << e.c << "  f = " << e.f << "  id = " << e.id << "  reversed = " << e.reversed<< endl;
    }

    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            cout << " ( " << g[i][j].first << " " << g[i][j].second << " ) ";
        }
        cout << endl;
    }*/

    int ans = 0;
    while (true) {
        //cout << "run while iteration" << endl;
        used.assign(n, false);
        int del = dfs(0, INT_MAX);
        if (del == 0) {
            break;
        }
        ans += del;
    }

    lef.assign(n, false);
    dfs1_5(0);

    used.assign(n, false);
    dfs2(0);
    for (set<int>::iterator it = deleted_id.begin(); it != deleted_id.end(); ++it) {
           // cout << "huy" << endl;
        //cout << "deleted is " << *it << endl;
        did.insert(*it / 2);
    }

    cout << deleted_id.size() << " " << ans << endl;

    /*for (int i = 0; i < tubes.size(); i += 2) {
        cout << tubes[i].f << endl;
    }*/

    for (set<int>::iterator it = did.begin(); it != did.end(); ++it) {

        cout << *it + 1 << " ";
    }

//    cin.close();
 //   cout.close();

    return 0;
}
