#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector <int> > t;

class Node {
public:
    int v;
    int a = 0;
    int b = 0;
    bool passed = false;
};

int dynamic(int pos, Node *nodeArray, int n) {
    if (nodeArray[pos].passed) {
            return max(nodeArray[pos].a, nodeArray[pos].b);
    } else {
        if (nodeArray[pos].v > 0) {
            nodeArray[pos].a = nodeArray[pos].v;
        } else {
            nodeArray[pos].a = 0;
        }
        //cout << "run2" << endl;
        for (int i = 0; i <t[pos].size(); i++) {
            int temp = dynamic(t[pos][i], nodeArray, n);
            if (nodeArray[t[pos][i]].b > 0) {
                nodeArray[pos].a += nodeArray[t[pos][i]].b;
            }
        }
        //cout << "run3" << endl;
        for (int i = 0; i < t[pos].size(); i++) {
            nodeArray[pos].b += dynamic(t[pos][i], nodeArray, n);
        }

        nodeArray[pos].passed = true;

        return max(nodeArray[pos].a, nodeArray[pos].b);
    }
}

int main() {

    ifstream fin("selectw.in");
    ofstream fout("selectw.out");

    int n;
    fin >> n;

    int *p = new int[n];
    int *q = new int[n];

    for (int i = 0; i < n; i++) {
        fin >> p[i] >> q[i];
    }

    Node *nodeArray = new Node[n + 1];
    t.resize(n + 1);
    for (int i = 1; i < n + 1; i++) {
        nodeArray[i].v = q[i - 1];
        t[p[i - 1]].push_back(i);
    }
    //cout << "run" << endl;
    int temp = dynamic(t[0][0], nodeArray, n);
    //for (int i = )
    fout << temp;
    fin.close();
    fout.close();

    return 0;
}
