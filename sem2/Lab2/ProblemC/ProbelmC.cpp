#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > edgeList;
vector<int> result;

bool dfsChecker(int curNode, int* color) {

    color[curNode] = 1;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        if (color[nextNode] == 0) {
            if(dfsChecker(nextNode, color)) return true;
        } else {
            if (color[nextNode] == 1) {
                return true;
            }
        }
    }
    color[curNode] = 2;
    return false;
}

void dfs(int curNode, bool* mark) {
    //cout << "start dfs; curNode = " << curNode << endl;
    mark[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        if (!mark[nextNode]) {
            dfs(nextNode, mark);
        }
    }
    result.push_back(curNode);
}

int main() {

    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    int n, m, start, finish;
    fin >> n >> m;
    //cout << n << " " << m << endl;

    edgeList.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        start--;
        finish--;
        edgeList[start].push_back(finish);
    }

    int *color = new int[n];
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    bool cycle = false;
    for (int i = 0; i < n; i++) {
        if (dfsChecker(i, color)) {
            cycle = true;
            break;
        }
    }

    if (cycle) {
        fout << "-1" << endl;
        return 0;
    }

    bool *mark = new bool[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }
    //result.clear();
    //cout << "start dfs" << endl;
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            dfs(i, mark);
        }
    }

    reverse(result.begin(), result.end());

    for (int i = 0; i < n; i++) {
        fout << result[i] + 1 << " ";
    }

    fin.close();
    fout.close();

    return 0;
}
