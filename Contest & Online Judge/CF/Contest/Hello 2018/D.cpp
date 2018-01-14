#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

pair<pair<int, int>, int> arr[N];
int n, t;

void read() {
    scanf("%d %d", &n, &t);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &arr[i].first.first, &arr[i].first.second);
        arr[i].second = i;
    }
}

void prepare() {
    sort(arr, arr + n);
}

void solve() {
    long long tot = 0;
    int it = n-1;

    priority_queue<pair<int, int>> pq;

    for(int i = n ; i >= 0 ; i--) {
        while(it >= 0 && arr[it].first.first >= i) {
            pq.push({arr[it].first.second, arr[it].second});
            tot += arr[it].first.second;
            it--;
        }

        while(pq.size() > i) {
            tot -= pq.top().first;
            pq.pop();
        }

        if(pq.size() == i && tot <= t) {
            printf("%d\n%d\n", i, i);

            while(!pq.empty()) {
                printf("%d ", pq.top().second+1);
                pq.pop();
            }

            puts("");

            break;
        }
    }
}

int main() {
    read();
    prepare();
    solve();
    return 0;
}