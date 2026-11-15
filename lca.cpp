const int N = 200005;
const int LOG = 20;
vector<int> g[N];
int n;
int depth[N];
int parent[LOG][N];
void dfs(int u, int p)
{
    parent[0][u] = p;

    for (auto v : g[u])
    {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
void build_lca()
{
    for (int i = 1; i < LOG; i++)
    {
        for (int v = 1; v <= n; v++)
        {
            parent[i][v] = parent[i - 1][parent[i - 1][v]];
        }
    }
}
int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++)
    {
        if (diff & (1 << i))
        {
            u = parent[i][u];
        }
    }

    if (u == v)
        return u;
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (parent[i][u] != parent[i][v])
        {
            u = parent[i][u];
            v = parent[i][v];
        }
    }

    return parent[0][u];
}
int dist(int u, int v)
{
    int L = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[L];
}
void pre(int n)
{
  for (int k = 1; k < LOG; k++)
  {
    for (int u = 1; u <= n; u++)
    {
      if (jump[u][k - 1] != -1)
      {
        jump[u][k] = jump[jump[u][k - 1]][k - 1];
      }
      else
      {
        jump[u][k] = -1;
      }
    }
  }
}
int kth(int u, int k)
{
  for (int i = 0; i < LOG; i++)
  {
    if ((k >> i) & 1)
    {
      u = jump[u][i];
      if (u == -1)
        return u;
    }
  }
  return u;
}