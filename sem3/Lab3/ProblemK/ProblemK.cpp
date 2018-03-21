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

int po = 27; //power of alphabet
vector<int> sc, cl, pl, plt, clt, sct; //sc - symbol count, cl - classes, pl - places, plt - temp places, clt - temp classes, sct - temp symbol count

int main() {

    ifstream fin("count.in");
    ofstream fout("count.out");

    //string s;
    vector<char> s;
    char c = ' ';
    while (!fin.eof()) {
        fin >> c;
        s.push_back(c);
    }
    s.pop_back();
    s.push_back('`');
    /*for (int i = 0; i < s.size(); i++) {
        cout << s[i];
    }
    cout << endl;*/
    // zero step
    int temp_shit = s.size();
    po = max(po, temp_shit);
    sc.resize(po);
    pl.resize(s.size());
    cl.resize(s.size());

    for (int i = 0; i < s.size(); i++) { sc[s[i] - '`']++; }

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
        sc[s[i] - '`']--;
        pl[sc[s[i] - '`']] = i;
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


    //cout << "pl: ";
    /*for (int i = 1; i < s.size(); i++) {
        cout << pl[i] + 1 << " ";
    }
    cout << endl;*/

    /*cout << "cl: ";
    for (int i = 0; i < s.size(); i++) {
        cout << cl[i] << " ";
    }
    cout << endl;*/

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
        cout << lcp[i] << " ";
    }
    cout << endl;*/

    long long sum1 = 0, sum2 = 0;
    for (int i = 1; i < s.size(); i++) {
        sum1 += (s.size() -1 - pl[i]);
    }

    for (int i = 1; i < lcp.size() - 1; i++) {
        sum2 += lcp[i];
    }
    //cout << "sum1 = " << sum1 << "   sum2 = " << sum2 << endl;
    fout << sum1 - sum2 << endl;

    fin.close();
    fout.close();

    return 0;
}
