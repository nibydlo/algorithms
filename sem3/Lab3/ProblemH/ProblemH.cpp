#include <bits/stdc++.h>

using namespace std;

int n;
string s;
string t;
class vert {
public:
    bool terminated = false;
    int term = -1;
    set<int> term_set;
    map<char, int> next;
    map<char, int> next2;
    pair<int, char> batya;
    int sl = -1;//suffix link
    int shl = -1;//short link

    vert() {}

    vert(char c, int prev, char prevc, int new_sl, vector<vert> & verts, int cur_v) {
        verts[cur_v].next.insert(make_pair(c, verts.size()));
        batya.first = prev;
        batya.second = prevc;
        sl = new_sl;
    }
};


vector<vert> verts(1);


int step(int cur_v, char sym);

int sl_getter(int cur_v) {
    if (verts[cur_v].sl == -1) {
        if (cur_v == 0 || verts[cur_v].batya.first == 0) {
            verts[cur_v].sl = 0;
        } else {
            verts[cur_v].sl = step(sl_getter(verts[cur_v].batya.first), verts[cur_v].batya.second);
        }
    }
    return verts[cur_v].sl;
}

int step(int cur_v, char sym) {
    //cout << "sym = " << sym << " cur_v = " << cur_v << endl;
    if (!verts[cur_v].next2.count(sym)) {
        if (verts[cur_v].next.count(sym)) {
            verts[cur_v].next2.insert(make_pair(sym, verts[cur_v].next[sym]));
        } else {
            //cout << "run else" << endl;
            verts[cur_v].next2.insert(make_pair(sym, (cur_v == 0 ? 0 : step(sl_getter(cur_v), sym))));
        }
    }
    return verts[cur_v].next2[sym];
}


int shl_getter(int cur_v) {

    if (verts[cur_v].shl == -1) {
        if (cur_v == 0 || verts[cur_v].batya.first == 0 || verts[cur_v].sl == 0) {
            verts[cur_v].shl = 0;
        } else if (verts[verts[cur_v].sl].term != -1) {
            verts[cur_v].shl = verts[cur_v].sl;
        } else {
            verts[cur_v].shl = shl_getter(verts[cur_v].sl);//step(shl_getter(verts[cur_v].batya.first), verts[cur_v].batya.second);
        }
    }
    return verts[cur_v].shl;
}

int step_shl(int cur_v, char sym) {
    //cout << "sym = " << sym << " cur_v = " << cur_v << endl;
    if (!verts[cur_v].next2.count(sym)) {
        if (verts[cur_v].next.count(sym)) {
            verts[cur_v].next2.insert(make_pair(sym, verts[cur_v].next[sym]));
        } else {
            //cout << "run else" << endl;
            verts[cur_v].next2.insert(make_pair(sym, (cur_v == 0 ? 0 : step(shl_getter(cur_v), sym))));
        }
    }
    return verts[cur_v].next2[sym];
}

set<int> terms(int cur_v) {
    if (verts[cur_v].terminated) {
        return verts[cur_v].term_set;
    }
    set<int> ans;
    ans.insert(verts[cur_v].term_set.begin(), verts[cur_v].term_set.end());

    if (verts[cur_v].shl != 0) {
        set<int> ans2;
        if (!verts[verts[cur_v].shl].terminated) {
            ans2 = terms(verts[cur_v].shl);
        } else {
            ans2 = verts[verts[cur_v].shl].term_set;
        }
        ans.insert(ans2.begin(), ans2.end());

    }
    verts[cur_v].term_set = ans;
    verts[cur_v].terminated = true;
    return ans;
}

int main() {

    ifstream fin("search5.in");
    ofstream fout("search5.out");

    fin >> n;
    getline(fin, s);
    //s.resize(n);
    for (int i = 0; i < n; i++) {
        getline(fin, s);
        //cout << "s[" << i << "] = " << s << endl;
        int j = 0;
        for (int k = 0; k < s.size(); k++) {
            if (!verts[j].next.count(s[k])) {
                verts.emplace_back(s[k], j, s[k], -1, verts, j);
            }
            j = verts[j].next[s[k]];
        }
        verts[j].term = i;
        verts[j].term_set.insert(i);
    }

    for (int i = 0; i < verts.size(); i++) {
        verts[i].sl = sl_getter(i);
        //cout << "i = " << i << "  sl = " << verts[i].sl << endl;
    }

    //


    for (int i = 0; i < verts.size(); i++) {
        verts[i].shl = shl_getter(i);
        //cout << " i = " << i << " shl = " << verts[i].shl << " sl = " << verts[i].sl << endl;
    }

    fin >> t;

    vector<int> result(n, 0);
    int cur_v = 0, ccur;
    for (int i = 0; i < t.size(); i++) {
        cur_v = step(cur_v, t[i]);
        //cout << "cur_v = " << cur_v << endl;
        set<int> ans = terms(cur_v);
        for (auto elem : ans) {
            result[elem]++;
        }
    }

    /*for (int i = 0; i < verts.size(); i++) {
        cout << "i = " << i << "  term_set: ";
        for (auto elem: verts[i].term_set) {
            cout << elem << " ";
        }
        cout << endl;
        //verts[i].term_set = terms(i);
    }*/

   /* for (int i = 0; i < verts.size(); i++) {
        cout << "i = " << i << "  term_set: ";
        for (auto elem : verts[i].term_set) {
            cout << elem << " ";
        }
        cout << endl;
    }*/

    /*
    int cur_v = 0;
    for (int i = 0; i < t.size(); i++) {
        cur_v = step(cur_v, t[i]);
        for (auto elem : verts[cur_v].term_set) {
            result[elem]++;
        }
    }*/



    //cout << "result: " << endl;
    for (int i = 0; i < n; i++) {
        fout << result[i] << endl;
    }

    fin.close();
    fout.close();
}
