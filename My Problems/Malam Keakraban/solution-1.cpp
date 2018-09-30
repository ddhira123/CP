#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int n;
int arr[N];

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

int calc(vector<int> &v) {
    int ret = 0;

    for(int i = 0 ; i < v.size() ; i++) {
        int j = (i + 1) % v.size();

        ret += (arr[v[i]] == arr[v[j]]);
    }

    return ret;
}

void solve() {
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 1);

    vector<int> permut = ans;

    do {
        if(calc(ans) > calc(permut)) {
            ans = permut;
        }
    } while(next_permutation(permut.begin(), permut.end()));

    for(int i = 0 ; i < ans.size() ; i++) {
        printf("%d%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
    }
}

int main() {
    read();
    solve();
    return 0;
}