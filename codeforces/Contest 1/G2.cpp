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

        int p = max_element(h.begin(), h.end()) - h.begin();
        vector<long long> b(n + 1), a(n + 1);
        for (int i = 0; i <= n; i++) b[i] = h[(p + i) % n];

        long long l = 0, r = 0;
        for (int i = 0; i < n; i++) r = max(r, abs(b[i] - b[i + 1]));

        long long ans = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            a = b;

            for (int i = 1; i <= n; i++)
                a[i] = max(a[i], a[i - 1] - mid);

            long long cost = 0;
            for (int i = n - 1; i >= 0; i--) {
                a[i] = max(a[i], a[i + 1] - mid);
                cost += a[i] - b[i];
            }

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