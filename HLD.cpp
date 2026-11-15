const ll N = 5e5 + 10;
const int mod = 998244353;
ll head[N], pos[N], par[N], heavy[N], sub[N], dep[N], cnt = 0, n;
vector<ll> adj[N];
void dfs(int vertex, int p)
{
    sub[vertex] = 1;
    par[vertex] = p;
    heavy[vertex] = -1;
    dep[vertex] = dep[p] + 1;
    int siz = -1;
    for (auto child : adj[vertex])
    {
        if (child == p)
            continue;
        dfs(child, vertex);
        sub[vertex] += sub[child];
        if (sub[child] > siz)
        {
            siz = sub[child];
            heavy[vertex] = child;
        }
    }
}
void hld(int vertex, int h)
{
    head[vertex] = h;
    pos[vertex] = ++cnt;
    if (heavy[vertex] != -1)
    {
        hld(heavy[vertex], h);
    }
    for (auto child : adj[vertex])
    {
        if (child != par[vertex] && child != heavy[vertex])
        {
            hld(child, child);
        }
    }
}
ll find_max(int u, int v)
{
    ll res = -1;
    while (head[u] != head[v])
    {
        if (dep[head[u]] < dep[head[v]])
            swap(u, v);
        res = max(res, seg.query(1, 1, n, pos[head[u]], pos[u]));
        u = par[head[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    res = max(res, seg.query(1, 1, n, pos[u], pos[v]));
    return res;
}
