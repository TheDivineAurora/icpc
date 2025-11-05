const int MOD = 1000000007; // Any Mod

using ll = long long;
using C = complex<long double>;
const long double PI = acos(-1.0L);

void fft(vector<C> &a) {
    int n = (int)a.size();
    if (n <= 1) return;
    int L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for (int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        complex<long double> x = polar(1.0L, PI / k);
        for (int i = k; i < 2 * k; ++i) {
            if (i & 1) {
                R[i] = R[i / 2] * x;
            } else {
                R[i] = R[i / 2];
            }
            rt[i] = C((long double)R[i].real(), (long double)R[i].imag());
        }
    }
    vector<int> rev(n);
    for (int i = 0; i < n; ++i) {
        rev[i] = (rev[i / 2] | ((i & 1) << L)) / 2;
    }
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                const long double *xr = reinterpret_cast<const long double *>(&rt[j + k]);
                const long double *yr = reinterpret_cast<const long double *>(&a[i + j + k]);
                C z(xr[0] * yr[0] - xr[1] * yr[1],
                    xr[0] * yr[1] + xr[1] * yr[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

template <int M>
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int resultSize = (int)a.size() + (int)b.size() - 1;
    int B = 32 - __builtin_clz(resultSize);
    int n = 1 << B;
    int cut = static_cast<int>(sqrt(M));

    vector<C> L(n, C(0, 0)), R(n, C(0, 0));
    for (size_t i = 0; i < a.size(); ++i) {
        int ai = static_cast<int>(a[i] % M);
        if (ai < 0) ai += M;
        L[i] = C(ai / cut, ai % cut);
    }
    for (size_t i = 0; i < b.size(); ++i) {
        int bi = static_cast<int>(b[i] % M);
        if (bi < 0) bi += M;
        R[i] = C(bi / cut, bi % cut);
    }
    fft(L);
    fft(R);
    vector<C> outl(n), outs(n);
    for (int i = 0; i < n; ++i) {
        int j = (-i) & (n - 1);
        C Li = L[i];
        C Lj = L[j];
        C Ri = R[i];
        C A = (Li + conj(Lj));
        C Bc = (Li - conj(Lj));
        outl[j] = A * Ri / (2.0 * (long double)n);
        outs[j] = Bc * Ri / (2.0 * (long double)n) / C(0, 1);
    }
    fft(outl);
    fft(outs);
    vector<ll> res(resultSize);
    for (int i = 0; i < resultSize; ++i) {
        ll av = ll(real(outl[i]) + 0.5);
        ll cv = ll(imag(outs[i]) + 0.5);
        ll bv = ll(imag(outl[i]) + 0.5) + ll(real(outs[i]) + 0.5);
        ll val = av % M;
        val = (val * cut + (bv % M + M) % M) % M;
        val = (val * cut + (cv % M + M) % M) % M;
        res[i] = val;
    }
    return res;
}
// vector<ll> res = convMod<MOD>(a, b);
