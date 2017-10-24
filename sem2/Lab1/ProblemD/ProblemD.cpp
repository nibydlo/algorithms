#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int min(int a, int b, int c){
    if (a <= b && a <= c) {
        return a;
    } else {
        if (b <= a && b <= c) {
            return b;
        } else {
            return c;
        }
    }
}

int main() {

    ifstream fin("levenshtein.in");
    ofstream fout("levenshtein.out");

    string s1, s2;
    fin >> s1 >> s2;

    int l1 = s1.length();
    int l2 = s2.length();

    char *c1 = new char[l1];
    char *c2 = new char[l2];

    for (int i = 0; i < l1; i++) c1[i] = s1[i];
    for (int i = 0; i < l2; i++) c2[i] = s2[i];

    int ** d = new int*[l1 + 1];
    for (int i = 0; i <= l1; i++) d[i] = new int[l2 + 1];
    for (int i = 0; i <= l1; i++) d[i][0] = i;
    for (int i = 0; i <= l2; i++) d[0][i] = i;

    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            if (c1[i - 1] == c2[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
                //cout << "equals " << i << " " << c1[i - 1] << " " << j << " " << c2[j - 1] << endl;
            } else {
                d[i][j] = min(d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]) + 1;
                //cout << d[i][j] << " ";
            }
        }
        //cout << endl;
    }

    /*for (int i = 0; i <= l1; i++) cout << d[i][0] << " ";
    cout << endl;*/

    /*for (int i = 0; i <= l1; i++){
        for (int j = 0; j <= l2; j++) cout << d[i][j] << " ";
        cout << endl;
    }*/

    fout << d[l1][l2] << endl;

    fin.close();
    fout.close();

    return 0;
}
