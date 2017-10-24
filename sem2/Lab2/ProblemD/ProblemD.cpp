#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > edgeList;
int cycleStart, cycleFinish;

bool dfsChecker(int curNode, int* color, int* prevNode) {
    //cout << "start checker";
    color[curNode - 1] = 1;
    for (int i = 0; i < edgeList[curNode - 1].size(); i++) {
        int nextNode = edgeList[curNode - 1][i];
        if (color[nextNode - 1] == 0) {
            prevNode[nextNode - 1] = curNode;
            if(dfsChecker(nextNode, color, prevNode)) return true;
        } else {
            if (color[nextNode - 1] == 1) {
                cycleStart = nextNode;
                cycleFinish = curNode;
                return true;
            }
        }
    }
    color[curNode - 1] = 2;
    return false;
}

int main() {

    ifstream fin("cycle.in");
    ofstream fout("cycle.out");

    int n, m, start, finish;
    fin >> n >> m;

    edgeList.resize(n);

    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        edgeList[start - 1].push_back(finish);
    }

    int *color = new int[n];
    for (int i = 0; i < n; i++) {
        color[i] = 0;
    }

    int* prevNode = new int[n];

    bool cycleB = false;
    for (int i = 0; i < n; i++) {
        if (dfsChecker(i + 1, color, prevNode)) {
            cycleB = true;
            break;
        }
    }

    if (!cycleB) {
        fout << "NO" << endl;
        return 0;
    }
    //cout << "start = " << cycleStart << endl;
    //cout << "finish = " << cycleFinish << endl;
    fout << "YES" << endl;
    vector<int> cycle;
    cycle.push_back(cycleStart);
    int curNode = cycleFinish;
    while (curNode != cycleStart) {
        cycle.push_back(curNode);
        //cout << "cur node = " << curNode << " prev node = " << prevNode[curNode - 1] << endl;
        curNode = prevNode[curNode - 1];

    }
    //cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());
    for (int i = 0; i < cycle.size(); i++) {
        fout << cycle[i] << " ";
    }
    fin.close();
    fout.close();

    return 0;
}
