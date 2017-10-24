#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int index;
    int s;
    int p;
    int t;
};

bool comp(Task x, Task y) {
    if (x.s < y.s)
        return true;
    else
        return false;
}

int main() {

    ifstream fin("practice.in");
    ofstream fout("practice.out");

    int n, T, R;
    fin >> n >> T >> R;
    Task firstTask;
    firstTask.index = 0;
    firstTask.s = 0;
    firstTask.p = 0;
    firstTask.t = 0;
    vector<Task> taskVector;
    vector<int> result;
    taskVector.push_back(firstTask);

    for (int i = 1; i <= n; i++) {
        Task tempTask;
        fin >> tempTask.s >> tempTask.p >> tempTask.t;
        tempTask.index = i;
        taskVector.push_back(tempTask);
    }

    /*for (int i = 1; i <= n; i++) {
        cout << taskVector[i].index << " " << taskVector[i].s << " " << taskVector[i].p << " " << taskVector[i].t << endl;
    }*/

    stable_sort(taskVector.begin(), taskVector.end(), comp);

    int **d = new int*[n + 1];
    for (int i = 0; i <= n; i++)
        d[i] = new int[T + 1];

    for (int i = 0; i <= n; i++ ) {
        for (int j = 0; j <= T; j++) {
            d[i][j] = R;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= T; j++) {
            if (j >= taskVector[i].t && d[i - 1][j - taskVector[i].t] >= taskVector[i].s) {
                d[i][j] = max(d[i - 1][j], d[i - 1][j - taskVector[i].t] + taskVector[i].p);
            } else {
                d[i][j] = d[i - 1][j];
            }
        }
    }

    fout << d[n][T] << endl;

    int i = n;
    int j = T;

    while (i > 0 && j > 0) {
        if (j >= taskVector[i].t && d[i - 1][j - taskVector[i].t] >= taskVector[i].s) {
            if (d[i - 1][j] < d[i - 1][j - taskVector[i].t] + taskVector[i].p) {
                result.push_back(taskVector[i].index);
                j -= taskVector[i].t;
            }
        }
        i--;
    }

    for (int i = result.size() - 1; i>= 0; i--){
        fout << result[i] << " ";
    }

    /*for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= T; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }*/

    fin.close();
    fout.close();

    return 0;
}
