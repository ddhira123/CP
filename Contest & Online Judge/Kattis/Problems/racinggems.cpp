#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

typedef long long LL;

#define fi first
#define se second

inline int io() {
    register char c;
    c = getchar_unlocked();
    while(c == ' ' || c == '\n') c = getchar_unlocked();
    int ret = 0;
    int sign = 1;
    if(c == '-') {
        sign = -1;
    }
    else {
        ret = c - '0';
    }
    
    while(1) {
        c = getchar_unlocked();
        if(!('0' <= c && c <= '9')) return ret;
        ret = (ret << 3) + (ret << 1) + (c - '0');
    }
}

inline void make(vector<LL> &v) {
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
}

inline int ID(LL x,vector<LL> &v) {
    return lower_bound(v.begin(),v.end(),x) - v.begin();
}

pair<LL,LL> arr[N];
int dp[N];
int n,r,w,h;
int BIT[2 * N];
vector<LL> uniq;

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

bool read() {
    if(scanf("%d %d %d %d",&n,&r,&w,&h) != 4) return 0;
    for(int i = 0 ; i < n ; i++) arr[i].se = io(), arr[i].fi = io();
    return 1;
}

int solve() {
    uniq.clear();
    for(int i = 0 ; i < n ; i++) {
        LL x = arr[i].fi - r * arr[i].se;
        LL y = arr[i].fi + r * arr[i].se;
        uniq.push_back(y);
        arr[i] = {x,y};
    }
    uniq.push_back((LL)-4e18);

    memset(BIT,0,sizeof BIT);
    sort(arr,arr + n);
    make(uniq);

    for(int i = 0 ; i < n ; i++) {
        arr[i].se = ID(arr[i].se,uniq);
        int ret = 1 + query(arr[i].se);
        update(arr[i].se,ret);
    }

    return query(uniq.size() - 1);
}

int main() {
    while(read()) {
        printf("%d\n",solve());
    }
    return 0;
}
