#include <bits/stdc++.h>
using namespace std;

typedef pair<int, pair<int,int>> data;

const int N = 55;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int dist[N][N][N];
int height[N][N];
int rowS[N], colS[N];

int r, c, n;

int minCost[N][N];
bool active[N][N];
int dp[N][N];
int cur_col, cur_student;

void read() {
    scanf("%d %d %d", &r, &c, &n);
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++) {
            scanf("%d", &height[i][j]);

            if(height[i][j] < 0) {
                int idx = -height[i][j] - 1;
                height[i][j] = 0;

                rowS[idx] = i;
                colS[idx] = j;
            }
        }
}

void dijkstra(int column) {
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++) {
            dist[column][i][j] = INF;
        }
    dist[column][0][column] = 1;

    priority_queue<data> pq;

    pq.push({-1, {0, column}});

    while(!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        int dis = -cur.first;
        int row = cur.second.first;
        int col = cur.second.second;

        if(dis != dist[column][row][col]) continue;

        // printf("%d %d %d -> %d\n", column, row, col, dis);

        for(int i = 0 ; i < 4 ; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(nr >= 0 && nr < r && nc >= 0 && nc < c) {
                int ndis = dis + 1 + abs(height[row][col] - height[nr][nc]);

                if(ndis < dist[column][nr][nc]) {
                    dist[column][nr][nc] = ndis;
                    pq.push({-ndis, {nr, nc}});
                }
            }
        }
    }
}

void prepare() {
    for(int i = 0 ; i < c ; i++) {
        dijkstra(i);

        for(int j = 0 ; j < n ; j++) {
            minCost[i][j] = dist[i][rowS[j]][colS[j]];
            active[i][j] = false;
        }
    }
}

int solve(int col, int student) {
    if(student == n) {
        return 1;
    }
    if(col == c) {
        return 0;
    }

    int &ret = dp[col][student];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    if(col == cur_col) {
        if(student != cur_student) return ret = 0;
        return ret = solve(col+1, student+1);
    }
    if(student == cur_student) {
        if(col > cur_col) return ret = 0;
        return ret = solve(cur_col+1, student+1);
    }

    ret = solve(col+1, student);
    if(active[col][student]) {
        ret = (ret + solve(col+1, student+1)) % MOD;
    }

    return ret;
}

int work() {
    vector<pair<int ,int>> v;
    for(int i = 0 ; i < c ; i++)
        for(int j = 0 ; j < n ; j++) {
            v.push_back({i, j});
        }

    sort(v.begin(), v.end(), [&] (pair<int ,int> a, pair<int ,int> b){
        return minCost[a.first][a.second] < minCost[b.first][b.second];
    });

    int ret = 0;
    for(auto x : v) {
        memset(dp, -1, sizeof dp);
        cur_col = x.first;
        cur_student = x.second;

        int ways = solve(0, 0);
        int add = 1ll * ways * minCost[cur_col][cur_student] % MOD;
        ret = (ret + add) % MOD;

        active[cur_col][cur_student] = true;
    }

    return ret;
}

int main() {

    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();

        cout << work() << endl;
    }
    return 0;
}