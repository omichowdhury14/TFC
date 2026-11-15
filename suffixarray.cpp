// OMI_14
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long int
#define ull unsigned long long int
#define faster                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);
using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// unordered_map<ll, ll> mp;
// mp.reserve(1024);
// mp.max_load_factor(1);
struct SuffixArray
{
    int n;
    vector<int> s;
    vector<int> sa;
    vector<int> rank;
    vector<int> lcp;
    vector<vector<int>> st;
    vector<int> lg;
    SuffixArray(vector<int> &str)
    {
        s = str;
        n = s.size();
        build_sa();
        build_lcp();
        build_sparse_table();
    }
    void build_sa()
    {
        sa.resize(n);
        rank.resize(n);
        vector<int> c(n);

        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++)
            a[i] = {s[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++)
            sa[i] = a[i].second;
        c[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            c[sa[i]] = c[sa[i - 1]] + (a[i].first != a[i - 1].first);
        }

        int k = 0;
        while ((1 << k) < n)
        {
            vector<pair<pair<int, int>, int>> a_next(n);
            for (int i = 0; i < n; i++)
            {
                a_next[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
            }
            sort(a_next.begin(), a_next.end());

            for (int i = 0; i < n; i++)
                sa[i] = a_next[i].second;
            c[sa[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                c[sa[i]] = c[sa[i - 1]] + (a_next[i].first != a_next[i - 1].first);
            }
            k++;
        }
        rank = c;
    }
    void build_lcp()
    {
        lcp.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n; i++)
        {
            if (rank[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i] + 1] = k;
            if (k)
                k--;
        }
    }
    void build_sparse_table()
    {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int max_log = lg[n] + 1;
        st.assign(max_log, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            st[0][i] = lcp[i];

        for (int j = 1; j < max_log; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int query_rmq(int L, int R)
    {
        if (L > R)
            swap(L, R);
        if (L == R)
            return n - 1 - sa[L];
        int j = lg[R - L];
        return min(st[j][L + 1], st[j][R - (1 << j) + 1]);
    }
};
int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);

    int t = 1;
    //   cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<vector<int>> pos(n);
        vector<int> s;
        int cnt = 1;
        vector<string> str(n);
        vector<vector<int>> p(n);
        for (int i = 0; i < n; i++)
        {
            string tem;
            cin >> tem;
            str[i] = tem;
            pos[i].resize(tem.size());
            for (int k = 0; k < tem.size(); k++)
            {
                pos[i][k] = s.size();
                s.push_back((tem[k] - '0') + 100005);
            }
            s.push_back(cnt++);
        }
        SuffixArray suf(s);
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < str[i].size(); k++)
            {
                int st = pos[i][k];
                int rnk = suf.rank[st];
                p[i].push_back(rnk);
            }
            sort(p[i].begin(), p[i].end());
        }

        int q;
        cin >> q;
        while (q--)
        {
            int i, l, r, j;
            cin >> i >> l >> r >> j;
            i--, l--, r--, j--;
            int len = r - l + 1;
            int pp = suf.rank[pos[i][l]];
            // first
            int lo = 0, hi = pp;
            int ans1 = pp;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;
                int tem = suf.query_rmq(mid, pp);
                if (tem >= len)
                {
                    ans1 = mid;
                    hi = mid - 1;
                }
                else
                {
                    lo = mid + 1;
                }
            }
            // sec
            lo = pp, hi = s.size() - 1;
            int ans2 = pp;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;
                int tem = suf.query_rmq(pp, mid);
                if (tem >= len)
                {
                    ans2 = mid;
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }
            auto it1 = upper_bound(p[j].begin(), p[j].end(), ans2);
            auto it2 = lower_bound(p[j].begin(), p[j].end(), ans1);
            cout << it1 - it2 << "\n";
            
        }
    }
    //  fclose(stdin);
    //  fclose(stdout);

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Build Suffix Array using Prefix Doubling O(N log^2 N)
vector<int> buildSuffixArray(const string &s)
{
    int n = s.length();
    vector<int> sa(n), rank(n);
    for (int i = 0; i < n; i++)
    {
        sa[i] = i;
        rank[i] = (unsigned char)s[i]; // Cast to avoid negative values
    }

    for (int k = 1; k < n; k <<= 1)
    {
        auto cmp = [&](int i, int j)
        {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };

        sort(sa.begin(), sa.end(), cmp);

        vector<int> tmp_rank(n);
        tmp_rank[sa[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            tmp_rank[sa[i]] = tmp_rank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = tmp_rank;

        // Optimization: stop early if all ranks are unique
        if (rank[sa[n - 1]] == n - 1)
            break;
    }
    return sa;
}

// 2. Build LCP Array using Kasai's Algorithm O(N)
vector<int> buildLCPArray(const string &s, const vector<int> &sa)
{
    int n = s.length();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
    {
        rank[sa[i]] = i;
    }

    vector<int> lcp(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (rank[i] == 0)
        {
            k = 0;
            continue;
        }
        int j = sa[rank[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
        {
            k++;
        }
        lcp[rank[i]] = k;
        if (k > 0)
            k--; // Decrement k for the next suffix
    }
    return lcp;
}

// 3. Check function for Binary Search
bool check(int L, int N, int K, const vector<int> &SA, const vector<int> &LCP, const vector<int> &owner)
{
    vector<int> freq(K, 0);
    int unique_count = 0;

    auto add = [&](int idx)
    {
        int id = owner[SA[idx]];
        if (id != -1)
        {
            if (freq[id] == 0)
                unique_count++;
            freq[id]++;
        }
    };

    auto remove_all = [&]()
    {
        fill(freq.begin(), freq.end(), 0);
        unique_count = 0;
    };

    // Initialize first element of the block
    add(0);

    for (int i = 1; i < N; ++i)
    {
        if (LCP[i] >= L)
        {
            // Suffix SA[i] shares at least L characters with SA[i-1]
            add(i);
            if (unique_count == K)
                return true;
        }
        else
        {
            // LCP dropped below L -> Reset for next block
            remove_all();
            add(i);
        }
    }
    return false;
}

// 4. Main LCS Solver
int lcsOfKStrings(const vector<string> &strings)
{
    int K = strings.size();
    if (K == 0)
        return 0;
    if (K == 1)
        return strings[0].length();

    string S = "";
    vector<int> owner;

    // Concatenate strings using unique non-printable ASCII characters as separators
    for (int i = 0; i < K; ++i)
    {
        for (char c : strings[i])
        {
            S += c;
            owner.push_back(i);
        }
        // Use non-printable ASCII characters (1, 2, 3...) to avoid collision with standard text
        S += (char)(1 + i);
        owner.push_back(-1); // Separator marker
    }

    int N = S.length();
    vector<int> SA = buildSuffixArray(S);
    vector<int> LCP = buildLCPArray(S, SA);

    int min_len = strings[0].length();
    for (int i = 1; i < K; ++i)
    {
        min_len = min(min_len, (int)strings[i].length());
    }

    // Binary Search on length L
    int low = 1, high = min_len, ans = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (check(mid, N, K, SA, LCP, owner))
        {
            ans = mid;
            low = mid + 1; // Try longer length
        }
        else
        {
            high = mid - 1; // Try shorter length
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Example Test Case
    vector<string> input_strings = {
        "applepie",
        "pineapple",
        "chapel",
        "snapple"};

    int result = lcsOfKStrings(input_strings);
    cout << "Length of Longest Common Substring across all " << input_strings.size()
         << " strings is: " << result << "\n";

    return 0;
}