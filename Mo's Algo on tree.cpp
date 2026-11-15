#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAXN = 2e5 + 10;
const int BLOCK = 350;
const int F_Bll = 350;
struct Query
{
    int l, r, lca, id, a, b;
    bool operator<(const Query &other) const
    {
        int b1 = l / BLOCK, b2 = other.l / BLOCK;
        if (b1 != b2)
            return b1 < b2;
        return (b1 & 1) ? (r < other.r) : (r > other.r);
    }
};
int n, q;
int arr[MAXN];
vector<int> adj[MAXN];
int tour[2 * MAXN], tin[MAXN], tout[MAXN], timer = 0;
int depth[MAXN], up[MAXN][20];
void dfs(int u, int p, int d)
{
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < 20; ++i)
    {
        if (up[u][i - 1] != -1)
            up[u][i] = up[up[u][i - 1]][i - 1];
    }

    tin[u] = timer;
    tour[timer++] = u;

    for (int v : adj[u])
    {
        if (v != p)
            dfs(v, u, d + 1);
    }

    tout[u] = timer;
    tour[timer++] = u;
}

int get_lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int i = 19; i >= 0; --i)
    {
        if (depth[u] - (1 << i) >= depth[v])
            u = up[u][i];
    }
    if (u == v)
        return u;
    for (int i = 19; i >= 0; --i)
    {
        if (up[u][i] != -1 && up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
bool vis[MAXN];
int freq[MAXN];
int bit[MAXN];
ll f_cnt[MAXN], s_f[MAXN / F_Bll + 10];
void update(int f, int d)
{
    f_cnt[f] += d;
    s_f[f / F_Bll] += d;
}
int get_sum(int l, int r)
{
    if (l > r)
        return 0;
    int sum = 0;
    int b_l = l / F_Bll, b_r = r / F_Bll;

    if (b_l == b_r)
    {
        for (int i = l; i <= r; ++i)
            sum += f_cnt[i];
    }
    else
    {
        for (int i = l; i < (b_l + 1) * F_Bll; ++i)
            sum += f_cnt[i];
        for (int b = b_l + 1; b < b_r; ++b)
            sum += s_f[b];
        for (int i = b_r * F_Bll; i <= r; ++i)
            sum += f_cnt[i];
    }
    return sum;
}
void toggle(int idx)
{
    int u = tour[idx];
    int val = arr[u];
    if (vis[u])
    {
        update(freq[val], -1);
        freq[val]--;
        if (freq[val] != 0)
        {
            update(freq[val], 1);
        }
    }
    else
    {
        // add(freq[val], -1);
        if (freq[val] != 0)
        {
            update(freq[val], -1);
        }
        freq[val]++;
        update(freq[val], 1);
    }
    vis[u] = !vis[u];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(up, -1, sizeof(up));
    dfs(1, 0, 0);
    vector<Query> qry(q);
    for (int i = 0; i < q; ++i)
    {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        if (tin[u] > tin[v])
            swap(u, v);
        int lca = get_lca(u, v);
        qry[i].id = i;
        if (lca == u)
        {
            qry[i].l = tin[u];
            qry[i].r = tin[v];
            qry[i].lca = 0;
        }
        else
        {
            qry[i].l = tout[u];
            qry[i].r = tin[v];
            qry[i].lca = lca;
        }
        qry[i].a = a;
        qry[i].b = b;
    }

    sort(qry.begin(), qry.end());
    vector<int> ans(q);
    int cur_l = 0, cur_r = -1;
    for (int i = 0; i < q; ++i)
    {
        int L = qry[i].l;
        int R = qry[i].r;
        int lca = qry[i].lca;
        int a = qry[i].a, b = qry[i].b;
        while (cur_l > L)
            toggle(--cur_l);
        while (cur_r < R)
            toggle(++cur_r);
        while (cur_l < L)
            toggle(cur_l++);
        while (cur_r > R)
            toggle(cur_r--);

        if (lca != 0)
        {
            toggle(tin[lca]);
        }
        ans[qry[i].id] = get_sum(a, b);
        if (lca != 0)
        {
            toggle(tin[lca]);
        }
    }

    for (int i = 0; i < q; ++i)
    {
        cout << ans[i] << "\n";
    }
   

    return 0;
}