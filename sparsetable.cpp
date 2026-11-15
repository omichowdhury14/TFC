#include <bits/stdc++.h>
using namespace std;

// 0-indexed Sparse Table for Idempotent Operations (Min, Max, GCD, etc.)
template <typename T>
struct SparseTable {
    int n;
    int max_log;
    vector<vector<T>> st;
    vector<int> lg;

    // Change this function depending on the problem (min, max, gcd, etc.)
    T combine(T a, T b) const {
        return min(a, b); 
    }

    SparseTable() {}

    SparseTable(const vector<T>& a) {
        init(a);
    }

    void init(const vector<T>& a) {
        n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }

        max_log = lg[n] + 1;
        st.assign(max_log, vector<T>(n));

        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // Query in range [L, R] inclusive -> O(1)
    T query(int L, int R) const {
        if (L > R) swap(L, R);
        int j = lg[R - L + 1];
        return combine(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

// --- Example Usage ---
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> arr = {1, 3, -2, 8, -7, 0, 5, 2};
    SparseTable<int> st(arr);

    // Query min in range [1, 4] -> arr[1...4] = {3, -2, 8, -7} -> result = -7
    cout << "Min in range [1, 4]: " << st.query(1, 4) << "\n";

    // Query min in range [0, 2] -> arr[0...2] = {1, 3, -2} -> result = -2
    cout << "Min in range [0, 2]: " << st.query(0, 2) << "\n";

    return 0;
}