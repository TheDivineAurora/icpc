#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define debug(...)
#else
#include "debug.h"
#endif

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (long long)(x).size()
#define pii pair<long long, long long>

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

long long random(long long l, long long r) {
    uniform_int_distribution<long long> uid(l, r);
    return uid(rng);
}

void solve(long long testcase) {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long zz = 1;
    cout << zz << '\n';
    for (long long i = 1; i <= zz; i++) {
        solve(i);
    }
    return 0;
}
