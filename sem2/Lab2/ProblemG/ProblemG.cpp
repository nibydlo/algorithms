#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > edgeList;
vector<int> t1, t2;
int m, timer, bridgeCounter;

void bridgesDfs(int curNode, bool* mark, int** edgeArray, bool* isBridge, int prevNode = -1) {
    mark[curNode] = true;
    t1[curNode] = timer;
    t2[curNode] = timer;
    //cout << "beg: timer = " << timer << endl;
    timer++;
    //cout << "and now timer = " << timer << endl;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        bool goFar = true;
        if (nextNode == prevNode) {
            continue;
        }
        if (mark[nextNode]) {
            //cout << "now t2[" << curNode << "] = " << min(t2[curNode], t1[nextNode]) << endl;
            t2[curNode] = min(t2[curNode], t1[nextNode]);
        } else {
            bridgesDfs(nextNode, mark, edgeArray, isBridge, curNode);
            t2[curNode] = min(t2[curNode], t2[nextNode]);
            if (t2[nextNode] > t1[curNode]) {
                //cout << "timer = " << timer << endl;
                //cout << "I see bridge between " << curNode << " and " << nextNode << endl;
                bridgeCounter++;
                for (int i = 0; i < m; i++) {
                    if (edgeArray[i][0] == curNode && edgeArray[i][1] == nextNode) {
                        isBridge[i] = true;
                    }
                }
            }
        }
    }
}

int main() {

    ifstream fin("bridges.in");
    ofstream fout("bridges.out");

    int n, start, finish;
    fin >> n >> m;

    edgeList.resize(n);
    bool* isBridge = new bool[m];
    for (int i = 0; i < m; i++) {
        isBridge[i] = false;
    }
    int** edgeArray = new int*[m];
    for (int i = 0; i < m; i++) {
            edgeArray[i] = new int[2];
    }
    t1.resize(n);
    t2.resize(n);
    for (int i = 0; i < n; i++) {
        t1[i] = t2[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        start--;
        finish--;
        edgeArray[i][0] = start;
        edgeArray[i][1] = finish;
        edgeList[start].push_back(finish);
        edgeList[finish].push_back(start);
    }
    bool *mark = new bool[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }

    timer = 0;
    bridgeCounter = 0;
    for (int i = 0; i < n; i++) {

        if (!mark[i]) {
            //cout << "run if in for, i = " << i << endl;
            bridgesDfs(i, mark, edgeArray, isBridge);
        }
    }
    fout << bridgeCounter << endl;
    for (int i = 0; i < m; i++) {
        if (isBridge[i]) {
            fout << i + 1 << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
