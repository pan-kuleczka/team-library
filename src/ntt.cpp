 
// Number Theoretic Tranform (NTT)
// For functions below you can choose 2 params:
// 1. M - prime modulus that MUST BE of form
// a*2ˆk+1, computation is done in Z_M
// 2. R - generator of Z_M
// Modulus often seen on Codeforces:
// M = (119<<23)+1, R = 62; M is 998244353
// Parameters for ll computation with CRT:
// M = (479<<21)+1, R = 62; M is > 10ˆ9
// M = (483<<21)+1, R = 62; M is > 10ˆ9
using ll=long long;
ll modPow(ll a, ll e, ll m)
{
    ll t = 1 % m;
    while (e)
    {
        if (e % 2)
            t = t * a % m;
        e /= 2;
        a = a * a % m;
    } // 66ca
    return t;
} // 1973
// Compute DFT over Z_M with generator R.
// Input size must be power of 2; O(n lg n)
// Input is expected to be in range [0;MOD)!
// dit == true <=> inverse transform * 2ˆn
// (without normalization)
template <ll M, ll R, bool dit>
void ntt(vector<ll> &a)
{
    static vector<ll> w(2, 1);
    int n = sz(a);
    for (int k = sz(w); k < n; k *= 2)
    {
        w.resize(n, 1);
        ll c = modPow(R, M / 2 / k, M);
        if (dit)
            c = modPow(c, M - 2, M);
        repp(i, k + 1, k * 2) w[i] = w[i - 1] * c % M;
    } // 0d98
    for (int t = 1; t < n; t *= 2)
    {
        int k = (dit ? t : n / t / 2);
        for (int i = 0; i < n; i += k * 2)
            rep(j, k)
            {
                ll &c = a[i + j], &d = a[i + j + k];
                ll e = w[j + k], f = d;
                d = (dit ? c - (f = f * e % M) : (c - f) * e % M);
                if (d < 0)
                    d += M;
                if ((c += f) >= M)
                    c -= M;
            } // e4a6
    }         // 8d38
} // 01f5
// Convolve a and b mod M (R is generator),
// store result in a; time: O(n lg n), 3x NTT
// Input is expected to be in range [0;MOD)!
template <ll M = (119 << 23) + 1, ll R = 62>
void convolve(vector<ll> &a, vector<ll> b)
{
    int len = sz(a) + sz(b) - 1;
    if (len <= 0)
        return a.clear();
    int n = 1 << (32 - __builtin_clz(len));
    ll t = modPow(n, M - 2, M);
    a.resize(n);
    b.resize(n);
    ntt<M, R, 0>(a);
    ntt<M, R, 0>(b);
    rep(i, n) a[i] = a[i] * b[i] % M * t % M;
    ntt<M, R, 1>(a);
    a.resize(len);
} // b413