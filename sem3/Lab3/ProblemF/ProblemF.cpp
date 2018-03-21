#include <bits/stdc++.h>

using namespace std;

class vert {
public:
    int length; //length of longest string from this eq class
    int sl; // suffics link
    map<char, int> to; //map of out edges
    bitset<10> symbols;
    vert() {}

    vert(int new_length, int new_sl) {
        length = new_length;
        sl = new_sl;
    }

    vert(int new_length, int new_sl, map<char, int> new_to) {
        length = new_length;
        sl = new_sl;
        to = new_to;
    }
};

vector<vert> sa;
vector<bool> used;
vector<bitset<10> > bs;
int pre;

void create() {
    pre = 0;
    sa.emplace_back(0, -1);
}

void add_char(char c) {

    cout << "char = " << c;
    int cur_v = sa.size();
    sa.emplace_back(sa[pre].length + 1, 0);
    cout << "   new size = " << sa.size() << "   new lenght= " << sa[sa.size() - 1].length << endl;
    int p;
    for (p = pre; p != -1 && !sa[p].to.count(c); p = sa[p].sl) {
        cout << " in for p = " << p << endl;
        sa[p].to[c] = cur_v;
    }

    cout << "p = " << p << "   sa[p].to.size() = " << sa[p].to.size() << endl;
    if (p == -1) {
        sa[cur_v].sl = 0;
    } else {
        int q = sa[p].to[c];
        cout << "q = " << q << endl;
        if (sa[p].length + 1 == sa[q].length) {
            sa[cur_v].sl = q;
        } else {
            sa.emplace_back(sa[q].length + 1, sa[q].sl, sa[q].to);
            cout << "new size = " << sa.size() << endl;

            for (; p != -1 && sa[p].to[c] == q; p = sa[p].sl) {
                sa[p].to[c] = sa.size() - 1;
            }
            cout << "q = " << q << endl;
            sa[q].sl = sa.size() - 1;
            sa[cur_v].sl = sa.size() - 1;

            for (int i = 0; i < sa.size(); i++) {
                cout << sa[i].sl << " ";
            }
            cout << endl;
        }

    }

    pre = cur_v;
    for (int i = 0; i < sa.size(); i++) {
        cout << sa[i].sl << " ";
    }
    cout << endl;
}

bitset<10> dfs(int cur_v, char sym) {
    used[cur_v] = true;
    if (sym < 10) {
        bs[cur_v][sym] = 1;
    }
    for (auto elem : sa[cur_v].to) {
        if (!used[elem.second]) {
            bs[cur_v][sym] |= dfs(elem.second, elem.first);
        } else {

        }
    }


}

int main() {

    ifstream fin("substr3.in");
    ofstream fout("substr3.out");

    int n;
    fin >> n;

    string s = "", temp_s;
    getline(fin, temp_s);
    for (int i = 0; i < n; i++) {
        getline(fin, temp_s);
        s += temp_s;
        s += (char) i;
    }
    cout << s << endl;
    //fin >> s;
    //s = "abcbc";
    create();

    for (int i = 0; i < sa.size(); i++) {
        cout << "i = " << i <<  "   length = " << sa[i].length << "   link = " << sa[i].sl << endl;
        cout << "map: " << endl;
        for (auto elem: sa[i].to) {
            cout << "     " << elem.first << "     " << elem.second << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < s.size(); i++) {
        add_char(s[i]);
    }

    for (int i = 0; i < sa.size(); i++) {
        cout << "i = " << i <<  "   length = " << sa[i].length << "   link = " << sa[i].sl << endl;
        cout << "map: " << endl;
        for (auto elem: sa[i].to) {
            cout << "     " << elem.first << "     " << elem.second << endl;
        }
        cout << endl;
    }

    used.assign(sa.size(), false);
    bs.resize(sa.size());
    dfs(0);

    fin.close();
    fout.close();

    return 0;
}
