#include <bits/stdc++.h>

using namespace std;

int main() {

    string s;
    cin >> s;
    vector<int> ans(s.size());
    ans[0] = 0;
    for (int i = 1; i < s.length(); i++) {
        int k = ans[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = ans[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        ans[i] = k;
    }
    int bordSize = s.length() - ans.back();
    //cout << "bs = " << bordSize << endl;
    if (s.length() % bordSize == 0) {
        cout << bordSize << endl;
    } else {
        cout << s.size() << endl;
    }
}
