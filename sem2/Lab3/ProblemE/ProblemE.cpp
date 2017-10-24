#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <functional>
#include <math.h>

using namespace std;

class edge{
public:
    int start;
    int finish;
    long long weight;

    edge(int a, int b, long long c) {
        start = a;
        finish = b;
        weight = c;
    }
};

vector< vector <pair< int, long long> > > edgeList;
vector <edge> edgeVector;
vector< long long > d2;
vector< bool > isAttainable;
const long long doHuya = (long long)pow(10, 15) + 1;

void dfs(int curNode) {
    isAttainable[curNode] = true;
    for (int i = 0; i < edgeList[curNode].size(); i++) {
        int nextNode = edgeList[curNode][i].first;
        if (isAttainable[nextNode] == false) {
            dfs(nextNode);
        }
    }
}

int main() {

    ifstream fin("path.in");
    ofstream fout("path.out");

    int n, m, s, start, finish;
    long long weight;
    fin >> n >> m >> s;
    isAttainable.assign(n, false);
    edgeList.resize(n);
    edgeVector.resize(m);
    d2.resize(n);

    long long ** d = new long long*[n];
    for (int i = 0; i < n; i++) {
        d[i] = new long long[n];
        for (int j = 0; j < n; j++) {
            d[i][j] = doHuya;
        }
        d[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        fin >> start >> finish >> weight;
        d[start - 1][finish - 1] = weight;
        edgeList[start - 1].push_back(make_pair(finish - 1, weight));
        edgeVector.push_back(edge(start - 1, finish - 1, weight));
    }

    dfs(s - 1);

    //floyd
    for (int k = 0; k < n; k++) {
        int i = s - 1;
        for (int i = 0; i < n; i++) {
            if(isAttainable[i]) {
                for (int j = 0; j < n; j++) {
                    if (isAttainable[j]) {
                    if (d[i][k] < doHuya && d[k][j] < doHuya) {
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    }
                    }
            }
            }
        }
    }

    //floyd for cycles
    /*for (int i = 0; i < n; i++) {
        if (isAttainable[i]) {
            for (int j = 0; j < n; j++) {
                if (isAttainable[j]) {
                for (int k = 0; k < n; k++) {
                    if (d[i][k] < doHuya && d[k][k] < 0 && d[k][j] < doHuya) {
                        d[i][j] = -doHuya;
                    }
                }
                }
            }
        }
    }*/

    int i = s - 1;
    //for (int i = 0; i < n; i++) {
        if (isAttainable[i]) {
            for (int j = 0; j < n; j++) {
                if (isAttainable[j]) {
                for (int k = 0; k < n; k++) {
                    if (d[i][k] < doHuya && d[k][k] < 0 && d[k][j] < doHuya) {
                        d[i][j] = -doHuya;
                    }
                }
                }
            }
        }
    //}

	    //-----------------------------------------------
//------------------------------------------------
//---------\-.?_.?,/"/-----------------------------
//----------"/.**...l-'-------------------------------
//-----------\...../..\--------------------------------
//------------|.../-\..\-------------------------------
//-----------(_/---\...\------------------------------
//------------------\...\-----------------------------
//-------------------\...\----------------------------
//--------------------\...\----------------------------
//---------------------\...\-----------------------------
//----------------------\...\-------------------------------
//-----------------------\...\--------------------------------
//------------------------\....\-------------------------------
//-------------------------|.....\------------------------------
//-----------------------,-'.....o.\----------------------------
//----------------------/..^^^.....o.'-,-------------------------
//---------------------(..^^^^.........o.'-,-----------------------
//----------------------\..^^^^...........O.\------------------------
//-----------------------\...^^^^^.......O..|-,------------------------
//------------------------\..|...../'-._,-'../---\------------------------
//-------------------------|..\...|-----\...|---#-------------------------
//--------------------------\.|../------|../------------------------------
//---------------------------\|.|-------\.|------------------------------
//----------------------------|/--------|/-----------------------------
//-------------------------------------------------------------------
//

    /*for (int i = 0; i < n; i++) {
        if (isAttainable[i]) {
            cout << "+" << " ";
        } else {
            cout << " - ";
        }
    }
    cout << endl;*/

	for (int i = 0; i < n; i++) {
        if (d[s - 1][i] == -doHuya) {
            fout << "-" << endl;
        } else if (d[s - 1][i] == doHuya) {
            fout << "*" << endl;
        } else {
            fout << d[s - 1][i] << endl;
        }
	}

    fin.close();
    fout.close();

    return 0;
}
