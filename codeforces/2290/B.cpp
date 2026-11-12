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

        int countSwaps = 0;
        char pen = 'R';

        for (int i = 0; i < n; i++) {
            if (s[i] != pen) {
                countSwaps++;
            }
            pen = (s[i] == 'R') ? 'B' : 'R';
        }
        cout << countSwaps << "\n";
    }
    return 0;
}