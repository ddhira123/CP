#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MX = 13;

int vis[N][(1 << MX) + 5];
int psum[N];
int arr[N];
int msb[(1 << MX) + 5];
int n;

void precompute() {
    for(int i = 1 ; i <= (1 << MX) ; i++)
        for(int j = 0 ; j <= MX ; j++)
            if(i & (1 << j))
                msb[i] = j;
}

void merge(int &a,int &b) {
    if(a > 0 && b > 0 && msb[a] == msb[b]) {
        a += (1 << msb[a]);
        b -= (1 << msb[b]);
    }
}

int dfs(int now,int sum) {
    if(now > n) {
        int r = psum[n] - sum;
        int l = sum;
        merge(l,r);
        if(r != 0 || __builtin_popcount(l) != 1)
            return 0;
        return 1;
    }

    int l = sum;
    int r = psum[now] - l - arr[now];
    merge(l,r);

    int &ret = vis[now][l];
    if(ret != -1) return ret;
    ret = 0;

    //tambah kiri
    if(l == 0 || (l & -l) >= arr[now])
        ret |= dfs(now + 1,l + arr[now]);

    //tambah kanan
    if(r == 0 || (r & -r) >= arr[now])
        ret |= dfs(now + 1,l);

    //tambah kanan, TAPI MASUK KE KIRI
    if(r == 0 && l > 0 && (1 << msb[l]) <= arr[now])
        ret |= dfs(now + 1,l + arr[now]);

    return ret;
}

void backtrack(int now,int sum) {
    if(now > n) {
        puts("");
        return;
    }

    int l = sum;
    int r = psum[now] - l - arr[now];
    merge(l,r);

    //tambah kiri
    if(l == 0 || (l & -l) >= arr[now]) {
        if(dfs(now + 1,l + arr[now])) {
            printf("l");
            backtrack(now + 1,l + arr[now]);
            return;
        }
    }

    //tambah kanan
    if(r == 0 || (r & -r) >= arr[now]) {
        if(dfs(now + 1,l)) {
            printf("r");
            backtrack(now + 1,l);
            return ;
        }
    }

    //tambah kanan, TAPI MASUK KE KIRI
    if(r == 0 && l > 0 && (1 << msb[l]) <= arr[now]) {
        if(dfs(now + 1,l + arr[now])) {
            printf("r");
            backtrack(now + 1,l + arr[now]);
            return;
        }
    }
}

int main() {
    precompute();
    int t; scanf("%d",&t);
    for(int tc = 1 ; tc <= t ; tc++) {
        scanf("%d",&n);
        for(int i = 1 ; i <= n ; i++) {
            scanf("%d",arr + i);
            psum[i] = psum[i - 1] + arr[i];
        }

        if(__builtin_popcount(psum[n]) != 1) {
            puts("no");
        }
        else {
            for(int i = 1 ; i <= n ; i++)
                for(int j = 0 ; j <= psum[i] ; j++)
                    vis[i][j] = -1;

            if(dfs(1,0)) {
                backtrack(1,0);
            }   
            else {
                puts("no");
            }
        }
    }
    return 0;
}