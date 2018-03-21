#include <bits/stdc++.h>

using namespace std;

class Tube
{
public:
    int id, from, to, f, c, reversed;

    Tube() {}

    Tube(int from, int to, int c, int id, int reversed)
    {
        this->id = id;
        this->from = from;
        this->to = to;
        this->f = 0;
        this->c = c;
        this->reversed = reversed;
    }

    Tube reverse()
    {
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
    //cout << "run dfs cur_v = " << cur_v << endl;
    if (used[cur_v])
    {
        return 0;
    }
    used[cur_v] = true;
    if (cur_v == t - 1)
    {
        return max_flow;
    }

    for (int i = 0; i < g[cur_v].size(); i++)
    {
        pair<int, int> next = g[cur_v][i];

            if (!used[next.first] && tubes[next.second].c - tubes[next.second].f > 0)
            {
                int d = dfs(next.first, min(max_flow, tubes[next.second].c - tubes[next.second].f));
                if (d > 0)
                {
                    tubes[next.second].f += d;
                    tubes[tubes[next.second].reversed].f -= d;
                    return d;
                }
            }

    }

    return 0;
}

int main()
{
    int a, b, c;
    cin >> n >> m;
    s = 1;
    t = n + m + 2;
    g.resize(n + m + 2);
    tubes.resize(0);

    for (int i = 0; i < n; i++)
    {
        cin >> c;
        while (c != 0)
        {

            Tube tempTube = * new Tube(i + 1, c + n, 1, tubes.size(), tubes.size() + 1);
            tubes.push_back(tempTube);
            g[i + 1].push_back(make_pair(c + n, tempTube.id));
            tempTube = tempTube.reverse();
            tubes.push_back(tempTube);
            g[n + c].push_back(make_pair(i + 1, tempTube.id));
            cin >> c;
        }
    }


    for (int i = 0; i < n; i++)
    {
        Tube tempTube = * new Tube(0, i + 1, 1, tubes.size(), tubes.size() + 1);
        tubes.push_back(tempTube);
        g[0].push_back(make_pair(i + 1, tempTube.id));
        tempTube = tempTube.reverse();
        tubes.push_back(tempTube);
        g[i + 1].push_back(make_pair(0, tempTube.id));
    }

    for (int i = 0; i < m; i++) {
        Tube tempTube = * new Tube(n + 1 + i, n + m + 1, 1, tubes.size(), tubes.size() + 1);
        tubes.push_back(tempTube);
        g[n + 1 + i].push_back(make_pair(n + m + 1, tempTube.id));
        tempTube = tempTube.reverse();
        tubes.push_back(tempTube);
        g[n + m + 1].push_back(make_pair(n + 1 + i, tempTube.id));
    }

    /*cout << "tubes: " << endl;
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

    while (true)
    {
        //cout << "run loop" << endl;
        used.assign(n + m + 2, false);
        int del = dfs(s - 1, INT_MAX);
        if (del == 0)
        {
            break;
        }
        ans += del;
    }

    cout << ans << endl;

    for (int i = 0; i < tubes.size(); i++) {
        if (tubes[i].f == 1 && tubes[i].from != 0 && tubes[i].to != n + m + 1) {
            cout << tubes[i].from << " " << tubes[i].to - n << endl;
        }
    }

    return 0;
}

