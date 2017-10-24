#include <iostream>
#include <string>

using namespace std;

int main() {

    string strT;
    string str;

    //cin >> strT;
    getline(cin, strT);
    //cin >> str;
    getline(cin, str);

    bool **d = new bool*[str.length() + 1];
    for (int i = 0; i <= str.length(); i++) {
        d[i] = new bool[strT.length() + 1];
    }

    d[0][0] = true;
    for (int i = 1; i <= str.length(); i++) d[i][0] = false;
    for (int i = 1; i <= strT.length(); i++) {
            if (d[0][i - 1] && strT[i - 1] == '*') {
                d[0][i] = true;
            } else {
                d[0][i] = false;
            }
    }

    for (int i = 1; i <= str.length(); i++) {
        for (int j = 1; j <= strT.length(); j++) {
            if (strT[j - 1] == '*') {
                if (d[i - 1][j - 1] || d[i - 1][j] || d[i][j - 1])
                    d[i][j] = true;
                else
                    d[i][j] = false;
            } else if (strT[j - 1] == '?'){
                d[i][j] = d[i - 1][j - 1];
            } else if (strT[j - 1] == str[i - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else{
                d[i][j] = false;
            }
        }
    }
    if (d[str.length()][strT.length()])
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
