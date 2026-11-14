#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string b;
        cin >> b;
        int n = b.size();
        string ans = "";
        ans += b[0];
        for (int i = 1; i < n; i+=2) {
                ans += b[i];
        }
        cout << ans << "\n";
    }
    return 0;
}
