#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > edgeList, edgeListT;
vector<int> order;
vector<int> component;

void dfsOrderGen(int curNode, bool* mark) {
    //cout << "start dfs1; curNode = " << curNode << endl;
    mark[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i];
        //cout << "nextNode = " << nextNode << endl;
        if(!mark[nextNode]) {
            dfsOrderGen(nextNode, mark);
        }
    }
    order.push_back(curNode);
}

void dfsComponentGen(int curNode, bool* mark) {
    mark[curNode] = true;
    component.push_back(curNode);
    for (int i = 0; i < edgeListT[curNode].size(); i++) {
        int nextNode = edgeListT[curNode][i];
        if (!mark[nextNode]) {
            dfsComponentGen(nextNode, mark);
        }
    }
}

int main() {

    ifstream fin("strong.in");
    ofstream fout("strong.out");

    int n, m, start, finish;
    fin >> n >> m;
    //cout << n << " " << m << endl;
    edgeList.resize(n);
    edgeListT.resize(n);

    for (int i = 0; i < m; i++) {
        fin >> start >> finish;
        //cout << "sf: " << start << " " << finish << endl;
        start--;
        finish--;
        edgeList[start].push_back(finish);
        edgeListT[finish].push_back(start);
    }
    //cout << "finish reading " << endl;
    bool *mark = new bool[n];
    for (int i = 0; i < n; i++) {
        mark[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (!mark[i]) {
            //cout << "start if in for, i = " << endl;
            dfsOrderGen(i, mark);
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
        /*cout << "mark : ";
        for (int i = 0; i < n; i++) {
            cout << mark[i] << " ";
        }
        cout << endl;*/
        if (!mark[curNode]) {
            dfsComponentGen(curNode, mark);
            if (!component.empty()) {
                componentsCount++;
            }
            //cout << "component size = " << component.size() << endl;
            for (int j = 0; j < component.size(); j++) {
                //cout << "start for" << endl;
                //cout << component[j] << " ";
                //cout << "ca[" << component[j] - 1 << "] = " << componentsCount << endl;
                componentsArray[component[j]] = componentsCount;
            }
            //cout << "mark: ";
            /*for (int i = 0; i < n; i++) {
                cout << mark[i] << " ";
            }*/
            //cout << endl;
            component.clear();
        }
    }

    fout << componentsCount << endl;
    for (int i = 0; i < n; i++) {
        fout << componentsArray[i] << " ";
    }

    /*for (int i = 0; i < n; i++) {
        if (componentsArray[i] == componentsArray[no(i)]) {
            cout << "-1";
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int res = componentsArray[i] > componentsArray[no(i)] ? i : no(i);
        if (res < n) {
            cout << friendsVector
        }
    }*/

    fin.close();
    fout.close();

    return 0;
}
