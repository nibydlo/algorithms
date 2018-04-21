#include <bits/stdc++.h>
using namespace std;



class Edge{
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

vector<int> q, depth;
vector<Edge> edges;
vector<vector<pair<int, int> > > g;
vector<bool> used;
vector<int> ptr, scores;
vector<vector<char> > table;
int n,  m, s, t;
map<pair<int, int>, int> pair_to_num;


int edge_count;
bool bfs() {
	depth.assign(edge_count, -1);
	int head = 0, tail = 0;
	q[tail++] = s - 1;
	depth[s - 1] = 0;


	while (head < tail && depth[t - 1] == -1) {
		int next_vert = q[head++];
		for (int i = 0; i < g[next_vert].size(); i++) {
			int to = g[next_vert][i].first;
			int id = g[next_vert][i].second;
			if (depth[to] == -1 && edges[id].f < edges[id].c) {
				q[tail++] = to;
				depth[to] = depth[next_vert] + 1;
			}
		}
	}
	return depth[t - 1] != -1;
}

void add_edge(int a, int b, int c) {

	Edge edge = * new Edge(a, b, c, edges.size(), edges.size() + 1);
	edges.push_back(edge);
	g[a].push_back(make_pair(b, edge.id));
	edge = edge.reverse();
	edges.push_back(edge);
	g[b].push_back(make_pair(a, edge.id));
}

int dfs(int cur_v, int max_flow) {
//	cout << "run dfs cur_v = " << cur_v << endl;
	if (max_flow == 0) {
		return max_flow;
	}
	used[cur_v] = true;
	if (cur_v == t - 1) {
		return max_flow;
	}

	for (;ptr[cur_v]<g[cur_v].size(); ++ptr[cur_v]) {
		pair<int, int> next = g[cur_v][ptr[cur_v]];
		if (!used[next.first] && edges[next.second].c - edges[next.second].f > 0) {
		//	cout << "go next.first = " << next.first << " next.second = " << next.second << endl;
			if (depth[next.first] != depth[cur_v] + 1) {
				continue;
			}
			int d = dfs(next.first, min(max_flow, edges[next.second].c - edges[next.second].f));
			if (d > 0) {
			//	cout << "run if" << endl;
				edges[next.second].f += d;
				edges[edges[next.second].reversed].f -= d;
				return d;
			}
		}
	}

	return 0;
}



int main() {

	cin >> n;

	edge_count = 2 + n + n*(n -1)/2;
	q.resize(edge_count);
	scores.resize(n);
	table.resize(n);
	for (int i = 0; i < n; i++) {
		table[i].resize(n);
		for (int j = 0; j < n; j++) {
			cin >> table[i][j];
		}
	}
	for (int i = 0; i < scores.size(); i++) {
		cin >> scores[i];
	}

	g.resize(2 + n + n*(n - 1)/2);

	s = 1;
	t = 2 + n + (n*(n - 1)/2);

	//edges from source;
	for (int i = 0; i < n; i++) {
		add_edge(0, i + 1, scores[i]);
	}


	//creating pair to num;
	int iter = 1 + n;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			pair_to_num.insert(make_pair(make_pair(i, j), iter++));
		}
	}


	//edges between teams ans games
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				//cout << "i = " << i << " j = " << j << endl;
				int cc = 3;
				if (table[i][j] == 'w') {
					cc = 2;
				}
				if (table[i][j] == 'l') {
					cc = 1;
				}
				if (table[i][j] == 'L') {
					cc = 0;
				}
				int ii = i, jj = j;

				if (jj < ii) {
					swap(ii, jj);
				}
				//cout << "ii = " << ii << "jj = " << jj << " num = ";
				//cout << pair_to_num[make_pair(ii, jj)] << endl;
				add_edge(i + 1, pair_to_num[make_pair(ii, jj)], cc);
			}
		}
	}


	//edges to terminal;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			add_edge(pair_to_num[make_pair(i, j)], t - 1, 3);
		}
	}

	/*cout << "edges: " << endl;
	for (int i = 0; i < edges.size(); i++) {
		Edge e = edges[i];
		cout << "id = " << e.id << " from = " << e.from << " to = " << e.to << " c = " << e.c << " f = " << e.f << endl;
	}

	cout << "here" << endl;*/


	int ans = 0;
	while(true) {
		ptr.assign(edge_count, 0);

		q.clear();
		if (!bfs()) {
			break;
		}

		used.assign(edge_count, false);
		int ans_mem = ans;
		int del = dfs(s - 1, INT_MAX);
		while (del != 0) {
			used.assign(n, false);
			ans += del;
			del = dfs(s - 1, INT_MAX);
		}
	}

	/*cout << "g: " << endl;
	for (int i = 0; i < g.size(); i++) {
		for (int j = 0; j < g[i].size(); j++) {
			cout << "(" << g[i][j].first << ", " << g[i][j].second << ") ";
		}
		cout << endl;
	}*/

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//cout << " i = " << i << " j = " << j << endl;
			if (table[i][j] != '.') {
				cout << table[i][j];
			} else {
				int ii = min(i, j);
				int jj = max(i, j);
				int num = pair_to_num[make_pair(ii, jj)];
				int game_res = -1;
				for (int k = 0; k < g[num].size(); k++) {
				//	cout << "key is" << edges[g[num][k].second].to << " i + 1 = " << i + 1 << endl;
					if (edges[g[num][k].second].to == i + 1) {

						game_res = -edges[g[num][k].second].f;
						break;
					}
				}
				if (game_res == 0) {
					cout << 'L';
				} else if (game_res == 1) {
					cout << 'l';
				} else if (game_res == 2) {
					cout << 'w';
				} else if (game_res == 3) {
					cout << 'W';
				} else {
					cout << "nf num is" << num;
				}
				//cout << endl;
			}
		}
		cout << endl;
	}

	return 0;
}
