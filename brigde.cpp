void dfs(int u, int p = -1)
{
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u])
    {
        if (v == p)
            continue;
        if (tin[v])
        {
            // Back-edge
            low[u] = min(low[u], tin[v]);
        }
        else
        {
            // Forward-edge
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // 1. Bridge Condition
            if (low[v] > tin[u])
            {
                // edge(u, v) is a bridge
            }

            // 2. Articulation Point Condition (Non-root)
            if (low[v] >= tin[u] && p != -1)
            {
                is_cut_vertex[u] = true;
            }
            children++;
        }
    }
    // 3. Articulation Point Condition (Root)
    if (p == -1 && children > 1)
    {
        is_cut_vertex[u] = true;
    }
}
