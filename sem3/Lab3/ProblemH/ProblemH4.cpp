#include <bits/stdc++.h>

using namespace std;

int n;
string t;
vector<string> s;

class vert {
public:
    int visits = 0;
    pair<char, *vert> batya;
    vert *sl; //suffix link
    vert *shl; // short suffix link
    bool term = false;
    bool used = false;
    vector<string> classes;
    map<char, *vert> next;

    vert() {}

    vert(vert * new_batya, char sym) {
        batya.first = sym;
        batya.second = new_batya;
        sl = nullptr;
        shl = nullptr;
    }
};

vert *r;



int main() {

    ifstream fin("search5.in");
    ofstream fout("search5.out");

    fin >> n;
    s.resize(n);
    getline(fin, s[0]);

    r = new vert(nullptr, '$');

    for (int i = 0; i < n; i++) {
        getline(fin, s[i]);
        if (repeat.count(s[i]) == 0) {
            repeat[s[i]] = 0;
            result[s[i]] = 0;
            new_branch(s[i]);

            vert * cur_v = r;
            for (auto elem : s[i]) {
                if (!cur_v.next.count(elem)) {
                    cur_v.next.insert(make_pair(elem, new vert(cur_v, elem)));
                }
                cur_v = cur_v.next[elem];
            }
            cur_v.term = true;
            cur_v.classes.push_back(s);
        }
        repeat[s[i]]++;
    }

    vert * cur_v = r;
    for (int i = 0; i < t.size(); i++) {
        cur_v = step(cur_v, t[i]);
        node.visits++;
    }

    fin.close();
    fout.close();

    return 0;
}
