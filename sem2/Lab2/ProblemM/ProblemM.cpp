#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > edgeList;
vector<vector<int> > edgeListT;
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

    ifstream fin("game.in");
    ofstream fout("game.out");

    int n, m, start, finish, s;
    fin >> n >> m >> s;
    //cout << n << " " << m << endl;

    edgeList.resize(n);
    edgeListT.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        start--;
        finish--;
        edgeList[start].push_back(finish);
        edgeListT[finish].push_back(start);
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

    //reverse(result.begin(), result.end());

    /*for (int i = 0; i < n; i++) {
        cout << result[i] + 1 << " ";
    }
    cout << endl;*/

    bool* gameColor = new bool[n];
    /*for (int i = 0; i < n; i++) {
        gameColor[i] = false;
    }*/
    gameColor[result[0]] = false;
    for (int i = 1; i < n; i++) {
        bool isTrue = true;
        //cout << "run for i = " << i << endl;
        for(int j = 0; j < edgeList[result[i]].size(); j++) {
            if (!gameColor[edgeList[result[i]][j]]) {
                //cout << "run first if" << endl;
                //cout << "nextNode = " << edgeList[result[i]][j] << endl;
                //cout << "color = " << gameColor[edgeList[result[i]][j]] <<endl;
                gameColor[result[i]] = true;
                isTrue = false;
            }
        }
        if(isTrue) {
            //cout <<  "run second if" << endl;
            gameColor[result[i]] = false;
        }
        //cout << "gc[i] = " << gameColor[i] << endl;
    }

    /*for (int i = 0; i < n; i++) {
        cout << gameColor[result[i]] << " ";
    }
    cout << endl;*/
    if (gameColor[s - 1]) {
        fout << "First player wins" << endl;
    } else {
        fout << "Second player wins" << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
