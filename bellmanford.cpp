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
int n, m;
struct edge
{
    ll u, v, w;
};
const ll inf = 1e17;
vector<edge> ed;
ll solve()
{
    vector<ll> dist(n + 1, 0), par(n + 1, 0);
    // distance should be 0 for multisource negative cycle
    vector<ll> neg, sz(n + 1, 0);
    int st = -1;
    for (int i = 0; i < n; i++)
    {
        st = -1;
        for (auto it : ed)
        {
            ll u = it.u, v = it.v, w = it.w;
            if (dist[v] > dist[u] + w)
            {
                if (i == n - 1)
                {
                    st = v;
                }
                par[v] = u;
                dist[v] = max(-inf, dist[u] + w);
            }
        }
    }
    if (st == -1)
    {
        return 0;
    }
    int ans = 1e8;

    int y = st;
    for (int i = 0; i < n; i++)
    {
        y = par[y];
    }
    int cur = y;
    int xx = 0;
    do
    {
        xx++;
        cur = par[cur];
    } while (cur != y);
    ans = min(ans, xx);

    return ans;
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
        for (int i = 0; i < m; i++)
        {
            ll x, y, w1, w2;
            cin >> x >> y >> w1 >> w2;
            edge ed1 = {x, y, -w1}, ed2 = {y, x, -w2};
            ed.push_back(ed1);
            ed.push_back(ed2);
        }
        cout << solve() << "\n";
    }
    //  fclose(stdin);
    //  fclose(stdout);

    return 0;
}
