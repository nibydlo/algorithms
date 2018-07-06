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

vector<vector<pair<int, int> > > g;
vector<Edge> edges;
vector<vector<char> > table;
int n, m, s, t, verts_count;
map<int, pair<int, int> > num_to_coor;

void add_edge(int a, int b, int c) {

	Edge edge = * new Edge(a, b, c, edges.size(), edges.size() + 1);
	edges.push_back(edge);
	g[a].push_back(make_pair(b, edge.id));
	edge = edge.reverse();
	edges.push_back(edge);
	g[b].push_back(make_pair(a, edge.id));
}

int main() {

	cin >> n >> m;
	table.resize(n);
	for (int i = 0; i < n; i++) {
		table[i].resize(m);
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}

	verts_count = 2 + (n + m - 1)*2;
	edges.resize(verts_count);

	//add edges from source
	for (int i = 0; i < n + m - 1; i++) {
		add_edge(0, i + 1, 1);
	}

	//first case when engle is white;
	char true_color = 'W';

	//add edges between diags
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (((i + j) % 2) == 0 && table[i][j] != true_color) {
				add_edge(i + j, i - j + m)
			}
		}
	}

	return 0;
}
