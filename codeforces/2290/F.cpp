#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, b, cnt = 0;
        cin >> n;
        vector<int> p(n + 1);
        for (int x = 1; x <= n; x++) {
            cin >> b;
            int pos = b + n - x + 1;
            if (pos >= 1 && pos <= n && !p[pos]) p[pos] = x, cnt++;
        }
        if (cnt < n) cout << -1;
        else for (int i = 1; i <= n; i++) cout << p[i] << " ";
        cout << "\n";
    }
}