#include <bits/stdc++.h>
using namespace std;

const int BASE = 33;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

int mod_pow(int base, int po) {
    int ret = 1;
    while(po) {
        if(po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }
    return ret;
}

int get_inverse(int x) {
    return mod_pow(x, MOD-2);
}

int convert(char x) {
    return x - 'a' + 1;
}

int pwr[N];
int inve[N];
int prefix[N];
string str;
int len;

int get_hash(int l, int r) {
    int ret = prefix[r];
    if(l) {
        ret = (ret - prefix[l-1] + MOD) % MOD;
    }

    ret = 1ll * ret * inve[l] % MOD;

    return ret;
}

void precompute() {
    pwr[0] = inve[0] = 1;
    pwr[1] = BASE; inve[1] = get_inverse(BASE);

    for(int i = 2 ; i < N ; i++) {
        pwr[i] = 1ll * pwr[i-1] * pwr[1] % MOD;
        inve[i] = 1ll * inve[i-1] * inve[1] % MOD;
    }
}

void prepare() {
    for(int i = 0 ; i < len ; i++) {
        prefix[i] = 1ll * convert(str[i]) * pwr[i] % MOD;
        if(i) {
            prefix[i] = (prefix[i] + prefix[i-1]) % MOD;
        }
    }
}

bool check(int l) {
    for(int i = 0 ; i < len ; i += l) {
        int sisa = min(l, len - i);

        if(get_hash(0, sisa-1) != get_hash(i, i + sisa - 1)) {
            return false;
        }
    }

    return true;
}

int work() {
    for(int i = 1 ; i <= len ; i++) {
        if(check(i)) {
            return i;
        }
    }
    return -1;
}

int main() {
    precompute();

    cin >> len;
    cin >> str;
    prepare();
    cout << work() << endl;
    return 0;
}