#define ll long long int
const ll N = 2e5 + 10;
const int mod = 998244353;
int aa[N];
struct node
{
    ll sum, set, len;
} t[4 * N];
int better(int i, int j)
{
  if (i == -1)
    return j;
  if (j == -1)
    return i;
  return (aa[i] >= aa[j] ? i : j);
}
struct ST
{
#define lc (n << 1)
#define rc ((n << 1) | 1)
    inline void pull(int n)
    {
        t[n].sum = t[lc].sum + t[rc].sum;
    }
    inline void apply(int n, int val)
    {
        if (val == 1)
        {
            t[n].sum = t[n].len;
            t[n].set = 1;
        }
        else
        {
            t[n].sum = 0;
            t[n].set = 0;
        }
    }

    inline void push(int n)
    {
        if (t[n].set != -1)
        {
            apply(lc,  t[n].set);
            apply(rc, t[n].set);
            t[n].set = -1;
        }
    }
    void build(int n, int b, int e)
    {
        t[n].sum = 0;
        t[n].set = -1;
        t[n].len = e - b + 1;
        if (b == e)
        {
            t[n].sum = aa[b];
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }

    void update(int n, int b, int e, int i, int j, int f)
    {
        if (b > j || e < i)
            return;
        if (b >= i && e <= j)
        {
            apply(n, f);

            return;
        }
        push(n);
        int mid = (b + e) >> 1;
        update(lc, b, mid, i, j, f);
        update(rc, mid + 1, e, i, j, f);
        pull(n);
    }
    ll query(int n, int b, int e, int i, int j)
    {
        if (b > j || e < i)
            return 0;
        if (b >= i && e <= j)
            return t[n].sum;
        push(n);
        int mid = (b + e) >> 1;
        return (query(lc, b, mid, i, j) + query(rc, mid + 1, e, i, j));
    }
} seg;
