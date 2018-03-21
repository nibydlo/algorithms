#include <bits/stdc++.h>

using namespace std;

int main() {
    string s, t;
    cin >> t;
    cin >> s;
    s = t + '#' + s;
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
    int res = 0;
    /*for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;*/
    vector<int> resVec;
    for (int i = t.length() + 1; i < s.length(); i++) {
        if (ans[i] == t.length()) {
            res++;
            resVec.push_back(i + 1 - 2*t.length());
        }
    }
    cout << res << endl;
    for (int i = 0; i < resVec.size(); i++) {
        cout << resVec[i] << " ";
    }
    cout << endl;
}
