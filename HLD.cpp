// Heavy-light decomposition.
// Decomposes the given tree into heavy and light paths.
// Provides the following functions:
// 1. `position(x)`: Returns the position of node x in the DFS order array.
// 2. `subtree(x)`: Returns range in the DFS order array that corresponds to the
//                  subtree of node x.
// 3. `path_query(a, b, f)`: Partitions the path between nodes a and b into
//                           O(log n) contiguous ranges of the DFS order array.
//                           Calls f(l, r) for each such range [l, r].
//                           The function f may, for example, query/update a
//                           segment tree.

using graph = vector<vector<long long>>;
struct HLD {
    long long n;
    graph &g;
    vector<long long> parent;
    vector<long long> jump;
    vector<long long> total;
    vector<long long> order;

    HLD(graph &g) : n(g.size()), g(g), parent(n), jump(n), total(n), order(n) {
        dfs_size(0);
        long long order_index = 0;
        dfs_hld(0, order_index);
    }

    template <typename F>
    void path_query(long long a, long long b, F f) {
        for (;; a = parent[jump[a]]) {
            if (order[a] < order[b]) swap(a, b);
            if (order[jump[a]] <= order[b]) {
                f(order[b], order[a]);
                return;
            }
            f(order[jump[a]], order[a]);
        }
    }

    long long position(long long x) { return order[x]; }
    pair<long long, long long> subtree(long long x) {
        return {order[x], order[x] + total[x] - 1};
    }

private:
    void dfs_size(long long node) {
        total[node] = 1;
        for (auto &child : g[node]) {
            g[child].erase(find(g[child].begin(), g[child].end(), node));
            dfs_size(child);
            total[node] += total[child];
            if (total[child] > total[g[node][0]]) {
                swap(child, g[node][0]);
            }
        }
    }

    void dfs_hld(long long node, long long &order_index) {
        order[node] = order_index++;
        for (auto child : g[node]) {
            parent[child] = node;
            if (child == g[node][0]) {
                jump[child] = jump[node];
            } else {
                jump[child] = child;
            }
            dfs_hld(child, order_index);
        }
    }
};

// Usage Example


template <class T> class SegmentTree {
private:
    const T DEFAULT = 0;
    vector<T> segtree;
    long long len;

public:
    T f(T a, T b) { return max(a, b); }
    SegmentTree(long long len) : len(len), segtree(len * 2, DEFAULT) {}
    void set(long long ind, T val) {
        ind += len;
        segtree[ind] = val;
        for (; ind > 1; ind /= 2) {
            segtree[ind / 2] = f(segtree[ind], segtree[ind ^ 1]);
        }
    }
    T range(long long start, long long end) {
        T sum = DEFAULT;
        for (start += len, end += len; start < end; start /= 2, end /= 2) {
            if (start % 2 == 1) { sum = f(sum, segtree[start++]); }
            if (end % 2 == 1) { sum = f(sum, segtree[--end]); }
        }
        return sum;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    long long n, q;
    cin >> n >> q;

    vector<long long> v(n);
    for (long long i = 0; i < n; ++i) {
        cin >> v[i];
    }

    graph g(n);
    for (long long i = 0; i < n - 1; ++i) {
        long long a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    HLD hld(g);


    SegmentTree<long long> tree(n);
    for (long long i = 0; i < n; ++i) {
        tree.set(hld.position(i), v[i]);
    }

    for (long long qi = 0; qi < q; ++qi) {
        long long t;
        cin >> t;
        if (t == 1) {
            long long s, x;
            cin >> s >> x;
            tree.set(hld.position(s - 1), x);
        } else {
            long long a, b;
            cin >> a >> b;
            long long ans = 0;
            auto update_ans = [&](long long l, long long r) {
                ans = max(ans, tree.range(l, r + 1));
            };
            hld.path_query(a - 1, b - 1, update_ans);
            cout << ans << '\n';
        }
    }
}