// OMI_14
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
typedef vector<vector<ll>> Matrix;
const int mod = 1e9 + 7;
Matrix multi(Matrix &A, Matrix &B)
{
    int n = A.size();
    Matrix C(n, vector<ll>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {

            for (int j = 0; j < n; j++)
            {

                C[i][j] = (C[i][j] + (A[i][k] * B[k][j])) % mod;
            }
        }
    }
    return C;
}
Matrix BE(Matrix T, ll p)
{
    int n = T.size();
    Matrix res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
    {
        res[i][i] = 1;
    }

    while (p > 0)
    {
        if (p & 1)
            res = multi(res, T);
        T = multi(T, T);
        p >>= 1;
    }
    return res;
}

int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n), c(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> c[i];
        }
        ll p, r, q;
        cin >> p >> q >> r;
        vector<vector<ll>> tem(n + 4, vector<ll>(n + 4, 0));
        for (int i = 0; i < n + 4; i++)
        {
            if (i < n)
            {
                tem[0][i] = c[i];
            }
            else if (i == n)
            {
                tem[0][i] = (p + r + q) % mod;
            }
            else if (i == n + 1)
            {
                tem[0][i] = r;
            }
            else if (i == n + 2)
            {
                tem[0][i] = (2LL * r + q) % mod;
            }
            else
            {
                tem[0][i] = 0;
            }
        }
        for (int i = 1; i < n; i++)
        {
            tem[i][i - 1] = 1;
        }
        tem[n][n] = 1;
        tem[n + 1][n + 1] = 1;
        tem[n + 1][n + 2] = 2;
        tem[n + 1][n + 3] = 1;
        tem[n + 2][n + 2] = 1;
        tem[n + 2][n + 3] = 1;
        tem[n + 3][n + 3] = 1;
        if (k < n)
        {
            cout << a[k] << "\n";
            continue;
        }
        tem = BE(tem, k - n + 1);
        ll ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += (tem[0][i] * a[n - i - 1]);
            ans %= mod;
        }
        ans += tem[0][n];
        ans %= mod;
        ans += ((tem[0][n + 1] * (n - 1) * (n - 1))) % mod;
        ans %= mod;
        ans += (tem[0][n + 2] * (n - 1)) % mod;
        ans %= mod;
        ans += tem[0][n + 3];
        ans %= mod;
        cout << ans << "\n";
    }
    //  fclose(stdin);
    //  fclose(stdout);
     
    return 0;
}
