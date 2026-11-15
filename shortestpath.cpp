const ll INF = 1e18;
ll dist[200007];
vector<pair<int, int>> adj[200007];
ll n, m, y;
ll x[200005];
void bfs()
{
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>>
        pq;

    dist[1] = 0;
    pq.push({0, 1});
    ll mn = x[1] + y;
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, w] : adj[u])
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}