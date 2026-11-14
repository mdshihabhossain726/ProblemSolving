#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        vector<bool> need(26, false);
        for (int i = 0; i < n / 2; i++) {
            int l = s[i] - 'a';
            int r = s[n - 1 - i] - 'a';
            if (l > r) swap(l, r);

            for (int c = l + 1; c <= r; c++) {
                need[c] = true;
            }
        }
        int ans = 0;
        for (int c = 0; c < 26; c++) {
            if (need[c]) ans++;
        }

        cout << ans << "\n";
    }
    return 0;
}