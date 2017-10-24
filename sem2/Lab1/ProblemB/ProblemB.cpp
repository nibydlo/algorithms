#include <iostream>
#include <fstream>

using namespace std;

int iter = 0;

void printSeq(int **prevR, int **prevC, int *a1, int i, int j, int *result) {
    if (i == 0 || j == 0) return;
    if (prevR[i][j] == i - 1 && prevC[i][j] == j - 1) {
        printSeq(prevR, prevC, a1, i - 1, j - 1, result);
        //fout << a1[i - 1] << " ";
        result[iter] = a1[i - 1];
        iter++;
    } else {
        if (prevR[i][j] == i - 1 && prevC[i][j] == j) {
            printSeq(prevR, prevC, a1, i - 1, j, result);
        }
        else {
            printSeq(prevR, prevC, a1, i, j - 1, result);
        }
    }
}

int main() {

    ifstream fin("lcs.in");
    int l1, l2;

    fin >> l1;
    int *a1 = new int[l1];
    for (int i = 0; i < l1; i++) fin >> a1[i];

    fin >> l2;
    int *a2 = new int[l2];
    for (int i = 0; i < l2; i++) fin >> a2[i];

    int **lcs = new int*[l1 + 1];
    int **prevR = new int*[l1 + 1];
    int **prevC = new int*[l1 + 1];
    for (int i = 0; i <= l1; i++){
        lcs[i] = new int[l2 + 1];
        prevR[i] = new int[l2 + 1];
        prevC[i] = new int[l2 + 1];
    }

    for (int i = 1; i <= l1; i++) lcs[i][0] = 0;
    for (int i = 0; i <= l2; i++) lcs[0][i] = 0;

    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            if (a1[i - 1] == a2[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                prevR[i][j] = i - 1;
                prevC[i][j] = j - 1;
            } else {
                if (lcs[i - 1][j] >= lcs[i][j - 1]) {
                    lcs[i][j] = lcs[i - 1][j];
                    prevR[i][j] = i - 1;
                    prevC[i][j] = j;
                } else {
                    lcs[i][j] = lcs[i][j - 1];
                    prevR[i][j] = i;
                    prevC[i][j] = j - 1;
                }
           }
        }
    }

    ofstream fout("lcs.out");
    //cout << lcs[l1][l2] << endl;
    fout << lcs[l1][l2] << endl;
    int *result = new int[lcs[l1][l2]];
    printSeq(prevR, prevC, a1, l1, l2, result);

    for (int i = 0; i < lcs[l1][l2]; i++) {
        fout << result[i] << " ";
    }
    fin.close();
    fout.close();

    return 0;
}
