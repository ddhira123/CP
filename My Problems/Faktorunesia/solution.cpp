#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MAX = 4005;
const int MOD = 1e9 + 7;

bool can[N][MAX];
bool done[N][MAX];
vector<pair<int, int>> adj[N];
int fact[MAX];
int n, m;

// initialize factorial
void precompute() {
    fact[0] = 1;
    for(int i = 1 ; i < MAX ; i++)
        fact[i] = 1ll * i * fact[i-1] % MOD;
}

// check whether if it's possible to reach node now using current_idx step
bool dfs_check(int now, int current_idx) {
    if(current_idx == 0) {
        return now == 1;
    }
    if(done[now][current_idx]) {
        return can[now][current_idx];
    }

    done[now][current_idx] = true;
    can[now][current_idx] = false;

    for(pair<int, int> edge : adj[now]) {
        if(edge.second >= current_idx) continue;
        can[now][current_idx] |= dfs_check(edge.first, current_idx - 1);
    }

    return can[now][current_idx];
}

// get all node visited from n using 0-valued edge
vector<int> get_all_possible_end() {
    vector<bool> vis(n+1, false);
    queue<int> q;
    vector<int> ret;

    vis[n] = true;
    q.push(n);

    while(!q.empty()) {
        int now = q.front();
        q.pop();
        ret.push_back(now);

        for(pair<int, int> edge : adj[now]) {
            if(edge.second != 0 || vis[edge.first]) continue;
            vis[edge.first] = true;
            q.push(edge.first);
        }
    }

    return ret;
}

int get_answer() {
    vector<int> ends = get_all_possible_end();
    int min_highest = MAX;

    // get minimum step needed to get to any of ends
    for(int end : ends) {
        for(int i = 0 ; i < MAX ; i++)
            if(dfs_check(end, i)) {
                min_highest = min(min_highest, i);
            }
    }

    // if there's no way to visit any of those ends
    if(min_highest == MAX) {
        return -1;
    }

    vector<int> candidate;
    for(int end : ends)
        if(dfs_check(end, min_highest)) {
            candidate.push_back(end);
        }

    vector<bool> vis(n+1, false);
    int answer = 0;
    for(int i = min_highest ; i >= 1 ; i--) {
        int mins = MAX;
        
        // find minimum cost needed on this step
        for(int cur : candidate) {
            for(pair<int, int> edge : adj[cur]) {
                if(edge.second < i && dfs_check(edge.first, i-1))
                    mins = min(mins, edge.second);
            }
        }

        answer = (answer + 1ll * fact[i] * mins) % MOD;

        fill(vis.begin(), vis.end(), false);
        vector<int> next_candidate;

        // find every possible next node to use in step-1
        for(int cur : candidate) {
            for(pair<int, int> edge : adj[cur]) {
                if(edge.second == mins && dfs_check(edge.first, i-1) && !vis[edge.first]) {
                    vis[edge.first] = true;
                    next_candidate.push_back(edge.first);
                }
            }
        }

        candidate = next_candidate;
    }

    return answer;
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

int main() {
    precompute();
    read();
    printf("%d\n", get_answer());
    return 0;
}
