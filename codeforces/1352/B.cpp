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
        int odd_last = n - (k - 1);
        int even_last = n - 2 * (k - 1);
        if (odd_last > 0 && odd_last % 2 == 1) {
            cout << "YES\n";
            for (int i = 0; i < k - 1; ++i) {
                cout << "1 ";
            }
            cout << odd_last << "\n";
        } else if (even_last > 0 && even_last % 2 == 0) {
            cout << "YES\n";
            for (int i = 0; i < k - 1; ++i) {
                cout << "2 ";
            }
            cout << even_last << "\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
