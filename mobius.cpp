const int MAXN = 10000000;
int mu[MAXN + 1];
int primes[664580];
bool comp[MAXN + 1];
int cnt = 0;
void func()
{
    mu[1] = 1;
    for (int i = 2; i <= MAXN; ++i)
    {
        if (!comp[i])
        {
            primes[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i * primes[j] <= MAXN; ++j)
        {
            comp[i * primes[j]] = true;

            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            else
            {
                mu[i * primes[j]] = -mu[i];
            }
        }
    }
}