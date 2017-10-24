#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//vector < vector < pair < int, int > > > edgeList;

int main() {

    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");

    int n, m, start, finish, weight;
    fin >> n >> m;

    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = INT_MAX;
        }
        matrix[i][i] = 0;
    }

    //edgeList.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish >> weight;
        start--;
        finish--;
        //edgeList[start].push_back(make_pair(finish, weight));
        matrix[start][finish] = weight;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] < INT_MAX && matrix[k][j] < INT_MAX) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }



    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << matrix[i][j] << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
