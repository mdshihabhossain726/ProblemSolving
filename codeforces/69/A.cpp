#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int sum1 = 0, sum2 = 0, sum3 = 0;
    while (n--) {
        int x, y, z;
        cin >> x >> y >> z;
        sum1 += x;
        sum2 += y;
        sum3 += z;
    }
    if (sum1 == 0 && sum2 == 0 && sum3 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
