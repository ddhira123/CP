#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int DIGIT = 20;

vector<int> adj[N];
int worst[N];
int sz[N];
bool blocked[N];

long long ans[N];
long long cnt[N];

char s[N];

int mpa[1 << DIGIT];

vector<int> seen;

int n;

void dfs(int now, int prv) {
    seen.push_back(now);
    worst[now] = 0;
    sz[now] = 1;

    for(int nex : adj[now]) {
        if(nex == prv || blocked[nex]) continue;
        dfs(nex, now);
        sz[now] += sz[nex];
        worst[now] = max(worst[now], sz[nex]);
    }
}

vector<int> seen_mask;
vector<int> seen_glob;

void dfs_populate(int now, int prv, int mask, int root_val) {
    mask ^= (1 << (s[now] - 'a'));
    cnt[now] = 0;

    cnt[now] += mpa[mask];

    for(int i = 0 ; i < DIGIT ; i++) {
        int nmask = mask ^ (1 << i);
        cnt[now] += mpa[nmask];
    }
    seen_mask.push_back(mask ^ root_val);

    // if(now == 0 && cnt[now] != 0) {
    //     // cout << "adsadsa " << mask << " " << root_val << endl;
    // }

    for(int nex : adj[now]) {
        if(nex == prv || blocked[nex]) continue;
        dfs_populate(nex, now, mask, root_val);
    }
}

void dfs_upward(int now, int prv) {
    for(int nex : adj[now]) {
        if(nex == prv || blocked[nex]) continue;
        dfs_upward(nex, now);
        cnt[now] += cnt[nex];
    }
    ans[now] += cnt[now];
}

queue<int> q;

void centroid_work(int x) {
    seen.clear();
    dfs(x, -1);
    int root = x;

    for(int y : seen) {
        worst[y] = max(worst[y], sz[x] - sz[y]);
        if(worst[y] < worst[root]) {
            root = y;
        }
    }


    int root_val = 1 << (s[root] - 'a');

    mpa[root_val] = 1;

    seen_glob.clear();
    seen_glob.push_back(root_val);

    for(int nex : adj[root]) {
        if(!blocked[nex]) {
            seen_mask.clear();

            dfs_populate(nex, root, 0, root_val);

            for(int x : seen_mask) {
                mpa[x]++;
                seen_glob.push_back(x);
            }
        }
    }

    dfs_upward(root, -1);

    for(int it : seen) {
        cnt[it] = 0;
    }
    reverse(adj[root].begin(), adj[root].end());
    
    for(int x : seen_glob) {
        mpa[x] = 0;
    }
    seen_glob.clear();

    for(int nex : adj[root]) {
        if(!blocked[nex]) {
            seen_mask.clear();

            dfs_populate(nex, root, 0, root_val);

            for(int x : seen_mask) {
                mpa[x]++;
                seen_glob.push_back(x);
            }
        }
    }

    dfs_upward(root, -1);
    ans[root] -= cnt[root];
    cnt[root] = 0;

    // cout << root << " " << ans[root] << "aaa\n";

    for(int it : seen) {
        cnt[it] = 0;
    }
    for(int x : seen_glob) {
        mpa[x] = 0;
    }

    blocked[root] = 1;

    for(int nex : adj[root]) {
        if(!blocked[nex]) {
            q.push(nex);
        }
    }
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%s", s);
}

void work() {
    q.push(1);
    while(!q.empty()) {
        int now = q.front();
        q.pop();

        centroid_work(now);
    }

    for(int i = 0 ; i < n ; i++) {
        printf("%lld ", ans[i] + 1);
    }
}

int main() {
    read();
    work();
    return 0;
} 