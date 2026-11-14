#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<int> l, r, mid;
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if (i > 0 && a[i] == a[i - 1]) {
                cnt++;
            } else {
                cnt = 1;
            }
            if (cnt == 1) {
                l.push_back(a[i]);
            } else if (cnt == 2) {
                r.push_back(a[i]);
            } else {
                mid.push_back(a[i]);
            }
        }
        reverse(r.begin(), r.end());
        cout<< l.size() + r.size()<< "\n";
        for(int x : l) cout << x << " ";
        for(int x : mid) cout << x << " ";
        for(int x : r) cout << x << " ";
        cout << "\n";
    }
    return 0;
}