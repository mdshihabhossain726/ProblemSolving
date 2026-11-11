#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, n, w;
    cin >> k >> n >> w;
    
    for(int i = 1; i <= w; i++) {
        n -= k * i;
    }
    if(n >= 0) {
        cout << 0 << "\n";
    } else {
        cout << -n << "\n";
    }
    
    return 0;
}
