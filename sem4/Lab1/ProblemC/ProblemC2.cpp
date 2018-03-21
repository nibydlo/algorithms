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
        return * new Tube(to, from, 0, reversed, id);
    }
};

vector<Tube> tubes;
vector<vector<pair<int, int> > > g;
vector<bool> used;

int n, m, s, t;

int dfs(int cur_v, int max_flow)
{
    if (cur_v < n && used[cur_v]) {
        return 0;
    }
    used[cur_v] = true;
    if (cur_v == t - 1) {
        return max_flow;
    }

    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next;
        if (cur_v < n && i < g[cur_v].size()) {
            next = g[cur_v][i];
        }
        if (next.first < n && next.second < 2 * m && tubes[next.second].reversed < 2* m) {
            if (!used[next.first] && tubes[next.second].c - tubes[next.second].f > 0) {
                int d = dfs(next.first, min(max_flow, tubes[next.second].c - tubes[next.second].f));
                if (d > 0) {
                    tubes[next.second].f += d;
                    tubes[tubes[next.second].reversed].f -= d;
                    return d;
                }
            }
        }
    }

    return 0;
}

int main()
{
    //ifstream cin("flow.in");
    //ofstream cout("flow.out");

    int a, b, c;
    cin >> n >> m >> s >> t;
    g.resize(n);
    tubes.resize(0);

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;

        Tube tempTube = * new Tube(a - 1, b - 1, 1, tubes.size(), tubes.size() + 1);
        tubes.push_back(tempTube);
        g[a - 1].push_back(make_pair(b - 1, tempTube.id));
        tempTube = tempTube.reverse();
        tubes.push_back(tempTube);
        g[b - 1].push_back(make_pair(a - 1, tempTube.id));
    }

    int ans = 0;
    while (true) {
        used.assign(n, false);
        int del = dfs(s - 1, INT_MAX);
        if (del == 0) {
            break;
        }
        ans += del;
    }

    cout << ans << endl;

    for (int i = 0; i < tubes.size(); i += 2) {
        cout << tubes[i].f << endl;
    }



    return 0;
}

