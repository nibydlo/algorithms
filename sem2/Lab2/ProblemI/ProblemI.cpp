#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > edgeList, edgeListT;
vector<int> order;
vector<int> component;

void dfsOrderGen(int curNode, bool* mark) {
    //cout << "start dfs1; curNode = " << curNode << endl;
    mark[curNode - 1] = true;
    for (int i = 0; i < edgeList[curNode - 1].size(); i++) {
        int nextNode = edgeList[curNode - 1][i];
        //cout << "nextNode = " << nextNode << endl;
        if(!mark[nextNode - 1]) {
            dfsOrderGen(nextNode, mark);
        }
    }
    order.push_back(curNode);
}

void dfsComponentGen(int curNode, bool* mark) {
    mark[curNode - 1] = true;
    component.push_back(curNode);
    for (int i = 0; i < edgeListT[curNode - 1].size(); i++) {
        int nextNode = edgeListT[curNode - 1][i];
        if (!mark[nextNode - 1]) {
            dfsComponentGen(nextNode, mark);
        }
    }
}

int main() {

    ifstream fin("fire.in");
    ofstream fout("fire.out");

    int n, m, start, finish;
    fin >> n >> m;
    edgeList.resize(n);
    edgeListT.resize(n);

    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        edgeList[start - 1].push_back(finish);
        edgeListT[finish - 1].push_back(start);
    }

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeListT[i].size(); j++) {
            cout << edgeListT[i][j] << " ";
        }
        cout << endl;
    }*/

    bool *mark = new bool[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            //cout << "start if in for, i = " << endl;
            dfsOrderGen(i + 1, mark);
        }
    }
    //cout << "finish first dfs" << endl;
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }

    int componentsCount = 0;
    int* componentsArray = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        //cout << "order i = " << order[i] << endl;
        int curNode = order[i];
        //cout << "curNode = " << curNode << endl;
        if (!mark[curNode - 1]) {
            dfsComponentGen(curNode, mark);
            if (!component.empty()) {
                componentsCount++;
            }
            for (int j = 0; j < component.size(); j++) {
                //cout << "start for" << endl;
                //cout << component[j] << " ";
                componentsArray[component[j] - 1] = componentsCount;
            }
            //cout << "mark: ";
            /*for (int i = 0; i < n; i++) {
                cout << mark[i] << " ";
            }*/
            //cout << endl;
            component.clear();
        }
    }

    //cout << componentsCount << endl;
    /*for (int i = 0; i < n; i++) {
        cout << componentsArray[i] << " ";
    }*/
    //cout << "edgeListT[5][0] - 1 = " << edgeListT[5][0] - 1<< endl;
    int* cp = new int[componentsCount];
    for (int i = 0; i < componentsCount; i++) {
        cp[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        //cout << "i = " << i << endl;
        for (int j = 0; j < edgeList[i].size(); j++) {
            //cout << "run for" << endl;
            //cout << componentsArray[edgeListT[i][j] - 1] << " " << componentsArray[i] << endl;
            if (componentsArray[edgeList[i][j] - 1] != componentsArray[i]) {
                //cout << "run if i = " << i << " j = " << j << endl;
                cp[componentsArray[i] - 1]++;
                //cout << "now cp[" << componentsArray[i] - 1 << "] = " << cp[componentsArray[i]- 1] << endl;
            }
        }
    }
    int fireStationCount = 0;
    for (int i = 0; i < componentsCount; i++) {
        if (cp[i] == 0) {
            fireStationCount++;
        }
    }
    fout << fireStationCount << endl;

    fin.close();
    fout.close();

    return 0;
}
