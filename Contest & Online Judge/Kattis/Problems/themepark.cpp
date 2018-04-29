#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int arr[N];

int vis[N];
int sum[N];
int nxt[N];

int r, k, n;

int get(int x) {
    if(sum[x] != -1) return sum[x];

    sum[x] = 0;
    nxt[x] = x;

    for(int i = 0 ; i < n ; i++) {
        sum[x] += arr[(i + x) % n];
        nxt[x] = (i + x) % n;

        if(sum[x] > k) {
            sum[x] -= arr[(i + x) % n];
            break;
        }
    }

    return sum[x];
}

void read() {
    scanf("%d %d %d", &r, &k, &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

long long work() {
    memset(vis, -1, sizeof vis);
    memset(sum, -1, sizeof sum);

    long long ret = 0;
    int cur = 0;

    for(int i = 0 ; i < r ; i++) {
        if(vis[cur] == -1) {
            vis[cur] = i;
            ret += get(cur);
            cur = nxt[cur];
        } else {
            int cycle = i - vis[cur];
            int sisa = r - i;

            int loop = sisa / cycle;
            int tail = sisa % cycle;

            long long in_cycle = 0;
            int now = cur;

            for(int j = 0 ; j < cycle ; j++) {
                in_cycle += get(now);
                now = nxt[now];
            }

            ret += in_cycle * loop;
            now = cur;

            for(int j = 0 ; j < tail ; j++) {
                ret += get(now);
                now = nxt[now];
            }

            break;
        }
    }

    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("Case #%d: %lld\n", tc, work());
    }
    return 0;
}