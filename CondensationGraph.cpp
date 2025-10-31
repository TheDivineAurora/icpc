void scc_components(vector<vector<int>>& adj, vector<vector<int>>& adj_cond, vector<int>& roots) {
    int n = adj.size(); // zero base indexing is used.
    vector<vector<int>> adj_rev(n);
    roots.assign(n, 0); adj_cond.assign(n, {});
    for (int i = 0; i < n; ++i) {
        for (auto v : adj[i]) {
            adj_rev[v].push_back(i);
        }
    }
    vector<int> vis(n, 0), ord;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (auto v : adj[u]) if (!vis[v]) {
                dfs(v);
            }
        ord.pb(u);
    };
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs(i);
    }
    vis.assign(n, 0);
    while (!ord.empty()) {
        int u = ord.back();
        ord.pop_back();
        if (vis[u]) continue;
        queue<int> q;
        q.push(u);
        vis[u] = 1;
        roots[u] = u;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (auto v : adj_rev[node]) if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                    roots[v] = u;
                }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto v : adj[i]) {
            if (roots[i] != roots[v]) {
                adj_cond[roots[i]].push_back(roots[v]);
            }
        }
    }
}
