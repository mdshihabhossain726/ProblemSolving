#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    int max_val = 0, max_idx = 0;
    int min_val = 101, min_idx = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > max_val) {
            max_val = x;
            max_idx = i;
        }
        if (x <= min_val) {
            min_val = x;
            min_idx = i;
        }
    }

    int ans = max_idx + (n - 1 - min_idx);
    if (max_idx > min_idx) {
        ans--;
    }

    cout << ans << "\n";
    
    return 0;
}
