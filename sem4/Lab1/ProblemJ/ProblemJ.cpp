#include <bits/stdc++.h>
using namespace std;

int n, w;

class Object {
public:
	int x1, x2, y1, y2;

	Object(int x1, int y1, int x2, int y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	int dist(Object o) {

		int dx, dy;
		if (this->x1 <= o.x1 && o.x1 <= this->x2
			|| this->x1 <= o.x2 && o.x2 <= this->x2
			|| o.x1 <= this->x1 && this->x1 <= o.x2
			|| o.x1 <= this->x2 && this->x2 <= o.x2)
		{
			dx = 0;
		} else {
			dx = min(abs(o.x1 - this->x2), abs(this->x1 - o.x2));
		}

		if (this->y1 <= o.y1 && o.y1 <= this->y2
			|| this->y1 <= o.y2 && o.y2 <= this->y2
			|| o.y1 <= this->y1 && this->y1 <= o.y2
 			|| o.y1 <= this->y2 && this->y2 <= o.y2)
		{
			dy = 0;
		} else {
			dy = min(abs(o.y1 - this->y2), abs(this->y1 - o.y2));
		}

		return max(dx, dy);
	}

};

vector<Object> objects;
vector<vector<pair<int, int> > > g;

int main() {

	cin >> n >> w;
	int a, b, c, d;

	Object A(INT_MIN, w, INT_MAX , w+1);
	objects.push_back(A);
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;
		objects.push_back(Object(a, b, c, d));
	}
	Object B(INT_MIN, -1, INT_MAX, 0);
	objects.push_back(B);

	g.resize(n + 2);

	for (int i = 0; i < n + 2; i++) {
		for (int j = 0;j< n + 2; j++) {
			if (i != j) {
				g[i].push_back(make_pair(j, objects[i].dist(objects[j])));
			}
		}
	}

	vector<int> dist(n + 2, INT_MAX);
	vector<bool> used(n + 2, false);


	dist[0] = 0;
	for (int i = 0; i < n + 2; i++) {

		int nearest = -1;
		for (int j = 0; j < n + 2; j++) {
			if (!used[j] && (nearest == -1 || dist[j] < dist[nearest])) {
				nearest = j;
			}
		}
		if (dist[nearest] == INT_MAX) {
			break;
		}

		for (int j = 0; j < g[nearest].size(); j++) {
			if ( dist[g[nearest][j].first] > dist[nearest] + g[nearest][j].second) {
				dist[g[nearest][j].first] = dist[nearest] + g[nearest][j].second;
			}
		}

		used[nearest] = true;
	}

	cout << dist[n + 1] << endl;

	return 0;
}
