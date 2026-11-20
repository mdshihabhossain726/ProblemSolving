#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long a, b, x, y, n;
        cin >> a >> b >> x >> y >> n;

        long long a1 = a, b1 = b, n1 = n;
        long long komabo_a = min(n1, a1 - x);
        a1 -= komabo_a;
        n1 -= komabo_a;
        b1 -= min(n1, b1 - y);
        long long ans1 = a1 * b1;

        long long a2 = a, b2 = b, n2 = n;
        long long komabo_b = min(n2, b2 - y);
        b2 -= komabo_b;
        n2 -= komabo_b;
        a2 -= min(n2, a2 - x);
        long long ans2 = a2 * b2;

        cout << min(ans1, ans2) << "\n";
    }

    return 0;
}