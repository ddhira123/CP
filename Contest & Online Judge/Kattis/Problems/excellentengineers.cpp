#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

pair<int, pair<int, int>> arr[N];
int n;

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d %d", &arr[i].first, &arr[i].second.first, &arr[i].second.second);
    }
}

int work() {
    sort(arr, arr + n);
    set<pair<int, int>> st;

    int ret = 0;
    for(int i = 0 ; i < n ; i++) {
        pair<int, int> cur = arr[i].second;

        auto it = st.lower_bound(cur);
        bool add = false;

        if(it == st.begin()) {
            add = true;
        } else {
            it--;
            if((*it).second > cur.second) {
                add = true;
            }
        }

        if(add) {
            ret++;
            st.insert(cur);

            while(1) {
                it = st.upper_bound(cur);

                if(it == st.end() || (*it).second < cur.second) {
                    break;
                } else {
                    st.erase(it);
                }
            }
        }
    }

    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%d\n", work());
    }
    return 0;
}