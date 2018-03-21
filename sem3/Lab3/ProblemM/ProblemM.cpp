#include <bits/stdc++.h>

using namespace std;

int main() {

    ifstream fin("cyclic.in");
    ofstream fout("cyclic.out");

    string s;
    int temp_shit;
    getline(fin, s);
    temp_shit = s.size();
    s += s;

    //cout << s << endl;
    vector<int> z(s.size());
    z[0] = 0;
    int l = 0, r = 0;

    for (int i = 1; i < s.length(); i++) {
        z[i] = max(min(r - i, z[i - l]), 0);
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    /*for (int i = 1; i < s.length(); i++) {
        cout << z[i] << " ";
    }
    cout << endl;*/

    int coun = 0;
    for (int i = 1; i < temp_shit; i++) {
        if (z[i] >= temp_shit - 1) {
            //nothing
        } else {

            if (s[z[i]] > s[z[i] + i]) {
                //cout << "i = " << i << "  s[z[i]] = " << s[z[i]] << "   s[z[i] + i - 1] = " << s[z[i] + i - 1] << endl;
                coun++;
            }
        }
    }

    fout << coun + 1 << endl;

    fin.close();
    fout.close();
}

