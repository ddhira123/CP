#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

vector<int> chld[N];
int n;
bool ok = true;

int dfs(int x) {
    if(chld[x].size() == 0) return 1;

    int tot = 0;
    for(int nex : chld[x]) {
        tot += dfs(nex);
    }

    if(tot < 3) {
        ok = false;
    }

    return 0;
}

int main() {
    cin >> n;
    for(int i = 2 ; i <= n ; i++) {
        int x; cin >> x;
        
        chld[x].push_back(i);
    }

    dfs(1);

    printf("%s\n", ok ? "Yes" : "No");
    return 0;
}