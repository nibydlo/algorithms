#include <bits/stdc++.h>

using namespace std;

int n;
vector< vector <int> > matrix;
vector<int> row_pot;
vector<int> col_pot;
vector<int> parsos;
vector<int> parent;
vector<int> mins;
vector<bool> used;
vector<int> result;

const int maxsos = 400000000;

int main() {

	ifstream fin("assignment.in");
	ofstream fout("assignment.out");

	fin >> n;
	matrix.resize(n + 1);
	matrix[0].assign(n + 1, 0);
	for (int i = 1; i < n + 1; i++) {
		matrix[i].resize(n + 1);
		matrix[i][0] = 0;

		for (int j = 1; j < n + 1; j++) {
			fin >> matrix[i][j];
		}
	}

	row_pot.resize(n + 1);
	col_pot.resize(n + 1);
	parsos.resize(n + 1);
	parent.resize(n + 1);

	for (int i = 0; i < n + 1; i++) {

		mins.assign(n + 1, maxsos);
		used.assign(n + 1, false);

		parsos[0] = i;
		int col_num = 0;

		do {
			used[col_num] = true;
			int row_num = parsos[col_num];
			int del = maxsos;
			int new_col_num;

			for (int j = 1; j < n + 1; j++) {
				if (!used[j]) {

					int new_min = matrix[row_num][j] - row_pot[row_num] - col_pot[j];

					if (new_min < mins[j]) {
						mins[j] = new_min;
						parent[j] = col_num;
					}

					if (mins[j] < del) {
						del = mins[j];
						new_col_num = j;
					}
				}
			}

			for (int j = 0; j < n + 1; j++) {
				if (used[j]) {
					row_pot[parsos[j]] += del;
					col_pot[j] -= del;
				} else {
					mins[j] -= del;
				}
			}

			col_num = new_col_num;

		} while (parsos[col_num] != 0);

		do {
			int new_col_num = parent[col_num];
			parsos[col_num] = parsos[new_col_num];
			col_num = new_col_num;
		} while (col_num);
	}

	result.resize(n + 1);
	long long ans = 0;
	for (int i = 1; i < n + 1; i++) {
		result[parsos[i]] = i;
		ans += matrix[parsos[i]][i];
	}

	fout << ans << endl;
	for (int i = 1; i < n + 1; i++) {
		fout << i << " " << result[i] << endl;
	}

	fin.close();
	fout.close();

	return 0;
}
