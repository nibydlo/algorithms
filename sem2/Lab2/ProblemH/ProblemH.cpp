#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > edgeList;
int timer, nodeCounter, n;

void pointsDfs(int curNode, int prevNode, int* t1, int* t2, bool* mark, bool* isPoint) {
    mark[curNode] = true;
    t1[curNode] = timer;
    t2[curNode] = timer;
    timer++;
    int nexts = 0;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        if (nextNode == prevNode) {
            continue;
        }
        if (mark[nextNode]) {
            t2[curNode] = min(t2[curNode], t1[nextNode]);
        } else {
            pointsDfs(nextNode, curNode, t1, t2, mark, isPoint);
            t2[curNode] = min(t2[curNode], t2[nextNode]);
            nexts++;
            if (t2[nextNode] >= t1[curNode] && prevNode != -1) {
                if (!isPoint[curNode]) {
                        nodeCounter++;
                }
                isPoint[curNode] = true;
            }
        }
    }
    if (nexts > 1 && prevNode == -1) {
            if (!isPoint[curNode]) {
                        nodeCounter++;
                }
        isPoint[curNode] = true;
        //nodeCounter++;
    }
}

int main() {

    ifstream fin("points.in");
    ofstream fout("points.out");

    int m, start, finish;
    fin >> n >> m;
    edgeList.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        start--;
        finish--;
        edgeList[start].push_back(finish);
        edgeList[finish].push_back(start);
    }

    bool* mark = new bool[n];
    bool* isPoint = new bool[n];
    int* t1 = new int[n];
    int* t2 = new int[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
        isPoint[i] = false;
    }
    timer = 0;
    nodeCounter = 0;

    pointsDfs(0, -1, t1, t2, mark, isPoint);
    fout << nodeCounter << endl;
    for (int i = 0; i < n; i++) {
        if (isPoint[i]) {
            fout << i + 1 << " ";
        }
    }

    fin.close();
    fout.close();

    return 0;
}
