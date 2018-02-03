// https://mathoverflow.net/questions/71802/analysis-of-misere-nim
#include <bits/stdc++.h>
using namespace std;

const int SQRT = 1e6 + 5;
const int MOD = 1e9 + 7;
const int MAX_DIVISOR = 40;
const int MAX_XOR = 64;

bool flag[SQRT];
int pwr[SQRT];
vector<int> primes;

vector<int> cnts;

int dp[MAX_DIVISOR][MAX_XOR][2];

// number of first case win, n_i > 1 for some i and xor-sum = 0
int solve(int cur, int nim, int exist) {
    if(cur == cnts.size()) {
        return exist && (nim == 0);
    }

    int &ret = dp[cur][nim][exist];
    if(ret != -1) return ret;

    if(cnts[cur] == 0) return ret = solve(cur+1, nim, exist);

    // skip entirely
    ret = solve(cur+1, nim, exist);
    // odd occurence
    ret = (ret + 1ll * solve(cur+1, nim ^ cur, exist | (cur > 1)) * pwr[cnts[cur]-1]) % MOD;
    // even occurence
    ret = (ret + 1ll * solve(cur+1, nim, exist | (cur > 1)) * (pwr[cnts[cur]-1]-1)) % MOD;

    return ret;
}

void precompute() {
    for(int i = 2 ; i < SQRT ; i++)
        if(!flag[i]) {
            primes.push_back(i);
            for(int j = i ; j < SQRT ; j += i)
                flag[j] = true;
        }

    // cout << primes.size() << endl;

    pwr[0] = 1;
    for(int i = 1 ; i < SQRT ; i++) {
        pwr[i] = pwr[i-1] + pwr[i-1];
        if(pwr[i] >= MOD) pwr[i] -= MOD;
    }
}

vector<int> populate(long long a, long long b) {
    vector<long long> v(b-a+1);
    vector<int> div_count(b-a+1, 0);
    iota(v.begin(), v.end(), a);

    for(int x : primes) {
        long long st = (a + x - 1) / x * x;

        if(st <= b) {
            for(int i = st - a ; i < v.size() ; i += x) {
                while(v[i] % x == 0) {
                    v[i] /= x;
                    div_count[i]++;
                }
            }
        }
    }

    for(int i = 0 ; i < v.size() ; i++) {
        if(v[i] != 1) {
            div_count[i]++;
        }
    }

    vector<int> cnt(MAX_DIVISOR, 0);
    for(int x : div_count) {
        cnt[x]++;
    }

    return cnt;
}

int work(long long a, long long b) {
    cnts = populate(a, b);
    memset(dp, -1, sizeof dp);

    // case 2: all n_i = 1, xor-sum = 1
    int ret = pwr[cnts[1]-1];
    ret = (ret + solve(1, 0, 0)) % MOD;

    return ret;
}

int main() {
    precompute();

    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        long long a, b;
        cin >> a >> b;

        cout << work(a, b) << endl;
    }
    return 0;
}