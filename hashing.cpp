
const int mod = 1e9 + 7;
const int p = 31;
const int p1 = 37;
const int mod1 = 1e9 + 9;
ll has[2000005], has1[2000005], po[2000005], po1[2000005], hasp[2000005], hasp1[2000005], n;
string s = "", sp = "";
ll gethash(ll l, ll r)
{
    ll ans = (has[r] - (has[l - 1] * po[r - l + 1]) % mod + mod) % mod;
    ll ans1 = (has1[r] - (has1[l - 1] * po1[r - l + 1]) % mod1 + mod1) % mod1;
    return ((ans << 32) | ans1);
}
ll gethashp(ll l, ll r)
{
    ll ans = (hasp[r] - (hasp[l - 1] * po[r - l + 1]) % mod + mod) % mod;
    ll ans1 = (hasp1[r] - (hasp1[l - 1] * po1[r - l + 1]) % mod1 + mod1) % mod1;
    return ((ans << 32) | ans1);
}

void cal()
{
    po[0] = 1;
    po1[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        po[i] = (po[i - 1] * p) % mod;
        po1[i] = (po1[i - 1] * p1) % mod1;
    }

    for (int i = 1; i <= n; i++)
    {
        has[i] = (has[i - 1] * p + (s[i - 1] - 'a' + 1)) % mod;
        has1[i] = (has1[i - 1] * p1 + (s[i - 1] - 'a' + 1)) % mod1;
    }
}
void calp()
{
    for (int i = 1; i <= n; i++)
    {
        hasp[i] = (hasp[i - 1] * p + (sp[i - 1] - 'a' + 1)) % mod;
        hasp1[i] = (hasp1[i - 1] * p1 + (sp[i - 1] - 'a' + 1)) % mod1;
    }
}
bool is_pal(int i, int len)
{
    if (len % 2)
    {
        int l1 = i, r1 = i + (len / 2) - 1;
        int l2 = r1 + 2, r2 = i + len - 1;
        int lp = n - r2 + 1, rp = n - l2 + 1;
        ll ans1 = gethash(l1, r1);
        ll ans2 = gethashp(lp, rp);
        if (ans1 == ans2)
        {
            return true;
        }
    }
    else
    {
        int l1 = i, r1 = i + (len / 2) - 1;
        int l2 = r1 + 1, r2 = i + len - 1;
        int lp = n - r2 + 1, rp = n - l2 + 1;
        ll ans1 = gethash(l1, r1);
        ll ans2 = gethashp(lp, rp);
        if (ans1 == ans2)
        {
            return true;
        }
    }
    return false;
}