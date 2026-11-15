#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // Large enough to act as infinity, safe from overflow when adding two INFs

/**
 * Computes all-pairs shortest paths using the Floyd-Warshall algorithm.
 * @param n    The number of vertices (1-indexed or 0-indexed).
 * @param dist The adjacency matrix, updated in-place to contain shortest paths.
 */
void floyd_warshall(int n, vector<vector<long long>> &dist)
{
    // The outermost loop MUST be the intermediate vertex 'k'
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                // Check if paths through 'k' are valid to prevent using disconnected components
                if (dist[i][k] < INF && dist[k][j] < INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main()
{
    // Optimize standard I/O streams
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; // Vertices, Edges, Queries
    if (cin >> n >> m >> q)
    {

        // Initialize distance matrix with INF and 0 on the diagonal
        vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
        for (int i = 1; i <= n; ++i)
        {
            dist[i][i] = 0;
        }

        // Read edges
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            // If the graph can have multiple edges between the same nodes, keep the minimum weight
            dist[u][v] = min(dist[u][v], w);
            // If the graph is undirected, uncomment the next line:
            // dist[v][u] = min(dist[v][u], w);
        }

        // Run the algorithm
        floyd_warshall(n, dist);

        // Process Queries
        while (q--)
        {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] == INF)
            {
                cout << -1 << "\n"; // Unreachable
            }
            else
            {
                cout << dist[u][v] << "\n";
            }
        }
    }
    return 0;
}