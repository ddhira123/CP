#include <bits/stdc++.h>
using namespace std;

multiset<int> st;
int n, k;
vector<pair<int, int>> v;

void read() {
    scanf("%d %d", &n, &k);
    v.resize(n);

    for(pair<int, int> &x : v) {
        scanf("%d %d", &x.first, &x.second);
    }
}

int work() {
    for(int i = 0 ; i < k ; i++) {
        st.insert(-1);
    }

    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    int ret = 0;
    for(pair<int, int> x : v) {
        auto it = st.lower_bound(x.first);

        if(it != st.begin()) {
            it--;
            st.erase(it);
            st.insert(x.second);

            ret++;
        }
    }

    return ret;
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}