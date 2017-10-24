#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<int> > edgeList, edgeListT;
vector<int> order;
vector<int> component;
int n;

void dfsOrderGen(int curNode, bool* mark) {
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

/*void dfsComponentGen(int curNode, bool* mark) {
    mark[curNode] = true;
    component.push_back(curNode);
    for (int i = 0; i < edgeListT[curNode].size(); i++) {
        int nextNode = edgeListT[curNode][i];
        if (!mark[nextNode]) {
            dfsComponentGen(nextNode, mark);
        }
    }
}*/

void dfsComponentGen(int curNode, int cl, bool* mark) {
    component[curNode] = cl;
    for (int i = 0; i < edgeListT[curNode].size(); i++) {
        int nextNode = edgeListT[curNode][i];
        if (component[nextNode] == -1) {
            dfsComponentGen(nextNode, cl, mark);
        }
    }
}

int no(int a) {
    if (a < n) {
        return a + n;
    } else {
        return a - n;
    }
}

int main() {

    int m, start, finish;
    //ifstream fin("2sat.in");
    cin >> n >> m;
    edgeList.resize(2*n);
    edgeListT.resize(2*n);
    vector<string> friendsVector(n);
    for (int i = 0; i < n; i++) {
        cin >> friendsVector[i];
    }
    //input
    for (int i = 0; i < m; i++) {
        char sign1, sign2;
        string name1, name2, impl;
        cin >> sign1 >> name1 >> impl >> sign2 >> name2;
        //convert names into numbers
        int indexName1, indexName2, start, finish;
        std::vector<string>::iterator it;
        it = find(friendsVector.begin(), friendsVector.end(), name1);
        indexName1 = distance(friendsVector.begin(), it);
        it = find(friendsVector.begin(), friendsVector.end(), name2);
        indexName2 = distance(friendsVector.begin(), it);
        //input edges
        sign1 == '-' ? start = no(indexName1) : start = indexName1;
        sign2 == '-' ? finish = no(indexName2) : finish = indexName2;
        edgeList[start].push_back(finish);
        edgeList[no(finish)].push_back(no(start));
        edgeListT[finish].push_back(start);
        edgeListT[no(start)].push_back(no(finish));
    }

    /*cout << "edgeList: " << endl;
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < edgeList[i].size(); j++) {
            cout << edgeList[i][j] << " ";
        }
        cout << endl;
    }

    cout << "edgeListT: " << endl;
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < edgeListT[i].size(); j++) {
            cout << edgeListT[i][j] << " ";
        }
        cout << endl;
    }*/

    bool* mark = new bool[2*n];
    for (int i = 0; i < 2*n; i++) {
        mark[i] = false;
    }

    for (int i = 0; i < 2*n; i++) {
        if (!mark[i]) {
            dfsOrderGen(i, mark);
        }
    }

    for (int i = 0; i < 2*n; i++) {
        mark[i] = false;
    }
//cout << "run" << endl;
    int componentsCount = 0;
    //int* componentsArray = new int[2*n];
    component.resize(2*n);
    for (int i = 0; i < 2*n; i++) {
        component[i] = -1;
    }
    //cout << "run" << endl;
    for (int i = 0, j = 0; i < 2*n; i++) {
        int curNode = order[2*n - i - 1];
        if (component[curNode] == -1) {
            dfsComponentGen(curNode, j++, mark);
        }
    }
    /*for (int i = 2*n - 1; i >= 0; i--) {
        int curNode = order[i];
        if (!mark[curNode]) {
            dfsComponentGen(curNode, mark);
            if (!component.empty()) {
                componentsCount++;
            }
            for (int j = 0; j < component.size(); j++) {
                componentsArray[component[j]] = componentsCount;
            }
            component.clear();
        }
    }*/

    bool e = false;
    for (int i = 0; i < n; i++) {
        if (component[i] == component[no(i)]) {
            e = true;
            //return 0;
        }
    }

    /*cout << componentsCount << endl;
    for (int i = 0; i < 2*n; i++) {
        cout << componentsArray[i] << " ";
    }*/
    vector<string> outputVector;
    int friendCounter = 0;
    //cout << "fr counter = " << friendCounter << endl;
    for (int i = 0; i < n; i++) {
        int res = component[i] > component[no(i)] ? i : no(i);
        if (res < n) {
            //cout << "res = " << res << endl;
            friendCounter++;
            outputVector.push_back(friendsVector[res]);

        }
    }
    if (friendCounter == 0 || e) {
        cout << -1;
        return 0;
    }
    cout << friendCounter << endl;
    for (int i = 0; i < outputVector.size(); i++) {
        cout << outputVector[i] << endl;
    }

    return 0;
}
