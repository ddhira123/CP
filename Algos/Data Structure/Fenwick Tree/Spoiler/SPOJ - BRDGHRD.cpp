#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> uniq;
pair<int,int> arr[N];
int BIT[N];
int n;

void make() {
    uniq.push_back(-1e9);
    sort(uniq.begin(),uniq.end());
    uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());

    for(int i = 1 ; i < uniq.size() ; i++)
        BIT[i] = 0;
}

int getIndex(int x) {
    return lower_bound(uniq.begin(),uniq.end(),x) - uniq.begin();
}

void update(int x,int val) {
    for(; x < uniq.size() ; x += x & -x)
        BIT[x] = max(BIT[x],val);
}

int query(int x) {
    int ret = 0;
    while(x) {
        ret = max(ret,BIT[x]);
        x -= x & -x;
    }
    return ret;
}

void read() {
    scanf("%d",&n);

    for(int i = 1 ; i <= n ; i++)
        scanf("%d",&arr[i].first);
    uniq.clear();
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d",&arr[i].second);
        uniq.push_back(arr[i].second);
    }
}

int solve() {
    make();
    sort(arr + 1,arr + n + 1);

    int ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        int idx = getIndex(arr[i].second);
        int temp = 1 + query(idx);
        ret = max(ret,temp);
        update(idx,temp);
    }

    return ret;
}

int main() {
    int t; scanf("%d",&t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%d\n",solve());
    }
    return 0;
}