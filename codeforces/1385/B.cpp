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
        vector<bool> seen(n + 1, false);
        for (int i = 0; i < 2*n; ++i) {
            int x;
            cin >> x;
            if (!seen[x]) {
                cout << x << " ";
                seen[x] = true;
            }
            
        }
        cout << "\n";
    }

    return 0;
}
