#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<vector<int> > edgeList;
int timer, bridgeCounter;



void bridgesDfs(int curNode, int prevNode, int* t1, int* t2, bool* mark, bool* isBridge, int m, int** edgeArray) {
    //cout << "RUN DFS, CURNODE = " << curNode << endl;
    mark[curNode] = true;
    t1[curNode] = timer;
    t2[curNode] = timer;
    timer++;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        //cout << "curNode = " << curNode << " nextNode = " << edgeList[curNode][i] << endl;
        //cout << "t1 curNode == " << t1[curNode] << " t2 curNode == " << t2[curNode] << endl;
        int nextNode = edgeList[curNode][i];
        if (nextNode == prevNode) {
            continue;
        }
        if (mark[nextNode]) {
            //cout << "run if" << endl;
            //cout << "now"
            t2[curNode] = min(t2[curNode], t1[nextNode]);
        } else {
            //cout << "run else" << endl;
            bridgesDfs(nextNode, curNode, t1, t2, mark, isBridge, m, edgeArray);
            t2[curNode] = min(t2[curNode], t2[nextNode]);
            if (t2[nextNode] > t1[curNode]) {
                //cout << "I see bridge between " << curNode << " and " << nextNode << endl;
                //cout << "because t2[" << nextNode << "] = " << t2[nextNode] << " & t1[" << curNode << "] = " << t1[curNode] << endl;
                bridgeCounter++;
                for (int i = 0; i < m; i++) {
                    if (edgeArray[i][0] == curNode && edgeArray[i][1] == nextNode || edgeArray[i][1] == curNode && edgeArray[i][0] == nextNode) {
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

    int n, m, start, finish;
    fin >> n >> m;
    edgeList.resize(n);
    int** edgeArray = new int*[m];
    for (int i = 0; i < m; i++) {
            edgeArray[i] = new int[2];
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
    //cout << "run" << endl;
    bool* mark = new bool[n];
    int* t1 = new int[n];
    int* t2 = new int[n];
    bool* isBridge = new bool[m];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
        //isBridge[i] = false;
        t1[i] = 0;
        t2[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        isBridge[i] = false;
    }
    timer = 0;
    bridgeCounter = 0;
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
        bridgesDfs(i, -1, t1, t2, mark, isBridge, m, edgeArray);
        }
    }
    //fout << "run" << endl;
    fout << bridgeCounter << endl;
    for (int i = 0; i < m; i++) {
        if (isBridge[i]) {
            fout << i + 1 << " ";
        }
    }

    fin.close();
    fout.close();

    return 0;
}
