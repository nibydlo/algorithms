#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
long long dp[18][(1<<18)];
long long g[18][18];
const long long inf =1e14;
int a,b,dist,n,m;
int main()
{
    /*freopen("salesman.in","r",stdin);
    freopen("salesman.out","w",stdout);
    ios_base::sync_with_stdio(0);*/
    ifstream cin("salesman.in");
    ofstream cout("salesman.out");
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1<<n); j++)
        {
            dp[i][j] = inf;
        }
    for (int i = 0; i < n; i++)
    {
        dp[i][(1 << i)] =0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = inf;
    for (int i = 0; i < m; i++)
    {

        cin >> a >> b >> dist;
        a--;
        b--;
        g[a][b] = dist;
        g[b][a] = dist;
    }

    for (int j = 1; j < (1 << n); j++)
        for (int i = 0; i < n; i++)
        {
            for (int k =0 ; k < n; k++)
            {
                //cout << " mask = " << j << " i = " << i << " j = " << k << endl;
                if (((1 << k) & j) == 0)
                {
                    dp[k][j ^ (1 << k)] = min(dp[k][j ^ (1 << k)], dp[i][j] + g[i][k]);
                    cout << "first = " << dp[k][j ^ (1 << k)] << " second = " << dp[i][j] + g[i][k] << endl;
                    cout << " if: mask = " << j << " i = " << i << " j = " << k << " d = " << dp[k][j ^ (1 << k)] << endl;
                }
            }
        }
    long long mdist = inf;
    for (int i = 0; i < n; i++)
    {
        mdist = min(mdist,dp[i][(1 << n) - 1]);
    }
    if (mdist < inf)
        cout << mdist;
    else
        cout << -1;
    return 0;
}
