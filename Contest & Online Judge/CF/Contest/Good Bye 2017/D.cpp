#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mod_pow(int base, int po) {
    int ret = 1;
    while(po) {
        if(po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }
    return ret;
}

int k, pa, pb;

struct Value {
    int val;
    int a_cnt;
    int b_cnt;
    int ab_cnt;

    Value operator +(Value other) const {
        Value ret = (Value){0, 0, 0, 0};
        int this_val = val;
        int other_val = other.val;

        //cout << "a " << a_cnt << " " << other.a_cnt << endl;

        if(a_cnt > other.a_cnt) {
            other_val = 1ll * other_val * mod_pow(pa, a_cnt - other.a_cnt) % MOD;
            ret.a_cnt = a_cnt;
        } else {
            this_val = 1ll * this_val * mod_pow(pa, other.a_cnt - a_cnt) % MOD;
            ret.a_cnt = other.a_cnt;
        }

        //cout << "b " << b_cnt << " " << other.b_cnt << endl;

        if(b_cnt > other.b_cnt) {
            other_val = 1ll * other_val * mod_pow(pb, b_cnt - other.b_cnt) % MOD;
            ret.b_cnt = b_cnt;
        } else {
            this_val = 1ll * this_val * mod_pow(pb, other.b_cnt - b_cnt) % MOD;
            ret.b_cnt = other.b_cnt;
        }

        if(ab_cnt > other.ab_cnt) {
            other_val = 1ll * other_val * mod_pow(pa + pb, ab_cnt - other.ab_cnt) % MOD;
            ret.ab_cnt = ab_cnt;
        } else {
            this_val = 1ll * this_val * mod_pow(pa + pb, other.ab_cnt - ab_cnt) % MOD;
            ret.ab_cnt = other.ab_cnt;
        }

        ret.val = (this_val + other_val) % MOD;

        return ret;
    }

    Value operator *(Value other) const {
        Value ret = {val, a_cnt, b_cnt, ab_cnt};

        ret.val = 1ll * val * other.val % MOD;
        ret.a_cnt = a_cnt + other.a_cnt;
        ret.b_cnt = b_cnt + other.b_cnt;
        ret.ab_cnt = ab_cnt + other.ab_cnt;

        return ret;
    }
};

Value dp[1005][1005];
bool vis[1005][1005];

Value mul_a, mul_b;

Value solve(int a, int sisa) {
    if(a >= sisa) {
        int total = k + (a - sisa);

        int tmp = 1ll * (pa + pb) * (total-1) % MOD;
        Value one = (Value){tmp, 0, 1, 0};

        tmp = 1ll * (pa + pb) * (pa + pb) % MOD;
        Value two = (Value){tmp, 0, 2, 0};

        Value ret = one + two;
        ret = ret * mul_b;
        //cout << ret.val << " " << ret.a_cnt << " " << ret.b_cnt << " " << ret.ab_cnt << endl;

        return ret;
    }

    if(vis[a][sisa]) {
        return dp[a][sisa];
    }

    vis[a][sisa] = true;

    dp[a][sisa] = mul_a * solve(a+1, sisa);
    dp[a][sisa] = dp[a][sisa] + mul_b * solve(a, sisa-a);

    return dp[a][sisa];
}

int work() {
    mul_a = (Value){pa, 0, 0, 1};
    mul_b = (Value){pb, 0, 0, 1};

    Value inf_b = (Value){pa+pb, 1, 0, 0};
    Value ret = solve(1, k);

    //cout << ret.val << " " << ret.a_cnt << " " << ret.b_cnt << " " << ret.ab_cnt << endl;

    ret = ret * inf_b;
    ret = ret * mul_a;

    int ans = ret.val;

    int inve_a = mod_pow(pa, MOD-2);
    int inve_b = mod_pow(pb, MOD-2);
    int inve_ab = mod_pow(pa + pb, MOD-2);

    ans = 1ll * ans * mod_pow(inve_a, ret.a_cnt) % MOD;
    ans = 1ll * ans * mod_pow(inve_b, ret.b_cnt) % MOD;
    ans = 1ll * ans * mod_pow(inve_ab, ret.ab_cnt) % MOD;

    //cout << ret.val << " " << ret.a_cnt << " " << ret.b_cnt << " " << ret.ab_cnt << endl;

    return ans;
}

int main() {
    cin >> k >> pa >> pb;
    cout << work() << endl;
    return 0;
}

