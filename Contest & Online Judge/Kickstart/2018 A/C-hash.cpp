#include <bits/stdc++.h>
using namespace std;

const int N = 20005;
const int MX = 1e6 + 5;
const int MOD = 1e9 + 7;
const int BASE = 1e5 + 3;

char asu[MX];

string read_string() {
    scanf("%s", asu);

    return (string)asu;
}

long long pwr[30];

int n;
string arr[N];
int idx[N];

int len;
string str;
int a, b, c, d;
string s1, s2;

int calc_match(int l, int r) {
    int cur_len = arr[idx[l]].length();
    if(cur_len > len) {
        return 0;
    }

    map<int, int> exists[26][26];

    for(int i = l ; i <= r ; i++) {
        int id = idx[i];

        int hsh = 0;
        for(char x : arr[id]) {
            hsh = (hsh + pwr[x - 'a']) % MOD;
        }

        int f = arr[id][0] - 'a';
        int b = arr[id][cur_len-1] - 'a';

        exists[f][b][hsh]++;
    }

    int ret = 0;

    int hsh = 0;
    for(int i = 0 ; i < len ; i++) {
        hsh = (hsh + pwr[str[i] - 'a']) % MOD;

        if(i >= cur_len) {
            hsh = (hsh - pwr[str[i - cur_len] - 'a']) % MOD;
            hsh = (hsh + MOD) % MOD;
        }

        if(i >= cur_len-1) {
            int a = str[i - cur_len + 1] - 'a';
            int b = str[i] - 'a';

            if(exists[a][b].count(hsh)) {
                ret += exists[a][b][hsh];
                exists[a][b][hsh] = 0;
            }
        }
    }

    return ret;
} 

int get_next(int i, int j) {
    int x = 1ll * a * j %d;
    x = (x + 1ll * b * i) % d;
    x = (x + c) % d;

    return x;
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        arr[i] = read_string();
    }

    s1 = read_string();
    s2 = read_string();

    scanf("%d %d %d %d %d", &len, &a, &b, &c, &d);

    // cerr << n << " " << s1 << " " << s2 << " " << len << " " << a << " " << b << " " << c << " " << d << endl;
    // len = 1e6;
}

void prepare() {
    for(int i = 0 ; i < n ; i++) {
        idx[i] = i;
    }

    sort(idx, idx + n, [&](int a, int b) {
        return arr[a].length() < arr[b].length();
    });

    str = s1;
    str += s2;

    int x1 = s1[0];
    int x2 = s2[0];

    for(int i = 2 ; i < len ; i++) {
        int x3 = get_next(x1, x2);
        x1 = x2;
        x2 = x3;

        str += (char)('a' + x3 % 26);
    }

    // cout << str << endl;
}

int work() {
    int ret = 0;

    for(int i = 0 ; i < n ; ) {
        int j = i;

        while(j < n && arr[idx[i]].length() == arr[idx[j]].length()) {
            j++;
            // cerr << j << endl;
        }

        // cerr << i << " " << j << endl;

        ret += calc_match(i, j-1);
        i = j;
    }
    return ret;
}

int main() {
    pwr[0] = 1;
    for(int i = 1 ; i < 30 ; i++) {
        pwr[i] = (pwr[i-1] * BASE) % MOD;
    }

    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        cerr << tc << endl;
        read();
        prepare();

        printf("Case #%d: %d\n", tc, work());
    }
    return 0;
}