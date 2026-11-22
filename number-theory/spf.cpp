const int MAX = 1e6;
vector<int> spf(MAX + 1);

void sieve()
{
    for (int i = 1; i <= MAX; ++i)
        spf[i] = i;

    for (int i = 2; i * i <= MAX; ++i)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= MAX; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}