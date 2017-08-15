#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int M = 205;

struct Data {
    int first_person;
    int second_person;
    int pos_first;
};

int n, m;
vector<int> a, b;
int dist[N][N][M];
bool vis[N][N][M];

void read() {
    cin >> m >> n;
    a.resize(n+1);
    b.resize(n+1);

    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; i++) {
        cin >> b[i];
    }
}

int solve() {
    a[0] = 0;
    b[0] = m/2;

    for(int i = 1 ; i <= n+1 ; i++)
        for(int j = 1 ; j <= n+1 ; j++)
            for(int k = 0 ; k < m ; k++)
                dist[i][j][k] = 1e9;

    dist[1][1][0] = 0;

    deque<Data> dq;
    dq.push_back((Data){1, 1, 0});

    while(!dq.empty()) {
        Data now = dq.front();
        dq.pop_front();

        int first_person = now.first_person;
        int second_person = now.second_person;
        int pos_first = now.pos_first;
        int pos_second = (now.pos_first + m/2) % m;

        if(vis[first_person][second_person][pos_first]) continue;
        vis[first_person][second_person][pos_first] = true;

        int cur_dist = dist[first_person][second_person][pos_first];

        if(first_person <= n && pos_first == a[first_person]) {
            if(cur_dist < dist[first_person+1][second_person][pos_first]) {
                dist[first_person+1][second_person][pos_first] = cur_dist;
                dq.push_front((Data){first_person+1, second_person, pos_first});
            }
        }

        if(second_person <= n && pos_second == b[second_person]) {
            if(cur_dist < dist[first_person][second_person+1][pos_first]) {
                dist[first_person][second_person+1][pos_first] = cur_dist;
                dq.push_front((Data){first_person, second_person+1, pos_first});
            }
        }

        for(int i = -1 ; i <= 1 ; i += 2) {
            int next_pos = (pos_first + m + i) % m;

            if(cur_dist + 1 < dist[first_person][second_person][next_pos]) {
                dist[first_person][second_person][next_pos] = cur_dist + 1;
                dq.push_back((Data){first_person, second_person, next_pos});
            }
        }
    }

    int ret = 1e9;
    for(int i = 0 ; i < m ; i++)
        ret = min(ret, dist[n+1][n+1][i]);

    return ret;
}

int main() {
    read();
    int ret = solve();

    cout << ret << endl;
    return 0;
}
