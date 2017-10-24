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

    ifstream fin("cond.in");
    ofstream fout("cond.out");

    int n, m, start, finish;
    fin >> n >> m;
    //cout << n << " " << m << endl;
    edgeList.resize(n);
    edgeListT.resize(n);

    int* startArray = new int[m];
    int* finishArray = new int[m];
    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        startArray[i] = start;
        finishArray[i] = finish;
        //cout << "sf: " << start << " " << finish << endl;
        edgeList[start - 1].push_back(finish);
        edgeListT[finish - 1].push_back(start);
    }
    //cout << "finish reading " << endl;
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

    bool* edgesResultBool = new bool[m];
    for (int i = 0; i < m; i++) {
        edgesResultBool[i] = true;
    }
    bool** mark2 = new bool*[componentsCount];
    for (int i = 0; i < componentsCount; i++) {
        mark2[i] = new bool[componentsCount];
    }
    for (int i = 0; i < componentsCount; i++) {
        for (int j = 0; j < componentsCount; j++) {
            mark2[i][j] = false;
        }
    }
    //cout << "comp ar [3] = " << componentsArray[3] << endl;
    for (int i = 0; i < m; i++) {
        //cout << "run for: i = " << i << endl;
        //cout << "before start = " << componentsArray[startArray[i] - 1] << endl;
        startArray[i] = componentsArray[startArray[i] - 1];
        //cout << "start ar = " << startArray[i] << endl;
        //cout << "before finish = " << componentsArray[finishArray[i] - 1] << endl;
        finishArray[i] = componentsArray[finishArray[i] - 1];
        //cout << "finish ar = " << finishArray[i] << endl;
        if (startArray[i] == finishArray[i]) {
            edgesResultBool[i] = false;
        }
        if (mark2[startArray[i] - 1][finishArray[i] - 1]) {
            edgesResultBool[i] = false;
        }
        mark2[startArray[i] - 1][finishArray[i] - 1] = true;
    }

    int edgesCounter = 0;
    for (int i = 0; i < m; i++) {
        if (edgesResultBool[i]) {
            edgesCounter++;
        }
    }

    /*bool** mark2 = new bool*[n];
    for (int i = 0; i < n; i++) {
        mark2[i] = new bool[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mark2[i][j] = false;
        }
    }*/

    /*bool* resultEdges = new bool[m];
    for (int i = 0; i < m; i++) {
        if (componentsArray[startArray[i] - 1] == componentsArray[finishArray[i] - 1] || mark2[componentsArray[startArray[i] - 1]][componentsArray[finishArray[i] - 1]]) {
            resultEdges[i] = false;
        } else {
            resultEdges[i] = true;
            startArray[i] = componentsArray[startArray[i] - 1];
            finishArray[i] = componentsArray[finishArray[i] - 1];
            mark2[componentsArray[startArray[i] - 1]][componentsArray[finishArray[i] - 1]] = true;
        }
    }

    int edgesCounter = 0;
    for (int i = 0; i < m; i++) {
        if (resultEdges[i]) {
            //cout << startArray[i] << " " << finishArray[i] << endl;
            edgesCounter++;
        }
    }*/


    fout << componentsCount << " " << edgesCounter << endl;
    /*for (int i = 0; i < n; i++) {
        fout << componentsArray[i] << " ";
    }*/

    fin.close();
    fout.close();

    return 0;
}
