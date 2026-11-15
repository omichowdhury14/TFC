const int N = 5000006;
ull phi[N + 1];
void func()
{
    for (int i = 1; i <= N; i++)
    {
        phi[i] = i;
    }
    for (int i = 2; i <= N; i++)
    {
        if (phi[i] == i)
        {
            for (int k = i; k <= N; k += i)
            {
                phi[k] -= phi[k] / i;
            }
        }
    }
    
}