vector<vector<int>> aux(n + 1);
vector<int> tot;
auto build_aux = [&]() {
    sort(tot.begin(), tot.end());
    tot.erase(unique(tot.begin(), tot.end()), tot.end());
    sort(tot.begin(), tot.end(), [&](int a, int b) { return tin[a] < tin[b]; });

    int sz = tot.size();
    for (int i = 0; i + 1 < sz; ++i) {
        tot.pb(tree.lca(tot[i], tot[i + 1]));
    }

    sort(tot.begin(), tot.end());
    tot.erase(unique(tot.begin(), tot.end()), tot.end());
    sort(tot.begin(), tot.end(), [&](int a, int b) { return tin[a] < tin[b]; });

    stack<int> st;
    st.push(tot[0]);
    for (int i = 1; i < tot.size(); ++i) {
        while (!st.empty() && !isanc(st.top(), tot[i])) st.pop();
        if (!st.empty()) {
            aux[st.top()].pb(tot[i]);
            aux[tot[i]].pb(st.top());
        }
        st.push(tot[i]);
    }
};
