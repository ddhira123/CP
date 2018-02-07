#include <bits/stdc++.h>
using namespace std;

const int MX = 2e6 + 5;
const int ALPHA = 26;
const int N = 1e5 + 5;

string read_string() {
    static char str[MX];
    scanf("%s", str);
    return (string)str;
}

int trie[MX][ALPHA];
int fail[MX];
int depth[MX];
int trie_sz = 1;

string arr[N];
int node[N];
int n, q;

vector<int> chld[MX];
int in[MX], ot[MX];
int cntr;
int BIT[MX];

int tampung[MX];

void update(int x, int val) {
    for( ; x <= cntr ; x += x & -x) {
        BIT[x] += val;
    }
}

int query(int x) {
    int ret = 0;
    while(x) {
        ret += BIT[x];
        x -= x & -x;
    }
    return ret;
}

int query(int l, int r) {
    return query(r) - query(l-1);
}

void add_trie(int idx) {
    int cur = 1;

    for(char x : arr[idx]) {
        int ch = x - 'a';

        if(trie[cur][ch] == 0) {
            trie[cur][ch] = ++trie_sz;
        }

        cur = trie[cur][ch];
    }

    node[idx] = cur;
}

void make_aho() {
    queue<int> q;
    for(int i = 0 ; i < ALPHA ; i++) {
        if(trie[1][i] == 0) {
            trie[1][i] = 1;
        } else {
            q.push(trie[1][i]);
            fail[trie[1][i]] = 1;
        }
    }

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        chld[fail[now]].push_back(now);

        for(int i = 0 ; i < ALPHA ; i++) {
            if(trie[now][i] == 0) {
                trie[now][i] = trie[fail[now]][i];
            } else {
                q.push(trie[now][i]);
                fail[trie[now][i]] = trie[fail[now]][i];
            }
        }
    }
}

void dfs(int now) {
    in[now] = ++cntr;

    for(int nex : chld[now]) {
        depth[nex] = depth[now] + 1;
        dfs(nex);
    }

    ot[now] = cntr;
}

void add_str(string str) {
    priority_queue<pair<int, int>> vis;
    vis.push({0, 1});
    int cur = 1;

    for(char x : str) {
        int ch = x - 'a';
        cur = trie[cur][ch];

        vis.push({depth[cur], cur});
    }

    int lst = -1;
    while(!vis.empty()) {
        pair<int, int> now = vis.top();
        vis.pop();

        int dep = now.first;
        int cur = now.second;

        if(lst == cur) continue;
        lst = cur;

        update(in[cur], 1 - tampung[cur]);
        tampung[cur] = 0;

        if(cur != 1) {
            tampung[fail[cur]]++;
            vis.push({dep-1, fail[cur]});
        }
    }
}

int solve(int idx) {
    int nod = node[idx];
    return query(in[nod], ot[nod]);
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        arr[i] = read_string();
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        add_trie(i);
    }
    make_aho();
    dfs(1);
}

void work() {
    scanf("%d", &q);
    for(int i = 0 ; i < q ; i++) {
        int opt; scanf("%d", &opt);

        if(opt == 1) {
            string str = read_string();
            add_str(str);
        } else {
            int idx; scanf("%d", &idx);
            printf("%d\n", solve(idx));
        }
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}
