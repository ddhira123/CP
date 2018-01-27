#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> st;
    for(int i = 0 ; i < 30000 ; i++) {
        st.insert(i * i);
    }

    int n; scanf("%d", &n);
    int ans = -1e9;

    for(int i = 1 ; i <= n ; i++) {
        int x; scanf("%d", &x);
        if(!st.count(x)) {
            ans = max(ans, x);
        }
    }

    cout << ans << endl;
    return 0;
}