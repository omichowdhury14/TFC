// OMI_14
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long int
#define ull unsigned long long int
#define faster                      \
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
const int N = 2e5 + 10;
int tin[N], low[N], vis[N], mark[N], n;
vector<int> adj[N], st, g[2 * N];
int t1 = 0;
int cnt = 0;
const int LOG = 20;
int depth[2 * N];
int parent[LOG][2 * N];
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
    for (int v = 1; v <= cnt; v++)
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
void dfs_bt(int u, int p = -1)
{
  st.push_back(u);
  tin[u] = low[u] = ++t1;
  vis[u] = 1;
  for (int v : adj[u])
  {
    if (v == p)
      continue;
    if (vis[v])
    {
      low[u] = min(low[u], tin[v]);
    }
    else
    {
      dfs_bt(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= tin[u])
      {
        cnt++;
        g[cnt].push_back(u);
        g[u].push_back(cnt);
        while (true)
        {
          int x = st.back();
          st.pop_back();
          g[cnt].push_back(x);
          g[x].push_back(cnt);
          if (x == v)
            break;
        }
      }
    }
  }
}
void build()
{
  for (int i = 1; i <= n; i++)
  {
    if (!vis[i])
    {
      dfs_bt(i);
      if (!st.empty())
        st.pop_back();
    }
  }
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
    int m;
    cin >> n >> m;
    cnt = n;
    for (int i = 0; i < m; i++)
    {
      int x, y;
      cin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
    build();
    cout << cnt - n << "\n";
    for (int i = n + 1; i <= cnt; i++)
    {
      sort(g[i].begin(), g[i].end());
      cout << g[i].size() << " ";
      for (auto it : g[i])
        cout << it << " ";
      cout << "\n";
    }
  }

  //  fclose(stdin);
  //  fclose(stdout);

  return 0;
}
