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
vector<bool> used, used_vert;
vector<int> result;

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
        pair<int, int> next = g[cur_v][i];
        if (next.first < n && next.second < 2 * m && tubes[next.second].reversed < 2 * m) {
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

void dfs1(int cur_v)
{
	used[cur_v] = true;
	cout << cur_v + 1 << " ";
	if (cur_v == t - 1)
		return;
	for (int i = 0; i < g[cur_v].size(); i++)
	{
	    pair<int, int> next = g[cur_v][i];
		if (tubes[next.second].f == 1 && !used[next.first])
		{
			tubes[g[cur_v][i].second].f = 0;
			dfs1(next.first);
			return;
		}
	}
}

int main()
{
   freopen("snails.in", "r", stdin);
	freopen("snails.out", "w", stdout);

    int a, b;
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
        //cout << "run while iteration" << endl;
        used.assign(n, false);
        int del = dfs(s - 1, INT_MAX);
        if (del == 0) {
            break;
        }
        ans += del;
    }

    if (ans < 2) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    used.assign(n, false);
    dfs1(s - 1);
    cout << '\n';
    used.assign(n, false);
    dfs1(s - 1);
    cout << '\n';

    return 0;
}
