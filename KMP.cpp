vector<int> pi(const string &s) {
    int n = (int)s.size();
    vector<int> pi_s(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[j] != s[i]) { j = pi_s[j - 1]; }
        if (s[i] == s[j]) { j++; }
        pi_s[i] = j;
    }
    return pi_s;
}
// Compute no of occurence of a prefix in entire string

vector<int> ans(n + 1, 0);
for (int i = 0; i < n; i++)
    ans[pis[i]]++;
for (int i = n - 1; i > 0; i--)
    ans[pis[i - 1]] += ans[i];
for (int i = 0; i <= n; i++)
    ans[i]++;
