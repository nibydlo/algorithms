#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int> > edgeList;

/*void bfs(int row, int* distance, bool* mark, int curDist){
    for (int i = 0; i < edgeList[row].size(); i++) {
        if (!mark[edgeList[row][i]]){
            distance[edgeList[row][i]] = curDist;
            mark[edgeList[row][i]] = true;
        }
    }
}*/

int main(){

    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");

    int n, m, start, finish;
    fin >> n >> m;
    //cout << n << " " << m << endl;
    edgeList.resize(n);
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        edgeList[start - 1].push_back(finish);
        edgeList[finish - 1].push_back(start);
    }
    //cout << "input finished" << endl;
    int *distance = new int[n];
    bool *mark = new bool[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }
    distance[0] = 0;
    mark[0] = true;

    queue<int> nodeQueue;
    nodeQueue.push(1);

    while (!nodeQueue.empty()) {
        //cout << "start while" << endl;
        int curNode = nodeQueue.front();
        //cout << "curNode = " << curNode << endl;
        nodeQueue.pop();
        for (int i = 0; i < edgeList[curNode - 1].size(); i++) {
            //cout << " start for" << endl;
            int nextNode = edgeList[curNode - 1][i];
            //cout << "nextNode = " << nextNode << endl;
            if (!mark[nextNode - 1]) {
                mark[nextNode - 1] = true;
                nodeQueue.push(nextNode);
                distance[nextNode - 1] = distance[curNode - 1] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        fout << distance[i] << " ";
    }

    fin.close();
    fout.close();

    return 0;
}
