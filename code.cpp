// ------------------------------------------------------------------------------------------------ -
// Range Add Update and Range Min Query (Also with Position of First Element Below X)

// Usage Example
// SegTree seg(n);
// seg.update(l, r, val); // Add 'val' to all elements in range [l, r]
// long long minVal = seg.query(l, r); // Get minimum value in range [l, r]
// long long pos = seg.firstIndexBelow(x); // Get first index where value is below 'x', or -1 if none

// ------------------------------------------------------------------------------------------------ -

struct SegTree {
    long long n;
    vector<long long> seg, lazy;
    SegTree(long long _n): n(_n) {
        seg.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(long long idx, long long l, long long r) {
        if (lazy[idx] != 0) {
            seg[idx] += lazy[idx];
            if (l != r) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update(long long idx, long long l, long long r, long long ql, long long qr, long long val) {
        push(idx, l, r);
        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[idx] += val;
            push(idx, l, r);
            return;
        }
        long long mid = (l + r) >> 1;
        update(2 * idx + 1, l, mid, ql, qr, val);
        update(2 * idx + 2, mid + 1, r, ql, qr, val);
        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    void update(long long ql, long long qr, long long val) {
        update(0, 0, n - 1, ql, qr, val);
    }

    long long query(long long idx, long long l, long long r, long long ql, long long qr) {
        push(idx, l, r);
        if (r < ql || qr < l) return (LLONG_MAX << 2);
        if (ql <= l && r <= qr) return seg[idx];
        long long mid = (l + r) >> 1;
        return min(query(2 * idx + 1, l, mid, ql, qr), query(2 * idx + 2, mid + 1, r, ql, qr));
    }

    long long query(long long ql, long long qr) {
        return query(0, 0, n - 1, ql, qr);
    }

    long long firstIndexBelow(long long x) {
        if (seg[0] >= x) return -1;
        long long idx = 0, l = 0, r = n - 1;
        while (l != r) {
            push(idx, l, r);
            long long mid = (l + r) >> 1;
            push(2 * idx + 1, l, mid);
            if (seg[2 * idx + 1] < x) {
                idx = 2 * idx + 1;
                r = mid;
            }
            else {
                idx = 2 * idx + 2;
                l = mid + 1;
            }
        }
        return l;
    }
};

// ------------------------------------------------------------------------------------------------ -
// Kartik Lazy Segtree
// ------------------------------------------------------------------------------------------------ -

const long long inf = 4e18;
struct LazySegtree {
    typedef array<long long, 4> node;
    typedef array<long long, 2> F;
    int n, h;
    vector<node> T;
    vector<F> lz;
    node merge(const node &L, const node &R) {
        return {L[0] + R[0], min(L[1], R[1]), max(L[2], R[2]), L[3] + R[3]};
    }
    LazySegtree(vector<long long> &v) {
        n = (int)v.size();
        h = __lg(n);
        T = vector<node>(2 * n, {0, inf, -inf, 1});
        lz = vector<F> (n, { -inf, 0});
        for (int i = 0; i < n; i++)T[i + n] = {v[i], v[i], v[i], 1};
        for (int i = n - 1; i > 0; i--) {
            T[i] = merge(T[2 * i], T[2 * i + 1]);
        }
    }
    void apply(int v, F upd) {
        if (upd[0] != -inf)
            T[v] = {upd[0]*T[v][3], upd[0], upd[0], T[v][3]};
        T[v][0] += upd[1] * T[v][3], T[v][1] += upd[1], T[v][2] += upd[1];
        if (v < n) {
            if (upd[0] != -inf)
                lz[v] = upd;
            else
                lz[v][1] += upd[1];
        }
    }
    void push(int v) {
        for (int s = h; s > 0; s--) {
            int i = v >> s;
            apply(2 * i, lz[i]);
            apply(2 * i + 1, lz[i]);
            lz[i] = { -inf, 0};
        }
    }
    void pull(int v) {
        while (v > 1) {
            v >>= 1;
            T[v] = merge(T[2 * v], T[2 * v + 1]);
            F upd = lz[v];
            lz[v] = { -inf , 0};
            apply(v, upd);
        }
    }
    void update(int l, int r, F upd) {
        l += n, r += n + 1;
        push(l), push(r - 1);
        int tl = l, tr = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                apply(l++, upd);
            if (r & 1)
                apply(--r, upd);
        }
        pull(tl), pull(tr - 1);
    }
    node query(int l, int r) {
        l += n, r += n + 1;
        push(l), push(r - 1);
        node res = {0, inf, -inf, 0};
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = merge(res, T[l++]);
            if (r & 1)
                res = merge(res, T[--r]);
        }
        return res;
    }
};
// range add x -> st.update(l, r, {-inf, x})
// range set x -> st.update(l, r, {x, 0})