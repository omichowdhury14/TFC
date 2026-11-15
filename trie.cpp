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
const ll mx = 6200005;
ll dp[mx], tr[mx][2], cnt[mx][2], cc = 1;
void insert(ll x)
{
  int cur = 0;
  for (ll i = 30; i >= 0; i--)
  {
    int b = (x >> i) & 1;
    if (tr[cur][b] == 0)
    {
      tr[cur][b] = cc++;
    }
    cnt[cur][b]++;
    cur = tr[cur][b];
  }
}

ll func(ll dep, int cur)
{
  if (dep < 0)
    return 0;
  int left = cnt[cur][0], right = cnt[cur][1];
  ll x;
  if (left && right)
  {
    x = min(func(dep - 1, tr[cur][0]) + right - 1, func(dep - 1, tr[cur][1]) + left - 1);
    return x;
  }
  if (left)
  {
    x = func(dep - 1, tr[cur][0]);
    return x;
  }
  else
  {
    x = func(dep - 1, tr[cur][1]);
    return x;
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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
      ll x;
      cin >> x;
      insert(x);
    }
    cout << func(30, 0) << "\n";
  }
  //  fclose(stdin);
  //  fclose(stdout);

  return 0;
}
