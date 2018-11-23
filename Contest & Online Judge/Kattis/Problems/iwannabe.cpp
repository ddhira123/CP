#include <bits/stdc++.h>
using namespace std;

struct Data {
    int idx;
    long long a;
    long long b;
    long long c;

    void read() {
        scanf("%lld %lld %lld", &a, &b, &c);
    }
};

Data arr[1005];
int n, k;

int main() {
    cin >> n >> k;
    for (int i = 0 ; i < n ; i++) {
        arr[i].read();
        arr[i].idx = i;
    }

    set<int> st;

    sort(arr, arr + n, [](Data a, Data b) {
        return a.a > b.a;
    });
    for (int i = 0 ; i < k ; i++) st.insert(arr[i].idx);

    sort(arr, arr + n, [](Data a, Data b) {
        return a.b > b.b;
    });
    for (int i = 0 ; i < k ; i++) st.insert(arr[i].idx);

    sort(arr, arr + n, [](Data a, Data b) {
        return a.c > b.c;
    });
    for (int i = 0 ; i < k ; i++) st.insert(arr[i].idx);


    cout << st.size() << endl;
    return 0;
}