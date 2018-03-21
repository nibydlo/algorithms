/*        .                .
            :"-.          .-";
            |:`.`.__..__.'.';|
            || :-"      "-; ||
            :;              :;
            /  .==.    .==.  \
           :      _.--._      ;
           ; .--.' `--' `.--. :
          :   __;`      ':__   ;
          ;  '  '-._:;_.-'  '  :
          '.       `--'       .'
           ."-._          _.-".
         .'     ""------""     `.
        /`-                    -'\
       /`-                      -'\
      :`-   .'              `.   -';
      ;    /                  \    :
     :    :                    ;    ;
     ;    ;                    :    :
     ':_:.'                    '.;_;'
        :_                      _;
        ; "-._                -" :`-.     _.._
        :_          ()          _;   "--::__. `.
         \"-                  -"/`._           :
        .-"-.                 -"-.  ""--..____.'
       /         .__  __.         \
      : / ,       / "" \       . \ ;
       "-:___..--"      "--..___;-"      */

#include <bits/stdc++.h>

using namespace std;

int k;
int po = (126 - 30); //power of alphabet
vector<int> sc, cl, pl, plt, clt, sct; //sc - symbol count, cl - classes, pl - places, plt - temp places, clt - temp classes, sct - temp symbol count

vector<long long> p;
vector<long long> h;

void prep(vector<char> s) {

    p.resize(s.size());
    h.resize(s.size());
    p[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        p[i] = p[i - 1] * 127;
    }

    h[0] = s[0];
    for (int i = 1; i < s.size(); i++) {
        h[i] = h[i - 1] + s[i] * p[i];
    }
}

bool eq(int a, int b, int c, int d) {

    long long h1 = h[b];
    if (a != 0) {
        h1 -= h[a - 1];
    }

    long long h2 = h[d];
    if (c != 0) {
        h2 -= h[c - 1];
    }

    if (h1 * p[c] == h2 * p[a] || (a == c && b == d)) {
        //cout << "Yes" << endl;
        return true;
    } else {
        //cout << "No" << endl;
        return false;
    }
}

int main() {

    ifstream fin("shifts.in");
    ofstream fout("cyclic.out");

    string s1;
    vector<char> s;
    char c = ' ';
    /*while ( fin.peek() != '\n') {
        fin >> c;
        s.push_back(c);
    }*/
    getline(fin, s1);
    int temp_shit = s1.size();
    //int temp_shit = s1.size();
    for (int i = 0; i < s1.size(); i++) {
        s.push_back(s1[i]);
    }

    fin >> k;

    //doubling
    int temps = s.size();
    for (int i = 0; i < temps; i++) {
        s.push_back(s[i]);
    }

    //s.push_back(31);
    /*for (int i = 0; i < s.size(); i++) {
        cout << s[i];
    }
    cout << endl;*/

    //creating hashes
    prep(s);

    // zero step

    po = max(po, temp_shit);
    sc.resize(po);
    pl.resize(s.size());
    cl.resize(s.size());

    for (int i = 0; i < s.size(); i++) { sc[s[i] - 31]++; }
    /*cout << "sc: ";
    for (int i = 0; i < po; i++) {
        cout << sc[i] << " ";
    }
    cout << endl;*/

    for (int i = 1; i < po; i++) { sc[i] += sc[i - 1]; }

    /*cout << "sc: ";
    for (int i = 0; i < po; i++) {
        cout << sc[i] << " ";
    }
    cout << endl;*/

    for (int i = 0; i < s.size(); i++) {
        sc[s[i] - 31]--;
        pl[sc[s[i] - 31]] = i;
    }

    cl[pl[0]] = 0;
    int cl_int = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[pl[i]] != s[pl[i - 1]]) { cl_int++; }
        cl[pl[i]] = cl_int - 1;
    }

    /*cout << "pl: ";
    for (int i = 0; i < s.size(); i++) {
        cout << pl[i] << " ";
    }
    cout << endl;

    cout << "cl: ";
    for (int i = 0; i < s.size(); i++) {
        cout << cl[i] << " ";
    }
    cout << endl;

    cout << "sc: ";
    for (int i = 0; i < po; i++) {
        cout << sc[i] << " ";
    }
    cout << endl;*/

    plt.resize(s.size());
    clt.resize(s.size());

    for (int i = 1; i < s.size(); i*=2) {



        int i2 = i;
        for (int j = 0; j < s.size(); j++) {
            plt[j] = pl[j] - i2;
            if (plt[j] < 0) {
                plt[j] += s.size();
            }
        }

        /*cout << "plt: ";
        for (int j = 0; j < plt.size(); j++) {
            cout << plt[j] << " ";
        }
        cout << endl;*/

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

        /*cout << endl << endl << "cl: ";
        for (int j = 0; j < s.size(); j++) {
            cout << cl[j] << " ";
        }
        cout << endl;

        cout << "pl: ";
        for (int j = 0; j < s.size(); j++) {
            cout << pl[j] << " ";
        }
        cout << endl;*/
    }


    cout << "1111pl: ";
    for (int i = 0; i < s.size(); i++) {
        cout << pl[i] << " ";
    }
    cout << endl;

    cout << "cl: ";
    for (int i = 0; i < s.size(); i++) {
        cout << cl[i] << " ";
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

    /*for (int i = 1; i < lcp.size() - 1; i++) {
        fout << lcp[i] << " ";
    }
    fout << endl;*/

    /*int kk = 1;
    int iter = 1;
    while(pl[iter] >= temps) {
        iter++;
    }
    int prev = iter;
    iter++;
    while(kk != k && iter < pl.size()) {
        if (pl[iter] > temps) {
            iter++;
        }
        else if (!eq(pl[prev], pl[prev] + temps, pl[iter], pl[iter] + temps)) {
            prev = iter;
            kk++;
            iter++;

        } else {
            iter++;
        }
        //cout << "iter = " << iter << "  kk = " << kk << " prev = " << prev << endl;
    }

    iter--;
    //cout << "iter = " << iter << endl;
    //cout << "pl[iter] = " << pl[iter] << endl;
    //cout << "temps = " << temps << endl;
    if (k != kk) {
        fout << "IMPOSSIBLE" << endl;
        return 0;
    }*/
    int iter = -1;
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i] == k - 1) {
            iter = i;
            break;
        }
    }

    /*if (iter == -1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    } else {
        for (int i = iter; i < iter + temps; i++) {
            cout << s[i];
        }
        cout << endl;
    }*/

    /*for (int i = pl[iter]; i < pl[iter] + temps; i++) {
        fout << s[i];
    }
    fout << endl;*/
    cout << "ts = " << temp_shit << endl;
    int iter_2 = 0;
    bool stop = true;
    for (int i = 1; i < pl.size(); i++) {
        if (pl[i] <  temp_shit && stop) {
            cout << "i = " << i << endl;
            iter_2++;
            if (pl[i] == 0) {
                stop = false;
            }
        }
    }
    cout << iter_2 + 1 << endl;

    fin.close();
    fout.close();

    return 0;
}
