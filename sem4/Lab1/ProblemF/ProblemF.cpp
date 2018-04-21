#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
	int id, from, to, f, c, reversed;
	double time;

	Edge() {}

	Edge(int from, int to, int c, int id, int reversed, double time) {
		this->id = id;
		this->time = time;
		this->from = from;
		this->to = to;
		this->f = 0;
		this->c = c;
		this->reversed = reversed;
	}

	Edge reverse() {
		return * new Edge(to, from, 0, reversed, id, time);
	}
};

class Thing {
public:
	int num;
	double x, y, speed;

	Thing() {}

	Thing(int num, double x, double y, double speed) {
		this->num = num;
		this->x = x;
		this->y = y;
		this->speed = speed;
	}
};

class Destination {
public:
	int num;
	double x, y;

	Destination() {}

	Destination(int num, double x, double y) {
		this->num = num;
		this->x = x;
		this->y = y;
	}
};

vector<Edge> edges;
vector<double> times;
vector<Thing> things;
vector<Destination> destinations;
vector<vector<pair<int, int> > > g;
vector<bool> used;

int n, s, t;

int dfs(int cur_v, int max_flow, double time_limit) {
	//cout << "run dfs cur_v = " << cur_v << "  max_flow = " << max_flow << "  time limit = " << time_limit << endl;
	if (used[cur_v]) {
		return 0;
	}
	used[cur_v] = true;
	if (cur_v == t - 1) {
		return max_flow;
	}

	for (int i = 0; i < g[cur_v].size(); i++) {
		pair<int, int> next = g[cur_v][i];

		if (!used[next.first] && edges[next.second].time <= time_limit && edges[next.second].c - edges[next.second].f > 0) {
			//cout << "go" << endl;
			int d = dfs(next.first, min(max_flow, edges[next.second].c - edges[next.second].f), time_limit);
			if (d > 0) {
				edges[next.second].f += d;
				edges[edges[next.second].reversed].f -= d;
				return d;
			}
		}
	}

	return 0;
}

bool comp(Edge a, Edge b) {
	return a.time < b.time;
}

int main() {

	cin >> n;
	s = 1;
	t = n + n + 2;
	g.resize(n + n + 2);
	edges.resize(0);
	things.resize(0);
	destinations.resize(0);

	int x, y, speed;
	//read things
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> speed;
		things.push_back(Thing(i + 1, x, y, speed));
	}

	//read destinations
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		destinations.push_back(Destination(n + i + 1, x, y));
	}

	//build edges between things and destinations
	//cout << "run" << endl;
	for (Thing thing : things) {
		for (Destination destination : destinations) {

			double dx = destination.x - thing.x;
			double dy = destination.y - thing.y;
			double time = sqrt(dx*dx + dy*dy)/thing.speed;
			times.push_back(time);
			Edge edge = * new Edge(thing.num, destination.num,  1, edges.size(), edges.size() + 1, time);
			edges.push_back(edge);
			g[thing.num].push_back(make_pair(destination.num, edge.id));

			edge = edge.reverse();
			edges.push_back(edge);
			g[destination.num].push_back(make_pair(thing.num, edge.id));
		}
	}

	//build edges from source to things
	for (Thing thing : things) {

		Edge edge = * new Edge(0, thing.num, 1, edges.size(), edges.size() + 1, 0);
		edges.push_back(edge);
		g[0].push_back(make_pair(thing.num, edge.id));

		edge = edge.reverse();
		edges.push_back(edge);
		g[thing.num].push_back(make_pair(0, edge.id));
	}

	//build edges from desinations to terminal
	for (Destination destination : destinations) {

		Edge edge = * new  Edge(destination.num, n + n + 1, 1, edges.size(), edges.size() + 1, 0);
		edges.push_back(edge);
		g[destination.num].push_back(make_pair(n + n + 1, edge.id));

		edge = edge.reverse();
		edges.push_back(edge);
		g[n + n + 1].push_back(make_pair(destination.num, edge.id));
	}

	times.push_back(0);
	//sorting edges by time
	sort(times.begin(), times.end());

	/*cout << "times: " << endl;
	for (int i = 0; i < times.size(); i++) {
		cout << times[i] << " ";
	}
	cout << endl;

	cout << "tubes: " << endl;
     for (int i = 0; i < edges.size(); i++) {
         Edge e = edges[i];
         cout << "from = " <<  e.from << "  to = " << e.to << "  c = " << e.c << "  f = " << e.f << "  id = " << e.id << "  reversed = " << e.reversed << "  time = " << e.time << endl;
     }


	for (int i = 0; i < g.size(); i++) {
         for (int j = 0; j < g[i].size(); j++) {
             cout << " ( " << g[i][j].first << " " << g[i][j].second << " ) ";
         }
         cout << endl;
    }*/

	//start binsearch
	int l = -1;
	int r = times.size();
	while (l < r - 1) {
		int m = (l + r) / 2;
		double mtime = times[m];
		//cout << "m = " << m << "   mtime = " << mtime << endl;
		int ans = 0;

		for (int i = 0; i < edges.size(); i++) {
			edges[i].f = 0;
		}

	     while (true)
	     {
			//cout << "run inner while" << endl;
	         used.assign(n + n + 2, false);
	         int del = dfs(s - 1, INT_MAX, mtime);
		   /* cout << "tubes: " << endl;
	         for (int i = 0; i < edges.size(); i++) {
	             Edge e = edges[i];
	             cout << "from = " <<  e.from << "  to = " << e.to << "  c = " << e.c << "  f = " << e.f << "  id = " << e.id << "  reversed = " << e.reversed << "  time = " << e.time << endl;
		   }*/
	         if (del == 0)
	         {
	             break;
	         }
	         ans += del;
	     }
		//cout << "ans is" << ans << endl;
		if (ans == n) {
			r = m;
		} else {
			l = m;
		}
	}
	cout << times[r] << endl;

	return 0;
}
