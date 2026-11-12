#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            long long a;
            cin >> a;
            if (i % (k + 1) == 1) {
                sum += a;
            }
        }
        if (sum % 2 == 1) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
    return 0;
}