#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

// Type definition for convenience
using uint128 = unsigned __int128;

// Overloading cin (>>) for unsigned __int128
istream &operator>>(istream &in, uint128 &num)
{
    string s;
    if (in >> s)
    {
        num = 0;
        for (char c : s)
        {
            if (c >= '0' && c <= '9')
            {
                num = num * 10 + (c - '0');
            }
        }
    }
    return in;
}

// Overloading cout (<<) for unsigned __int128
ostream &operator<<(ostream &out, uint128 num)
{
    if (num == 0)
        return out << "0";
    string s = "";
    while (num > 0)
    {
        s += (char)('0' + (num % 10));
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return out << s;
}

// 128-bit Euclidean GCD
uint128 gcd128(uint128 a, uint128 b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Modular exponentiation
uint128 mod_pow(uint128 base, uint128 exp, uint128 mod)
{
    uint128 res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/**
 * Deterministic Miller-Rabin Primality Test (N < 2^64)
 */
bool miller_rabin(uint128 n)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    uint128 d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    static const uint128 bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (uint128 a : bases)
    {
        if (n <= a)
            break;
        uint128 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1)
            continue;

        bool composite = true;
        for (int r = 1; r < s; r++)
        {
            x = (x * x) % n;
            if (x == n - 1)
            {
                composite = false;
                break;
            }
        }
        if (composite)
            return false;
    }
    return true;
}

/**
 * Pollard's Rho Algorithm (Brent's Optimization)
 */
uint128 pollard_rho(uint128 n)
{
    if (n % 2 == 0)
        return 2;
    if (n % 3 == 0)
        return 3;
    if (miller_rabin(n))
        return n;

    static mt19937_64 rng(1337);

    while (true)
    {
        uint128 c = rng() % (n - 1) + 1;
        auto f = [&](uint128 x)
        {
            return ((x * x) % n + c) % n;
        };

        uint128 x = rng() % (n - 2) + 2;
        uint128 y = x;
        uint128 g = 1;

        while (g == 1)
        {
            x = f(x);
            y = f(f(y));
            uint128 diff = (x > y) ? (x - y) : (y - x);
            g = gcd128(diff, n);
        }

        if (g != n)
            return g;
    }
}

// Recursive factorizer
void factorize(uint128 n, vector<uint128> &factors)
{
    if (n == 1)
        return;
    if (miller_rabin(n))
    {
        factors.push_back(n);
        return;
    }
    uint128 factor = pollard_rho(n);
    factorize(factor, factors);
    factorize(n / factor, factors);
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint128 n;
    if (cin >> n)
    { // Using standard cin directly!
        if (miller_rabin(n))
        {
            cout << n << " is PRIME\n"; // Using standard cout directly!
        }
        else
        {
            vector<uint128> factors;
            factorize(n, factors);
            sort(factors.begin(), factors.end());

            cout << n << " is COMPOSITE\nPrime factors: ";
            for (auto f : factors)
            {
                cout << f << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}