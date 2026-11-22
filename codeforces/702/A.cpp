#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int prev;
    cin >> prev;

    int current_len = 1;
    int max_len = 1;

    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        if (x > prev) {
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 1;
        }
        prev = x;
    }
    cout << max_len << "\n";
    return 0;
}
