#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair

vector<pii> arr;
int ans[100005];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        arr.push_back(mp(x, i));
    }

    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        ans[arr[i].se] = n-i;
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
}