
#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> ans(s.size());
    ans[0] = 0;
    int l = 0, r = 0;

    for (int i = 1; i < s.length(); i++) {
        ans[i] = max(min(r - i, ans[i - l]), 0);
        while (i + ans[i] < s.length() && s[ans[i]] == s[i + ans[i]]) {
            ans[i]++;
        }
        if (i + ans[i] > r) {
            l = i;
            r = i + ans[i];
        }
    }

    for (int i = 1; i < s.length(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
