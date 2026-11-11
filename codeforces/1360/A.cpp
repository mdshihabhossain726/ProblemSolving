#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int a, b;
        cin >> a >> b;
        
        if (a > b) swap(a, b);
        if (a * 2 >= b) {
            int side = a * 2;
            cout << side * side << "\n";
        } else {
            int side = b;
            cout << side * side << "\n";
        }
    }

    return 0;
}