#include <bits/stdc++.h>
using namespace std;

const int DIGIT = 10;
const int MAX_LEN = 20;
const int MOD = 1e9 + 7;
const int K = 15;

long long dp[MAX_LEN][1 << DIGIT][2];

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}


long long solve(int pos, int mask, int is_less, string &str) {
    if(pos == -1) {
        return mask == 0;
    }

    long long &ret = dp[pos][mask][is_less];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    if(is_less) {
        for(int i = 0 ; i <= 9 ; i++) {
            int nmask = mask;
            if(mask & (1 << i)) {
                nmask ^= (1 << i);
            }

            ret += solve(pos-1, nmask, is_less, str);
        }
    } else {
        for(int i = 0 ; i <= str[pos] - '0' ; i++) {
            int nmask = mask;
            if(mask & (1 << i)) {
                nmask ^= (1 << i);
            }

            ret += solve(pos-1, nmask, i < (str[pos] - '0'), str);
        }
    }

    return ret;
}

string to_str(long long x) {
    string ret = "";
    while(x) {
        ret += (char)(x % 10 + '0');
        x /= 10;
    }
    return ret;
}

vector<long long> calc(long long x) {
    vector<long long> v(1 << DIGIT, 0);
    if(x == 0) return v;

    string str = to_str(x);
    int len = str.length();

    memset(dp, -1, sizeof dp);

    for(int i = 0 ; i+1 < len; i++) {
        for(int mask = 0 ; mask < (1 << DIGIT) ; mask++) {
            for(int highest_digit = 1 ; highest_digit < DIGIT ; highest_digit++) {
                int nmask = mask;
                if(mask & (1 << highest_digit)) {
                    nmask ^= (1 << highest_digit);
                }

                v[mask] += solve(i-1, nmask, 1, str);
            }
        }
    }

    {
        for(int mask = 0 ; mask < (1 << DIGIT) ; mask++) {
            for(int highest_digit = 1 ; highest_digit <= str[len-1] - '0' ; highest_digit++) {
                int nmask = mask;
                if(mask & (1 << highest_digit)) {
                    nmask ^= (1 << highest_digit);
                }

                v[mask] += solve(len-2, nmask, highest_digit + '0' < str[len-1], str);
            }
        }
    }

    return v;
}

int get_comb(long long n, int k) {
    if(n < k) return 0;

    vector<long long> v;
    for(int i = 0 ; i < k ; i++) {
        v.push_back(n - i);
    }

    for(int i = 2 ; i <= k ; i++) {
        int cur = i;

        for(long long &x : v) {
            long long fpb = gcd(x, cur);
            x /= fpb;
            cur /= fpb;

            if(cur == 1) {
                break;
            }
        }
    }

    int ret = 1;
    for(long long x : v) {
        int modx = x % MOD;

        ret = 1ll * ret * modx % MOD;
    }

    return ret;
}

int work(long long a, long long b, int k, int d) {
    vector<long long> vb = calc(b);
    vector<long long> va = calc(a-1);

    vector<long long> v = vb;
    for(int i = 0 ; i < v.size() ; i++) {
        v[i] = vb[i] - va[i];
        v[i] = get_comb(v[i], k);
    }

    int ret = 0;
    for(int i = (1 << DIGIT)-1 ; i >= 0 ; i--) {
        if(__builtin_popcount(i) == d) {
            ret = (ret + v[i]) % MOD;
        }

        for(int j = i & (i - 1) ; ; j = i & (j - 1)) {
            v[j] = (v[j] - v[i] + MOD) % MOD;
            if(j == 0) {
                break;
            }
        }
    }

    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        long long a, b;
        int k, d;

        cin >> a >> b >> k >> d;

        cout << work(a, b, k, d) << endl;
    }
    return 0;
}