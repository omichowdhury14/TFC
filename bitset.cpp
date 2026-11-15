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
const int N = 1e5 + 2;
const int B = 2048;
int vis[N];
vector<ll> adj[N];
bitset<B> reach[N];
vector<ll> top;
void dfs(int vertex)
{
  vis[vertex] = 1;
  for (auto child : adj[vertex])
  {
    if (vis[child])
      continue;
    dfs(child);
  }
  top.push_back(vertex);
}
int main()
{
  faster;
  // freopen("input.txt","r",stdin);
  // freopen("output1.txt","w",stdout);

  int t = 1;
  while (t--)
  {
    ll n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
      int x, y;
      cin >> x >> y;
      adj[x].push_back(y);
    }
    for (int i = 1; i <= n; i++)
    {
      if (!vis[i])
      {
        dfs(i);
      }
    }
    vector<pair<int, int>> query[n + 1];
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
      int u, v;
      cin >> u >> v;
      query[v].push_back({u, i});
    }
    vector<int> ans(q);
    for (ll L = 1; L <= n; L += B)
    {
      ll R = min(L + B - 1, n);
      for (int i = 1; i <= n; i++)
      {
        reach[i].reset();
      }
      for (int i = L; i <= R; i++)
      {
        reach[i][i - L] = 1;
      }
      for (auto vertex : top)
      {
        for (auto child : adj[vertex])
        {
          reach[vertex] |= reach[child];
        }
      }
      for (int v = L; v <= R; v++)
      {
        for (auto child : query[v])
        {
          int id = child.second;
          int u = child.first;
          ans[id] = reach[u][v - L];
        }
      }
    }
    for (int i = 0; i < q; i++)
    {
      if (ans[i])
      {
        cout << "Yes" << "\n";
      }
      else
      {
        cout << "No" << "\n";
      }
    }
  }
  //  fclose(stdin);
  //  fclose(stdout);

  return 0;
}
