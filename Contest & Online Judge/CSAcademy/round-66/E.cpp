#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct DSU {
    int pset[N];

    DSU() {
        memset(pset, -1, sizeof pset);
    }

    int finds(int x) {
        return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
    }

    void join(int x, int y) {
        x = finds(x);
        y = finds(y);

        if(x != y) {
            pset[x] += pset[y];
            pset[y] = x;
        } else {
            assert(0);
        }
    }
} kiri, kanan;

int a[N], b[N];
int v[N];
int n, real_n;
vector<int> adj[N];
int iter[N];
bool used[N];

bool visited[N];

vector<int> path;

int prv[N], nxt[N];

int face[N];

void dfs_component(int now, vector<int> &seen) {
    if(visited[now]) {
        return;
    }
    visited[now] = true;
    seen.push_back(now);

    for(int i : adj[now]) {
        int nex = a[i] ^ b[i] ^ now;
        dfs_component(nex, seen);
    }
}

void add_additional() {
    vector<vector<int>> zero, one;

    priority_queue<pair<int, int>> pq;

    for(int i = 1 ; i <= n ; i++)
        if(!visited[i]) {
            vector<int> v;
            dfs_component(i, v);

            vector<int> nol, satu;
            for(int x : v) {
                if(adj[x].size() & 1) {
                    satu.push_back(x);
                } else {
                    nol.push_back(x);
                }
            }

            zero.push_back(nol);
            one.push_back(satu);

            pq.push({one.back().size(), one.size()-1});
        }

    while(pq.size() > 1) {
        pair<int, int> x = pq.top();
        pq.pop();

        pair<int, int> y = pq.top();
        pq.pop();

        int ii, jj;

        if(x.first > 0 && y.first > 0) {
            ii = one[x.second].back();
            jj = one[y.second].back();

            one[x.second].pop_back();
            one[y.second].pop_back();

            ++n;
            a[n] = ii, b[n] = jj;
            adj[ii].push_back(n);
            adj[jj].push_back(n);


            zero[x.second].push_back(ii);
            zero[y.second].push_back(jj);
        } else if(x.first > 0) {
            ii = one[x.second].back();
            jj = zero[y.second].back();

            one[x.second].pop_back();
            zero[y.second].pop_back();

            ++n;
            a[n] = ii, b[n] = jj;
            adj[ii].push_back(n);
            adj[jj].push_back(n);


            zero[x.second].push_back(ii);
            one[y.second].push_back(jj);
        } else if(y.first > 0) {
            ii = zero[x.second].back();
            jj = one[y.second].back();

            zero[x.second].pop_back();
            one[y.second].pop_back();

            ++n;
            a[n] = ii, b[n] = jj;
            adj[ii].push_back(n);
            adj[jj].push_back(n);


            one[x.second].push_back(ii);
            zero[y.second].push_back(jj);
        } else {
            ii = zero[x.second].back();
            jj = zero[y.second].back();

            zero[x.second].pop_back();
            zero[y.second].pop_back();

            ++n;
            a[n] = ii, b[n] = jj;
            adj[ii].push_back(n);
            adj[jj].push_back(n);


            one[x.second].push_back(ii);
            one[y.second].push_back(jj);
        }

        if(one[x.second].size() + zero[x.second].size() >= one[y.second].size() + zero[y.second].size()) {
            for(int it : one[y.second]) {
                one[x.second].push_back(it);
            }
            one[y.second].clear();

            for(int it : zero[y.second]) {
                zero[x.second].push_back(it);
            }
            zero[y.second].clear();

            pq.push({one[x.second].size(), x.second});
        } else {
            for(int it : one[x.second]) {
                one[y.second].push_back(it);
            }
            one[x.second].clear();

            for(int it : zero[x.second]) {
                zero[y.second].push_back(it);
            }
            zero[x.second].clear();

            pq.push({one[y.second].size(), y.second});
        }

        // cout << "tambah " << ii << " " << jj << endl;
    }

    int idx = pq.top().second;
    while(one[idx].size() > 2) {
        int ii = one[idx].back();
        one[idx].pop_back();
        int jj = one[idx].back();
        one[idx].pop_back();

        // cout << "tambah2 " << ii << " " << jj << endl;

        ++n;
        a[n] = ii, b[n] = jj;
        adj[ii].push_back(n);
        adj[jj].push_back(n);
    }
}

void eulerian(int now, vector<int> &stek) {
    int &i = iter[now];

    while(i < adj[now].size()) {
        int cur = adj[now][i];
        i++;

        if(used[cur]) {
            continue;
        }
        used[cur] = 1;

        int nex = now ^ a[cur] ^ b[cur];

        // cout << cur << " " << now << " " << nex << endl;
        eulerian(nex, stek);
    }

    stek.push_back(now);
}

void read() {
    scanf("%d", &n);
    real_n = n;

    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", &a[i], &b[i]);

        adj[a[i]].push_back(i);
        adj[b[i]].push_back(i);
    }

    for(int i = 1 ; i < n ; i++) {
        scanf("%d", &v[i]);
    }
}

void prepare() {
    add_additional();
    int st = 1;

    for(int i = 1 ; i <= n ; i++) {
        if(adj[i].size() & 1) {
            st = i;
        }
    }

    eulerian(st, path);

    map<pair<int, int>, set<int>> mp;
    for(int i = 1 ; i <= n ; i++) {
        int l = a[i], r = b[i];
        if(l > r) swap(l, r);

        if(mp.count({l, r}) == 0) {
            mp[{l, r}] = {i};
        } else {
            mp[{l, r}].insert(i);
        }
    }

    vector<int> paths;
    for(int i = 1 ; i < path.size() ; i++) {
        int l = path[i-1], r = path[i];
        if(l > r) swap(l, r);

        int idx = *(mp[{l, r}].begin());
        mp[{l, r}].erase(idx);

        paths.push_back(idx);

        if(idx <= real_n) {
            face[idx] = (path[i-1] != a[idx]);
        }
    }

    for(auto it : mp) {
        assert(it.second.empty());
    }

    int lst = -1;

    for(int i = 0 ; i < paths.size() ; i++) {
        int now = paths[i];
        // printf("now %d\n", now);
        
        if(now <= real_n) {
            if(lst != -1) {
                // printf("joining %d %d\n", lst, now);
                nxt[lst] = now;
                prv[now] = lst;
            }
            lst = now;
        }
    }
}

void work() {
    vector<pair<int, int>> ans;

    for(int i = 1 ; i < real_n ; i++) {
        int cur_v = v[i];
        int l = kiri.finds(cur_v);
        int r = kanan.finds(cur_v);

        // printf("cur %d l %d r %d prvl %d nxtr %d\n", cur_v, l, r, prv[l], nxt[r]);

        if(prv[l] != 0) {
            int ll = kiri.finds(prv[l]);
            ans.push_back({ll, l});
            // assert()

            kiri.join(ll, l);
            kanan.join(r, kanan.finds(ll));
        } else {
            int ll = kiri.finds(nxt[r]);
            ans.push_back({l, ll});

            kiri.join(l, ll);
            kanan.join(kanan.finds(ll), r);
        }
    }
    for(pair<int, int> x : ans) {
        printf("%d %d\n", x.first, x.second);

        // assert(1 <= x.first && x.first <= real_n);
        // assert(1 <= x.second && x.second <= real_n);
    }
    for(int i = 1 ; i <= real_n ; i++) {
        printf("%d%c", face[i], i == real_n ? '\n' : ' ');
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}