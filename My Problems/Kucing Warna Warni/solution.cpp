#include <bits/stdc++.h>
using namespace std;

int n, m, k;

int get_lower_bound() {
    return n;
}

long long get_upper_bound() {
    long long ret = 0;
    for(int i = 1 ; i <= n ; i++)
        ret += min(m, i);
    return ret;
}

vector<int> get_answer() {
    long long lb = get_lower_bound();
    long long ub = get_upper_bound();
    vector<int> ans(n, -1);

    if(lb <= k && k <= ub) {
        for(int i = 1 ; i <= n ; i++) {
            if(min(m, i) + n-i >= k) {
                int sisa = k-(n-i);
                int prv = i-sisa;

                ans[i-1] = prv == 0 ? (i-1) % m + 1 : ans[prv-1];

                for(int j = i+1 ; j <= n ; j++)
                    ans[j-1] = ans[i-1];

                break;
            } else {
                ans[i-1] = (i-1) % m + 1;
                k -= min(m, i);
            }
        }
    }

    return ans;
}

void read() {
    scanf("%d %d %d", &n, &m, &k);
}

void solve() {
    vector<int> answer = get_answer();

    for(int i = 0 ; i < answer.size() ; i++)
        printf("%d%c", answer[i], i+1 == answer.size() ? '\n' : ' ');
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        solve();
    }
    return 0;
}