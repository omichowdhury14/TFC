#define MAXN 1000002
vector<int> spf(MAXN + 1, 1);
const ll m = 1e9 + 7;
// SPF
void sieve()
{

    spf[0] = 0;
    for (int i = 2; i <= MAXN; i++)
    {
        if (spf[i] == 1)
        {
            for (int j = i; j <= MAXN; j += i)
            {
                if (spf[j] == 1)
                    spf[j] = i;
            }
        }
    }
}
vector<ll> getFactorization(ll x)
{
    vector<ll> primes;
    while (x > 1)
    {
        int p = spf[x];
        primes.push_back(p);
        while (x % p == 0)
            x /= p;
    }
    return primes;
}
// BINARYEXPO
ll BE(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = (ans * a);
        }
        a = (a * a);
        b = b >> 1;
    }

    return ans;
}
ll gnd(ll mn,ll mx)
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> ff(mn, mx);
  return ff(gen);
}