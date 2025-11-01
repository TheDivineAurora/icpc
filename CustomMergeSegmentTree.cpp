struct Segtree {
    // sum, prefmin, prefmax
    typedef array<int,2> node;
    node def = {0, INF, -INF};
    vector<node> tree;

    node merge(const node& x, const node& y){
        return {
            x[0] + y[0],
            min(x[1], x[0] + y[1]),
            max(x[2], x[0] + y[2])
        };
    }

    node query(int v, int nl, int nh, int ql, int qh) {
        if (qh < nl || nh < ql) return def;
        if (ql <= nl && nh <= qh) return tree[v];
        int mid = (nl + nh) / 2;
        node res1 = query(2 * v, nl, mid, ql, qh);
        node res2 = query(2 * v + 1, mid + 1, nh, ql, qh);
        return merge(res1, res2);
    }

    void update(int v, int nl, int nh, int ql, int qh, int val){
        if(qh < nl || nh < ql) return;
        if(ql <= nl && nh <= qh){
            tree[v] = {val, val, val};
            return;
        }
        int mid = (nl + nh) / 2;
        update(2 * v, nl, mid, ql, qh, val);
        update(2 * v + 1, mid + 1, nh, ql, qh, val);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }

    Segtree(vector<int>& a){
        int n = a.size();
        tree.assign(4 * n, def);
        for(int i = 0; i < a.size(); ++i){
            update(1, 0, n - 1, i, i, a[i]);
        }
    } 
};//  (vv careful) use same nl, nh. nl = 0, nh = input vector size - 1 (last index)
