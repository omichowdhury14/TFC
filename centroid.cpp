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
const int N = 1e5 + 10;
const int LOGN = 20;
const int INF = 1e9;
int dead[N], sub[N], ans[N], cen_par[N], depth[N];
int up[N][LOGN];
vector<int> adj[N];
void dfs_lca(int vertex, int par, int d)
{
    depth[vertex] = d;
    up[vertex][0] = par;
    for (int i = 1; i < LOGN; i++)
    {
        if (up[vertex][i - 1] != -1)
            up[vertex][i] = up[up[vertex][i - 1]][i - 1];
        else
            up[vertex][i] = -1;
    }
    for (auto child : adj[vertex])
    {
        if (child == par)
            continue;
        dfs_lca(child, vertex, d + 1);
    }
}

int get_lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--)
    {
        if (u != -1 && depth[u] - (1 << i) >= depth[v])
            u = up[u][i];
    }
    if (u == v)
        return u;
    for (int i = LOGN - 1; i >= 0; i--)
    {
        if (up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int get_dist(int u, int v)
{
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

void dfs(int vertex, int par)
{
    sub[vertex] = 1;
    for (auto child : adj[vertex])
    {
        if (child == par || dead[child])
            continue;
        dfs(child, vertex);
        sub[vertex] += sub[child];
    }
}

ll get_cen(int vertex, int par, int siz)
{
    for (auto child : adj[vertex])
    {
        if (child == par || dead[child])
            continue;
        if (sub[child] > siz / 2)
        {
            return get_cen(child, vertex, siz);
        }
    }
    return vertex;
}
void decompose(int vertex, int p)
{
    dfs(vertex, -1);
    int cen = get_cen(vertex, -1, sub[vertex]);
    cen_par[cen] = p;
    dead[cen] = 1;
    for (auto child : adj[cen])
    {
        if (dead[child])
            continue;
        decompose(child, cen);
    }
}
void func(int vertex)
{
    int cur = vertex;
    while (cur != 0)
    {
        ans[cur] = min(ans[cur], get_dist(vertex, cur));
        cur = cen_par[cur];
    }
}

int query(int vertex)
{
    int cur = vertex;
    int mn = INF;
    while (cur != 0)
    {
        mn = min(mn, get_dist(vertex, cur) + ans[cur]);
        cur = cen_par[cur];
    }
    return mn;
}

int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);
    int t = 1;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n - 1; i++)
        {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        memset(up, -1, sizeof(up));
        dfs_lca(1, -1, 0);
        decompose(1, 0);
        for (int i = 1; i <= n; i++)
        {
            ans[i] = INF;
        }
        func(1);
        while (m--)
        {
            int ty, vertex;
            cin >> ty >> vertex;
            if (ty == 1)
            {
                func(vertex);
            }
            else
            {
                cout << query(vertex) << "\n";
            }
        }
    }
    //  fclose(stdin);
    //  fclose(stdout);
    return 0;
}