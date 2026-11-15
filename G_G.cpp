// OMI_14
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long int
#define ull unsigned long long int
#define faster                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// unordered_map<ll, ll> mp;
// mp.reserve(1024);
// mp.max_load_factor(1);
// double pi = 2.0 * acos(0.0);
const int N = 1003;
ll dp[11][N][N];
int m, n;
const int mod = 1e9 + 7;
ll func(int inx, int a, int b)
{
    if (inx == m)
    {
        return a <= b;
    }
    if (dp[inx][a][b] != -1)
        return dp[inx][a][b];
    ll x = 0;
    for (int i = a; i <= n; i++)
    {
        for (int k = b; k >= i; k--)
        {
            x = (x + func(inx + 1, i, k)) % mod;
        }
    }
    return dp[inx][a][b] = x;
}
int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);

    int t = 1;
    //   cin >> t;
    while (t--)
    {
        cin >> n >> m;
        memset(dp, -1, sizeof(dp));
        cout << func(0, 1, n) << "\n";
        ;
    }
    //  fclose(stdin);
    //  fclose(stdout);

    return 0;
}
