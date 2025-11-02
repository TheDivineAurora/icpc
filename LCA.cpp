struct LCA {
    const int LN = 20;
    vector<vector<int>> dp;
    vector<vector<int>> adj;
    vector<int> d;
    void dfs(int u,int p){
        dp[u][0] = p;
        for(int i = 1; i < LN; ++i){
            dp[u][i] = dp[dp[u][i-1]][i-1]; 
        }
        for(auto v : adj[u]) if(v != p) {
            d[v] = d[u] + 1;
            dfs(v, u);
        }
    }

    LCA(vector<vector<int>>& __adj){
        adj = __adj;
        d.resize(adj.size());
        dp.assign(adj.size(), vector<int>(LN, 0));
        dfs(1, 0);
    }

    int lca(int u,int v){
        if(d[u]<d[v]) swap(v,u);
        int diff = d[u] - d[v];
        for(int i = 0; i < LN; ++i){
            if(diff & (1 << i)){
                u = dp[u][i];
            }
        }
        if(u == v) return u;
        for(int i = LN - 1; i >= 0; --i){
            if(dp[u][i] != dp[v][i]){
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        return dp[u][0];
    }

    int kth(int u, int dis){
        for(int i = 0; i < LN; ++i){
            if(dis & (1 << i)){
                u = dp[u][i];
            }
        }
        return u;
    }
};
