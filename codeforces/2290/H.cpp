#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n + 1, 0), order;
        order.reserve(n);
        order.push_back(1);
        for (int i = 0; i < n; i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v != parent[u]) {
                    parent[v] = u;
                    order.push_back(v);
                }
            }
        }

        vector<int> sz(n + 1, 1), dp(n + 1, 0);
        sz[0] = 0; // এই লাইনটি না থাকায় sz[0] = 1 হয়ে যাচ্ছিল

        for (int i = n - 1; i >= 1; i--) {
            int u = order[i];
            int best = 0, second_sz = 0;
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                sz[u] += sz[v];
                if (sz[v] > sz[best]) {
                    second_sz = sz[best];
                    best = v;
                } else if (sz[v] > second_sz) {
                    second_sz = sz[v];
                }
            }
            if (best != 0) {
                dp[u] = max(dp[best], second_sz);
            }
        }

        vector<int> root_children;
        for (int v : adj[1]) {
            root_children.push_back(v);
        }
        sort(root_children.begin(), root_children.end(), [&](int a, int b) {
            return sz[a] > sz[b];
        });

        int lost = dp[root_children[0]];
        if (root_children.size() >= 2) {
            lost = max(lost, dp[root_children[1]]);
        }
        if (root_children.size() >= 3) {
            lost = max(lost, sz[root_children[2]]);
        }

        cout << n - lost << "\n";
    }
    return 0;
}