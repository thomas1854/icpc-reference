// Maximum expected array size
const int MAXN = 100005;

// Constants for Double Hashing (Larger prime bases for integer arrays)
const long long P1 = 1000000007LL, MOD1 = 1000000009LL;
const long long P2 = 1000000021LL, MOD2 = 1000000087LL;

// Precomputed powers: pow1[i] = P1^i % MOD1
long long pow1[MAXN], pow2[MAXN];

// Prefix hash arrays: pref1[i] represents hash of a[0...i-1]
long long pref1[MAXN], pref2[MAXN];

// Precomputes powers and prefix hashes in O(N) time
void computeHashes(const vector<int> &a)
{
    int n = static_cast<int>(a.size());
    if (n == 0)
    {
        pref1[0] = pref2[0] = 0;
        return;
    }

    // Shift values so all elements become positive (>= 1), avoiding zero-value collisions
    long long minVal = *min_element(a.begin(), a.end());

    // 1. Base cases for powers and prefix hashes
    pow1[0] = 1;
    pow2[0] = 1;
    pref1[0] = 0;
    pref2[0] = 0;

    // 2. Precompute powers of bases P1 and P2
    for (int i = 1; i <= n; i++)
    {
        pow1[i] = (pow1[i - 1] * P1) % MOD1;
        pow2[i] = (pow2[i - 1] * P2) % MOD2;
    }

    // 3. Compute 1-indexed Prefix Hashes
    // pref[i] = (val_0*P^(i-1) + val_1*P^(i-2) + ... + val_{i-1}*P^0) % MOD
    for (int i = 0; i < n; i++)
    {
        long long val = static_cast<long long>(a[i]) - minVal + 1;

        pref1[i + 1] = (pref1[i] * P1 + val) % MOD1;
        pref2[i + 1] = (pref2[i] * P2 + val) % MOD2;
    }
}

// O(1) Range Hash function for subarray a[L...R] (0-indexed, inclusive)
// Returns a pair representing the double hash (Hash1, Hash2)
pair<long long, long long> getRangeHash(int L, int R)
{
    int len = R - L + 1;

    long long hash1 = (pref1[R + 1] - (pref1[L] * pow1[len]) % MOD1 + MOD1) % MOD1;
    long long hash2 = (pref2[R + 1] - (pref2[L] * pow2[len]) % MOD2 + MOD2) % MOD2;

    return {hash1, hash2};
}

void solve()
{
    vector<int> a = {10, -5, 42, 1000000000, 10, -5, 42, 7};

    computeHashes(a);

    // Example 1: Hash of a[0...2] ({10, -5, 42})
    pair<long long, long long> hash_sub1 = getRangeHash(0, 2);

    // Example 2: Hash of a[4...6] ({10, -5, 42})
    pair<long long, long long> hash_sub2 = getRangeHash(4, 6);

    if (hash_sub1 == hash_sub2)
    {
        cout << "Subarrays a[0..2] and a[4..6] are identical!" << endl;
    }
    else
    {
        cout << "Subarrays are different." << endl;
    }
}