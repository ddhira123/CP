#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, m;
pair<int, int> arr[N];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &arr[i].first, &arr[i].second);
        arr[i].second += arr[i].first;
    }
}

int work() {
    multiset<int> st;

    sort(arr, arr + n, [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });

    int ret = n;

    for(int i = 0 ; i < n ; i++) {
        auto it = st.lower_bound(arr[i].first - m);

        if(it != st.end() && arr[i].first >= *it){
            // if(arr[i].first - *it > m) {
            // cout << arr[i].first << " -- " << *it << endl;
                // ret++;
            // }
            st.erase(it);
            st.insert(arr[i].second);
        } else {
            ret--;
            st.insert(arr[i].second);
        }
    }

    return ret;
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}