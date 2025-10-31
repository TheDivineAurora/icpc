vector<int> find_bridges(vector<vector<pii>>& adj, int m){
    int tmr = 1;
    int n = adj.size();
    vector<int> tin(n), tout(n), vis(n), br(m);
    function<void(int,int)> dfs = [&](int u, int p){
        tin[u] = tout[u] = tmr++;
        vis[u] = 1;
        for(auto v : adj[u]) if(v.first != p){
            if(vis[v.first]){
                tout[u] = min(tout[u], tin[v.first]);
            }
            if(!vis[v.first]){
                dfs(v.first, u);
                tout[u] = min(tout[u], tout[v.first]);
            }
            if(tin[u] < tout[v.first]){
                br[v.second] = 1;
            }
        }
    };
    
    for(int i = 0; i < n; ++i){
        if(!vis[i]) dfs(i, -1);
    }
    return br; // returns vector which has '1' if edge with ID i is bridge.
};