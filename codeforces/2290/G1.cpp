#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<long long> h(n);
        for (int i = 0; i < n; i++) cin >> h[i];

        long long l = 0, r = 1e9, ans = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            vector<long long> a = h;

            for (int rep = 0; rep < 2; rep++) {
                for (int i = 0; i < n; i++)
                    a[(i + 1) % n] = max(a[(i + 1) % n], a[i] - mid);
                for (int i = n - 1; i >= 0; i--)
                    a[(i - 1 + n) % n] = max(a[(i - 1 + n) % n], a[i] - mid);
            }
            long long cost = 0;
            for (int i = 0; i < n; i++) cost += a[i] - h[i];
            if (cost <= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}