#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    string s;
    if (!(cin >> n >> k >> s)) return 0;

    sort(s.begin(), s.end());
    int total_weight = 0;
    int count = 0;
    int last_val = -2;

    for (char ch : s) {
        int val = ch - 'a' + 1;
        if (val - last_val >= 2) {
            total_weight += val;
            last_val = val;
            count++;
            if (count == k) break;
        }
    }

    if (count == k) {
        cout << total_weight << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}