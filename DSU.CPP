struct DSU {
    vector<long long> e;
    DSU(long long N) {
        e = vector<long long>(N, -1);
    }
    long long get(long long x) {
        return e[x] < 0 ? x : e[x] = get(e[x]);
    }
    bool same_set(long long a, long long b) {
        return get(a) == get(b);
    }
    long long size(long long x) {
        return -e[get(x)];
    }
    bool unite(long long x, long long y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

