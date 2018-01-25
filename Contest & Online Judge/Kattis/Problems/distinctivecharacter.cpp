#include <bits/stdc++.h>
using namespace std;

const int K = 20;

int n, k;
int dist[1 << K];

void read() {
    cin >> n >> k;
    for(int i = 0 ; i < n ; i++) {
        string s; cin >> s;
        int mask = 0;

        for(int j = 0 ; j < k ; j++) {
            if(s[j] == '1') {
                mask |= (1 << j);
            }
        }

        dist[mask] = 0;
    }
}

void BFS() {
    queue<int> q;
    for(int i = 0 ; i < (1 << k) ; i++) {
        if(dist[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(int i = 0 ; i < k ; i++) {
            int nex = now ^ (1 << i);
            if(dist[nex] == -1) {
                dist[nex] = dist[now] + 1;
                q.push(nex);
            }
        }
    }
}

void solve() {
    BFS();
    int maks = -1;
    int ans = 0;

    for(int i = 0 ; i < (1 << k) ; i++) {
        if(dist[i] > maks) {
            maks = dist[i];
            ans = i;
        }
    }

    for(int i = 0 ; i < k ; i++) {
        if(ans & (1 << i)) cout << "1";
        else cout << "0";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(dist, -1, sizeof dist);

    read();
    solve();
    return 0;
}