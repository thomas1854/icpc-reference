const int MAX = 1e6 + 1;
vector<int> mu(MAX + 1);
vector<bool> composite(MAX + 1, 0);
vector<int> primes;
void mobius_sieve()
{
    mu[1] = 1;
    for (int i = 2; i <= MAX; i++)
    {
        if (!composite[i])
        {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (int p : primes)
        {
            if (i * p > MAX)
                break;
            composite[i * p] = 1;
            if (i % p == 0)
            {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
}