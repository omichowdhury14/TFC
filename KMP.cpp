const int N = 1e6 + 5;
int n, m;
string s, p;
int pi[N];
void prefix()
{
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j])
        {
            j = pi[j - 1];
        }
        if (p[i] == p[j])
        {
            j++;
        }
        pi[i] = j;
    }
}
ll kmp_search()
{
    ll ans = 0;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && p[j] != s[i])
        {
            j = pi[j - 1];
        }
        if (p[j] == s[i])
        {
            j++;
        }
        if (j == m)
        {
            ans++;
            j = pi[j - 1];
        }
    }
    return ans;
}
void prefix_auto(vector<vector<int>> &aut)
{
    int m = p.size();
    aut[0][p[0] - 'a'] = 1;
    int link = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (i < m && c == (p[i] - 'a'))
            {
                aut[i][c] = i + 1;
            }
            else
            {
                aut[i][c] = aut[link][c];
            }
        }
        if (i < m)
        {
            link = aut[link][p[i] - 'a'];
        }
    }
}