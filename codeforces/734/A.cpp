#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int anton = 0, danik = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            anton++;
        } else {
            danik++;
        }
    }

    if (anton > danik) {
        cout << "Anton\n";
    } else if (danik > anton) {
        cout << "Danik\n";
    } else {
        cout << "Friendship\n";
    }

    return 0;
}
