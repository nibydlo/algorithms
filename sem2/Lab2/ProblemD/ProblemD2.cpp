#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<pair<int, char> > > edgeList;
vector<bool> isTerminal;

int main() {

    ifstream fin("problem4.in");
    ofstream fout("problem4.out");

    int n, m, k, l, terminalNum, start, finish, name;
    fin >> n >> m >> k >> l;

    edgeList.resize(n);
    isTerminal.assign(n, false);
    for (int i = 0; i < k; i++) {
        fin >> terminalNum;
        isTerminal[terminalNum] = true;
    }

    for (int i = 0; i < m; i++) {
        fin >> start >> finish >> name;
        start--;
        finish--;
        edgeList[start].push_back(make_pair(finish, name));
    }

    for (int i = 0; i< n; i++) {
        for (int j = 0; j < edgeList[i].size(); j++) {
            cout << "(" << edgeList[i][j].first << ", " << edgeList[i][j].second << ")  ";
        }
        cout << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
