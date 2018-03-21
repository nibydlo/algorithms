#include <bits/stdc++.h>

using namespace std;

int po = 28; //power of alphabet
vector<int> sc, cl, pl, plt, clt, sct; //sc - symbol count, cl - classes, pl - places, plt - temp places, clt - temp classes, sct - temp symbol count
int s1_size;

int main() {

    ifstream fin("common.in");
    ofstream fout("common.out");

    //string s;
    string s1, s2, s;
    getline(fin, s1);
    s1_size = s1.size();
    getline(fin, s2);
    s = s1 + '`' + s2 + (char)95;
    char c = ' ';
    /*while (!fin.eof()) {
        fin >> c;
        s.push_back(c);
    }*/
    //s.pop_back();
    //s.push_back('`');

    // zero step
    int temp_shit = s.size();
    po = max(po, temp_shit);
    sc.resize(po);
    pl.resize(s.size());
    cl.resize(s.size());

    for (int i = 0; i < s.size(); i++) { sc[s[i] - 95]++; }

    for (int i = 1; i < po; i++) { sc[i] += sc[i - 1]; }

    for (int i = 0; i < s.size(); i++) {
        sc[s[i] - 95]--;
        pl[sc[s[i] - 95]] = i;
    }

    cl[pl[0]] = 0;
    int cl_int = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[pl[i]] != s[pl[i - 1]]) { cl_int++; }
        cl[pl[i]] = cl_int - 1;
    }


        /*cout << "first step: ";
        for (int i = 0; i < s.size(); i++) {
            cout << pl[i] + 1 << " ";
        }
        cout << endl;*/

    plt.resize(s.size());
    clt.resize(s.size());


   /* cout << "pl: ";
        for (int k = 0; k < pl.size(); k++) {
            cout << pl[k] << " ";
        }
        cout << endl;
        cout << "cl: ";
        for (int k = 0; k < cl.size(); k++) {
            cout << cl[k] << " ";
        }
        cout << endl;*/

    for (int i = 1; i < s.size(); i*=2) {



        int i2 = i;
        for (int j = 0; j < s.size(); j++) {
            plt[j] = pl[j] - i2;
            if (plt[j] < 0) {
                plt[j] += s.size();
            }
        }

        sc.assign(po, 0);
        for (int j = 0; j < s.size(); j++) {
            sc[cl[plt[j]]]++;
        }
        for (int j = 1; j < cl_int; j++) {
            sc[j] += sc[j - 1];
        }
        for (int j = s.size() - 1; j >= 0; j--) {
            sc[cl[plt[j]]]--;
            pl[sc[cl[plt[j]]]] = plt[j];

        }


        clt[pl[0]] = 0;
        cl_int = 1;

        for (int j = 1; j < s.size(); j++) {
            if (cl[pl[j]] != cl[pl[j - 1]]) {
                cl_int++;
            } else {
                int m1 = (pl[j] + i2) % s.size();
                int m2 = (pl[j - 1] + i2) % s.size();
                if (cl[m1] != cl[m2]) { cl_int++; }
            }
            clt[pl[j]] = cl_int - 1;
        }

        for (int j = 0; j < cl.size(); j++) {
            cl[j] = clt[j];
        }
        /*cout << "i = " << i << endl;
        cout << "plt: ";
        for (int k = 0; k < plt.size(); k++) {
            cout << plt[k] << " ";
        }
        cout << endl;
        cout << "clt: ";
        for (int k = 0; k < clt.size(); k++) {
            cout << clt[k] << " ";
        }
        cout << endl;
        for (int k = 0; k < s.size(); k++) {
            cout << pl[k] + 1 << " ";
        }
        cout << endl;*/
    }

    for (int i = 1; i < s.size(); i++) {
        cout << pl[i] << " ";
    }
    cout << endl;

    //building lcp
    int cur_lcp = 0;

    vector<int> lcp(s.size()), lcp_r(s.size());
    for (int i = 0; i < s.size(); i++) {
        lcp_r[pl[i]] = i;
    }
    for (int i = 0; i < s.size(); i++) {
        if (cur_lcp > 0) { cur_lcp--; }
        if (lcp_r[i] != s.size() - 1) {
            while (s[i + cur_lcp] == s[pl[lcp_r[i] + 1] + cur_lcp] && max(i, pl[lcp_r[i] + 1]) + cur_lcp < s.size()) {
                cur_lcp++;
            }
            lcp[lcp_r[i]] = cur_lcp;
        }
    }

    for (int i = 1; i < lcp.size() - 1; i++) {
        cout << lcp[i] << " ";
    }
    cout << endl;

    int mm = 1;
    for (int i = 1; i < lcp.size() - 1; i++) {
        //cout << "i = " << i << "  lcp[i] = " << lcp[i] << "   lcp[mm] = " << lcp[mm] << endl;
       // cout << "pl[i] - s1.size() = " << pl[i] - s1_size << "   pl[mm] - s1.size() = " << pl[i + 1] - s1_size << endl;
        if (lcp[i] > lcp[mm] && (pl[i] - s1_size)*(pl[i + 1] - s1_size) < 0) {
            //cout << "lcp[i] = " << lcp[i] << "   lcp[mm] = " << lcp[mm] << endl;
            //cout << "now mm = " << i << endl;
            mm = i;
        }
    }
    //cout << "mm = " << mm << endl;
    //cout << "lcp[mm] = " << lcp[mm] << endl;
    for (int i = 0; i < lcp[mm]; i++) {
        fout << s[pl[mm] + i];
    }
    fout << endl;

    fin.close();
    fout.close();

    return 0;
}
