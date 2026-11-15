// R4=(r1*r2*r3)/(r1*r2+r1*r3+r2*r3+2*sqrt((r1+r2+r3)*r1*r2*r3));// for inner
// R4=abs((r1*r2*r3)/(r1*r2+r1*r3+r2*r3-2*sqrt((r1+r2+r3)*r1*r2*r3))) for outer
//  OMI_14
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
// double pi = 2.0 * acos(0.0);
int main()
{
    faster;
    // freopen("input.txt","r",stdin);
    // freopen("output1.txt","w",stdout);

    int t = 1;
    cin >> t;
    while (t--)
    {
        double R1, R2, R3;
        cin >> R1 >> R2 >> R3;
        double pi = 2.0 * acos(0.0);
        double a = R1 + R2, b = R2 + R3, c = R3 + R1;
        double theta1 = acos((a * a + c * c - b * b) / (2.0 * a * c));
        double theta2 = acos((a * a + b * b - c * c) / (2.0 * a * b));
        double theta3 = pi - theta1 - theta2;
        double s = (a + b + c) / 2.0;
        double A = sqrt(s * (s - a) * (s - b) * (s - c));
        double ans = A - (0.5 * theta1 * R1 * R1) - (0.5 * theta2 * R2 * R2) - (0.5 * theta3 * R3 * R3);
        cout << fixed << setprecision(6) << ans << "\n";
    }

    //  fclose(stdin);
    //  fclose(stdout);

    return 0;
}
