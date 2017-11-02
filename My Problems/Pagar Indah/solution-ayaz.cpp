#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

long long dp[N][3][3][3];
int arr[N];
vector<pair<int, int>> v;
int n, k;

long long get_val(int x) {
    return 1ll * x * (x + 1) / 2;
}

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

void make() {
    for(int l = 1 ; l <= n ; ) {
        int r = l;

        while(r <= n && arr[r] == arr[l]) {
            r++;
        }

        v.push_back({arr[l], r - l});
        l = r;
    }
}

long long solve(int pos, int stat, int transfer, int k_left) {
    if(pos >= v.size()) {
        return 0;
    }

    long long &ret = dp[pos][stat][transfer][k_left];
    if(ret != -1) {
        return ret;
    }

    int cur = v[pos].second;
    if(stat == 1) {
        cur += transfer;
    } else if(stat == 2) {
        cur -= transfer;
    }

    if(cur == 0) {
        return ret = solve(pos+1, 0, 0, k_left);
    }

    // no transfer at all
    ret = solve(pos+1, 0, 0, k_left) + get_val(cur);

    // exactly one from this part
    if(cur >= 1 && k_left >= 1 && pos+1 < v.size()) {
        ret = max(ret, solve(pos+1, 1, 1, k_left-1) + get_val(cur-1));
    }
    // exacty two from this part
    if(cur >= 2 && k_left >= 2 && pos+1 < v.size()) {
        ret = max(ret, solve(pos+1, 1, 2, k_left-2) + get_val(cur-2));
    }
    // exactly one from this part and next part
    if(cur >= 1 && k_left >= 2 && pos+2 < v.size() && v[pos+1].second == 1) {
        ret = max(ret, solve(pos+2, 1, 2, k_left-2) + get_val(cur-1));
    }

    int sisa = k_left;
    for(int i = pos+1 ; i < v.size() ; i++) {
        ret = max(ret, solve(i, 0, 0, sisa) + get_val(cur));

        if(v[i].first == v[pos].first) {
            cur += v[i].second;
            ret = max(ret, solve(i+1, 0, 0, sisa) + get_val(cur));
        } else {
            if(sisa == 2) {
                // take one
                if(v[i].second == 1) {
                    cur++;
                    sisa--;

                    ret = max(ret, solve(i+1, 0, 0, sisa) + get_val(cur));
                } else {
                    ret = max(ret, solve(i, 2, 1, sisa-1) + get_val(cur+1));

                    if(v[i].second == 2) {
                        cur += 2;
                        sisa -= 2;

                        ret = max(ret, solve(i+1, 0, 0, sisa) + get_val(cur));
                    } else {
                        ret = max(ret, solve(i, 2, 2, sisa - 2) + get_val(cur+2));
                        break;
                    }
                }
            } else if(sisa == 1) {
                if(v[i].second == 1) {
                    cur++;
                    sisa--;

                    ret = max(ret, solve(i+1, 0, 0, sisa) + get_val(cur));
                } else {
                    ret = max(ret, solve(i, 2, 1, sisa-1) + get_val(cur+1));
                    break;
                }
            } else {
                break;
            }
        }
    }

    return ret;
}

int main() {
    read();
    make();

    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(0, 0, 0, k));
    return 0;
}
