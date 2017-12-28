#include <bits/stdc++.h>
using namespace std;

const int MX = 5e5 + 5;

int pset[MX];
map<int,int> cnt;
vector<pair<int,int>> v;

void init() {
    memset(pset,-1,sizeof pset);
}

int finds(int x) {
    int root = x;
    while(pset[root] >= 0) root = pset[root];
    while(x != root) {
        int y = pset[x];
        pset[x] = root;
        x = y;
    }
    return root;
}

void join(int x,int y) {
    x = finds(x);
    y = finds(y);
    if(x == y) return;
    pset[x] += pset[y];
    pset[y] = x;
}

int solve() {
    cnt.clear();
    v.clear();

    int m; scanf("%d",&m);
    for(int i = 0 ; i < m ; i++) {
        int x; scanf("%d",&x);
        cnt[finds(x)]++;
    }

    for(auto it : cnt)
        v.push_back(it);

    for(pair<int,int> x : v)
        if(-pset[x.first] != x.second) 
            return 0;

    for(int i = 1 ; i < v.size() ; i++)
        join(v[0].first,v[i].first);
    return 1;   
}

int main() {
    init();
    int n; scanf("%d",&n);
    int ret = 0;
    for(int i = 0 ; i < n ; i++) {
        int add = solve();
        ret += add;
    }
    printf("%d\n",ret);
    return 0;
}

