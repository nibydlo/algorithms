#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

vector<vector<int> > edgeList;
vector<vector<int> > weightList;
list<int> result;
vector<bool> mark;

struct Edge {
    int start;
    int cinish;
    int weight;
};


void dfs(int curNode) {
    //cout << "start dfs; curNode = " << curNode << endl;
    mark[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        if (!mark[nextNode]) {
            dfs(nextNode);
        }
    }
    result.push_front(curNode);
}

int main() {

    ifstream cin("shortpath.in");ofstream cout("shortpath.out");

    int n, m, s, t, tempS, tempF, tempW;
    cin >> n >> m >> s >> t;

    edgeList.resize(n);
    weightList.resize(n);
    Edge* edgeArray  = new Edge[m];
    for (int i = 0; i < m; i++) {
        cin >> tempS >> tempF >> tempW;
        tempS--;
        tempF--;
        edgeArray[i].start = tempS;
        edgeArray[i].cinish = tempF;
        edgeArray[i].weight = tempW;
        edgeList[tempS].push_back(tempF);
        weightList[tempS].push_back(tempW);
    }
    //cout << "run" << endl;


    //cout << "run" << endl;
    mark.resize(n,false);
    dfs(s - 1);

    if (!mark[t - 1] ) {
        cout << "Unreachable";
        return 0;
    }
    //cout << "run" << endl;



    /*for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }*/

    int* d = new int[n];
    for (int i = 0; i < n; i++) {
        d[i] = 100000001;
    }
    d[s - 1] = 0;

    for (list<int>::iterator i = result.begin();i!=result.end();++i) {
        for (int j = 0; j < edgeList[*i].size(); j++) {
            //cout << "run edgeList[i][j] = " << edgeList[i][j] << endl;
            int we = 100000001;
            int to = edgeList[*i][j];
            we = weightList[*i][j];
            /*for (int k = 0; k < m; k++) {
                if (edgeArray[k].start == *i && edgeArray[k].cinish == to) {
                    we = edgeArray[k].weight;
                    break;
                }
            }*/
            //cout << "we = " << we << " d[edgeList[i][j]] = " << d[edgeList[i][j]] << endl;
            d[to] = min(d[to], d[*i] + we);
            //cout << "now d[j] = " << d[edgeList[i][j]] << endl;
        }
    }

    if (d[t - 1] == 100000001) {
        cout << "Unreachable";
        return 0;
    }
    cout << d[t - 1];


    return 0;
}
