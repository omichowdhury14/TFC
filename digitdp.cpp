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
ll dp[20][2][3];
vector<int> digit;
int len;
ll func(int inx, int tight, int ok)
{
    if (inx > (len - 1) / 2)
    {
        if (!tight)
            return 1;
        return (ok != 2);
    }
    if (dp[inx][tight][ok] != -1)
        return dp[inx][tight][ok];
    int limit = tight ? digit[inx] : 9;
    ll ans = 0;
    for (int d = 0; d <= limit; d++)
    {
        if (inx == 0 && d == 0)
            continue;
        int nt = (tight & (digit[inx] == d));
        int nok = ok;
        if (d > digit[len - inx - 1])
            nok = 2;
        else if (d < digit[len - inx - 1])
            nok = 1;
        ans += func(inx + 1, nt, nok);
    }
    return dp[inx][tight][ok] = ans;
}
ll solve(ll n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    digit.clear();
    while (n)
    {
        digit.push_back(n % 10);
        n /= 10;
    }
    reverse(digit.begin(), digit.end());
    len = digit.size();
    ll tot = 0;
    for (int i = 1; i < len; i++)
    {
        ll h = (i - 1) / 2;
        ll way = 9;
        for (ll k = 0; k < h; k++)
        {
            way *= 10LL;
        }
        tot += way;
    }
    memset(dp, -1, sizeof(dp));
    tot += func(0, 1, 0);
    return tot + 1;
}
int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);

    int t = 1;
    cin >> t;
    int pp = 0;
    while (t--)
    {
        ll l, r;
        cin >> l >> r;
        cout << "Case " << pp + 1 << ": ";
        pp++;
        if (l > r)
            swap(l, r);
        cout << solve(r) - solve(l - 1) << "\n";
    }

    //  fclose(stdin);
    //  fclose(stdout);

    return 0;
}
