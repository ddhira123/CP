#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MOD = 1e9 + 7;

struct Path {
    vector<int> v;

    void clear() {
        v.clear();
    }

    bool is_empty() {
        return v.empty();
    }

    void add(int x) {
        v.push_back(x);
    }

    void pop() {
        v.pop_back();
    }

    bool operator <(const Path &other) const {
        int i = 0;
        while(i < v.size() && v[i] == 0) i++;
        int j = 0;
        while(j < other.v.size() && other.v[j] == 0) j++;

        if(v.size() - i < other.v.size() - j) return true;
        if(v.size() - i > other.v.size() - j) return false;
        for(int k = 0 ; k < v.size() - i ; k++) {
            if(v[i + k] < other.v[j + k]) return true;
            if(v[i + k] > other.v[j + k]) return false;
        }

        return true;
    }

    int get_val() {
        int ret = 0;
        int mul = 1;
        int it = 0;

        for(int i = v.size()-1 ; i >= 0 ; i--) {
            mul = 1ll * mul * (it+1) % MOD;
            ret = (ret + 1ll * mul * v[i]) % MOD;
            it++;
        }
        return ret;
    }
};

int n, m;
vector<pair<int,int>> adj[N];
Path dist[N];
bool vis[N];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

int work() {
    set<pair<Path, int>> st;
    dist[n].add(0);
    st.insert({dist[n], n});

    while(!st.empty()) {
        pair<Path, int> cur = *st.begin();
        st.erase(st.begin());

        if(vis[cur.second]) continue;
        vis[cur.second] = true;

        for(pair<int, int> edge : adj[cur.second]) {
            cur.first.add(edge.second);
            int nxt = edge.first;

            if(dist[nxt].is_empty() || cur.first < dist[nxt]) {
                dist[nxt] = cur.first;
                st.insert({dist[nxt], nxt});
            }

            cur.first.pop();
        }
    }

    Path ret;
    for(pair<int, int> edge : adj[1]) {
        if(vis[edge.first] && edge.second == 0) {
            dist[edge.first].add(0);
            if(ret.is_empty() || dist[edge.first] < ret) {
                ret = dist[edge.first];
            }
            dist[edge.first].pop();
        }
    }

    return ret.is_empty() ? -1 : ret.get_val();
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}