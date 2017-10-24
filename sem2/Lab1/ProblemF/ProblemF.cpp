#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {

    ifstream fin("palindrome.in");
    ofstream fout("palindrome.out");

    string s;
    fin >> s;
    int l = s.length();

    int **d = new int*[l];
    int **prevR = new int*[l];
    int **prevC = new int*[l];
    for (int i = 0; i < l; i++) d[i] = new int[l];
    for (int i = 0; i < l; i++) prevR[i] = new int[l];
    for (int i = 0; i < l; i++) prevC[i] = new int[l];
    for (int i = 0; i < l; i++){
        for (int j = 0; j < l; j++)
            d[i][j] = 0;
    }
    //cout << "run" << endl;
    for (int i = 0; i < l; i++){
        d[i][i] = 1;
        d[i][i - 1] = 0;
    }

    int left, right;
    for (int i = 2; i <= l; i++) {
        for (left = 0; left < l - i + 1; left++) {
            right = left + i - 1;
            if (s[left] == s[right]) {
                d[left][right] = d[left + 1][right - 1] + 2;
                prevR[left][right] = left + 1;
                prevC[left][right] = right - 1;
            } else {
                if (d[left + 1][right] >= d[left][right - 1]){
                    d[left][right] = d[left + 1][right];
                    prevR[left][right] = left + 1;
                    prevC[left][right] = right;
                } else {
                    d[left][right] = d[left][right - 1];
                    prevR[left][right] = left;
                    prevC[left][right] = right - 1;
                }
            }
        }
    }

    /*for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++)
            cout << d[i][j] << " ";
        cout << endl;
    }*/

    char *result = new char[d[0][l - 1]];

    left = 0;
    right = l - 1;
    int i = 0;
    /*while (left <= right && i <= d[0][l - 1] / 2){
        if (s[left] == s[right]){
            //cout << left << " " << right << endl;
            result[i] = s[left];
            i++;
        }
        int temp_left = left;
        left = prevR[left][right];
        right = prevC[temp_left][right];
    }

    for (int j = i; j < d[0][l - 1]; j++){
        result[j] = result[i - 2 - (j - i)];
    }*/

    while (left <= right && i < (d[0][l - 1] + 1)/2) {
        if (s[left] == s[right]) {
            //cout << "i = " << i << endl;
            result[i] = s[left];
            result[d[0][l - 1] - 1 - i] = s[left];
            i++;
        }
        int temp_left = left;
        left = prevR[left][right];
        right = prevC[temp_left][right];
    }

    fout << d[0][l - 1] << endl;
    for (int j = 0; j < d[0][l - 1]; j++)
        fout << result[j];
    /*cout << endl;
    cout << i << endl;*/

    fin.close();
    fout.close();

    return 0;
}
