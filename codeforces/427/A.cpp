#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    int police = 0;
    int untreated = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x > 0) {
            police += x;
        } else {
            if (police > 0) {
                police--;
            } else {
                untreated++;
            }
        }
    }

    cout << untreated << "\n";
    
    return 0;
}
