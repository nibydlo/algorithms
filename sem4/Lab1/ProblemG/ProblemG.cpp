#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
	int id, from, to, f, c, reversed;

	Edge() {}

	Edge(int from, int to, int c, int id, int reversed) {
		this->id = id;
          this->from = from;
          this->to = to;
          this->f = 0;
          this->c = c;
          this->reversed = reversed;
	}

	Edge reverse() {
		return * new Edge(to, from, 0, reversed, id);
	}
};

vector<Edge> edges;
vector<vector<pair<int, int> > > g;
vector<bool> used, lef;
vector<vector<char> > field;
bool fail_flag = false;
map<int, pair<int, int> > id_to_coor;
set<int> deleted_id, did;

int n, m, s, t;

int dfs(int cur_v, int max_flow) {

	if (used[cur_v]) {
		return 0;
	}
	used[cur_v] = true;
	if (cur_v == t) {
		return max_flow;
	}

	for (int i = 0; i < g[cur_v].size(); i++) {
		pair<int, int> next = g[cur_v][i];
		if (!used[next.first] && edges[next.second].c - edges[next.second].f > 0) {
			int d = dfs(next.first, min(max_flow, edges[next.second].c - edges[next.second].f));
			if (d > 0) {
				edges[next.second].f += d;
				edges[edges[next.second].reversed].f -= d;
				return d;
			}
		}
	}

	return 0;
}

void dfs1_5(int cur_v) {
    //cout << "run dfs1.5 cur_v = " << cur_v << endl;
	if (cur_v == t) {
		fail_flag = true;
	}

    if (lef[cur_v]) {
        return;
    }

    lef[cur_v] = true;
    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];
        if (!lef[next.first] && edges[next.second].c - edges[next.second].f > 0) {
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
        if (edges[next.second].c - edges[next.second].f == 0 && edges[next.second].c != 0 && !lef[edges[next.second].to]) {
            deleted_id.insert(next.second);
        }
    }

    for (int i = 0; i < g[cur_v].size(); i++) {
        pair<int, int> next = g[cur_v][i];
        if (!used[next.first] && edges[next.second].c - edges[next.second].f > 0) {
            dfs2(next.first);
        }
    }
}

int main() {

	char sign;
	cin >> n >> m;
	field.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> sign;
			field[i].push_back(sign);
		}
	}

	g.resize(n*m*2);

	for (int i = 0; i < n; i++) {
		for (int j = 0;j < m; j++) {

			if (field[i][j] == 'A') {
				s =  n*m + m*i + j;
			}

			if (field[i][j] == 'B') {
				t = m*i + j;
			}

			int cc;
			if (field[i][j] == '.') {
				cc = 1;
			} else if (field[i][j] == '#') {
				cc = 0;
			} else {
				cc = INT_MAX;
			}

			int enter_id = m*i + j;
			int exit_id = n*m + m*i + j;

			id_to_coor.insert(make_pair(edges.size(), make_pair(i, j)));
			//cout << "run inser key = " << edges.size() << " i = " << i << " j = " << j << endl;
			//adding inner edge
			Edge temp_edge = * new Edge(enter_id, exit_id, cc, edges.size(), edges.size() + 1);
			edges.push_back(temp_edge);
			g[enter_id].push_back(make_pair(exit_id, temp_edge.id));

			temp_edge = temp_edge.reverse();
			edges.push_back(temp_edge);
			g[exit_id].push_back(make_pair(enter_id, temp_edge.id));

			//adding edge to upper neighbour
			if (i != 0) {
			///	cout << "run1" << endl;
				temp_edge = * new Edge(exit_id, m*(i - 1) + j, INT_MAX, edges.size(), edges.size() + 1);
				edges.push_back(temp_edge);
				g[exit_id].push_back(make_pair(m*(i - 1) + j, temp_edge.id));

				temp_edge = temp_edge.reverse();
				edges.push_back(temp_edge);
				g[m*(i - 1) + j].push_back(make_pair(exit_id, temp_edge.id));
			}

			//adding edge to lower neighbour
			if (i != n - 1) {
			//	cout << "run2" << endl;
				temp_edge = * new Edge(exit_id, m*(i + 1) + j, INT_MAX, edges.size(), edges.size() + 1);
				edges.push_back(temp_edge);
				g[exit_id].push_back(make_pair(m*(i + 1) + j, temp_edge.id));

				temp_edge = temp_edge.reverse();
				edges.push_back(temp_edge);
				g[m*(i + 1) + j].push_back(make_pair(exit_id, temp_edge.id));
			}

			//adding edge to left neighbour
			if (j != 0) {
			//	cout << "run3" << endl;
				temp_edge = * new Edge(exit_id, m*i + j - 1, INT_MAX, edges.size(), edges.size() + 1);
				edges.push_back(temp_edge);
				g[exit_id].push_back(make_pair(m*i + j - 1, temp_edge.id));

				temp_edge = temp_edge.reverse();
				edges.push_back(temp_edge);
				g[m*i + j - 1].push_back(make_pair(exit_id, temp_edge.id));
			}

			//adding edge to right neighbour
			if (j != m - 1) {
			//	cout << "run4" << endl;
				temp_edge = * new Edge(exit_id, m*i + j + 1, INT_MAX, edges.size(), edges.size() + 1);
				edges.push_back(temp_edge);
				g[exit_id].push_back(make_pair(m*i + j + 1, temp_edge.id));

				temp_edge = temp_edge.reverse();
				edges.push_back(temp_edge);
				g[m*i + j + 1].push_back(make_pair(exit_id, temp_edge.id));
			}
		}
	}



	int ans = 0;
	while(true) {
		used.assign(n*m*2, false);
		int del = dfs(s, INT_MAX);
		if (del == 0) {
			break;
		}
		ans += del;
	}

	/*cout << "edges.size = " << edges.size() << endl;
	cout << "edges: " << endl;
	for (int i = 0; i < edges.size(); i++) {
	    Edge e = edges[i];
	    cout << "from = " <<  e.from << "  to = " << e.to << "  c = " << e.c << "  f = " << e.f << "  id = " << e.id << "  reversed = " << e.reversed<< endl;
    }*/


	/*for (int i = 0; i < g.size(); i++) {
         for (int j = 0; j < g[i].size(); j++) {
             cout << " ( " << g[i][j].first << " " << g[i][j].second << " ) ";
         }
         cout << endl;
    }*/

	lef.assign(n*m*2, false);
	dfs1_5(s);

	used.assign(n*m*2, false);
	dfs2(s);
	/*for (set<int>::iterator it = deleted_id.begin(); it != deleted_id.end(); ++it) {
		did.insert(*it/2);
	}*/

	//check
	for (set<int>::iterator it = deleted_id.begin(); it != deleted_id.end(); ++it) {
		if(edges[*it].c > 100000) {
			//cout << "id = " << *it << endl;
			cout << "-1" << endl;
			return 0;
		}
	}

	cout << deleted_id.size() << endl;
	for (set<int>::iterator it = deleted_id.begin(); it != deleted_id.end(); ++it) {
		//cout << "*it = " << *it << endl;
		//cout << "( " << id_to_coor[*it].first << ", " << id_to_coor[*it].second << ")" << endl;
		field[id_to_coor[*it].first][id_to_coor[*it].second] = '+';
	}

	for (int i = 0; i < field.size(); i++) {
		for (int j = 0; j < field[i].size(); j++) {
			cout << field[i][j];
		}
		cout << endl;
	}
}
