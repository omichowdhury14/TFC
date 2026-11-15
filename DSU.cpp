struct DSU
{
    vector<int> parent;
    vector<int> sz;
    DSU(int n)
    {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int v)
    {
        if (parent[v] == v)
            return v;
        return parent[v] = find(parent[v]);
    }
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a != b)
        {
            if (sz[a] < sz[b])
            {
                swap(a, b);
            }

            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};