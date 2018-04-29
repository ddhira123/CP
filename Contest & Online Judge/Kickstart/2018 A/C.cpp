#include <bits/stdc++.h>
using namespace std;

const int N = 20005;
const int MX = 1e6 + 5;

string read_string() {
    static char s[MX];
    scanf("%s", s);

    return (string)s;
}

int n;
string arr[N];
int idx[N];

int len;
string str;
int a, b, c, d;
string s1, s2;

int calc_match(int l, int r) {
    int cur_len = arr[idx[l]].length();

    set<pair<pair<char, char>, vector<int>>> exists;
    vector<int> cnt(26, 0);

    for(int i = 0 ; i < cur_len ; i++) {
        cnt[str[i]-'a']++;
    }

    exists.insert({{str[0], str[cur_len-1]}, cnt});

    // cout << str[0] << " " << str[cur_len-1] << endl;
    // for(int x : cnt) {
    //     cout << x << " ";
    // }
    // cout << "\n\n";

    for(int i = cur_len ; i < len ; i++) {
        cnt[str[i] - 'a']++;
        cnt[str[i - cur_len] - 'a']--;

        exists.insert({{str[i - cur_len + 1], str[i]}, cnt});
    }

    int ret = 0;
    for(int i = l ; i <= r ; i++) {
        int id = idx[i];

        for(int &x : cnt) {
            x = 0;
        }

        for(char x : arr[id]) {
            cnt[x - 'a']++;
        }

        pair<pair<char, char>, vector<int>> cur;
        cur.first = {arr[id][0], arr[id][cur_len-1]};
        cur.second = cnt;

        // printf("id %d\n", id);
        // printf("f %c l %c\n", cur.first.first, cur.first.second);
        // for(int j = 0 ; j < 26 ; j++) {
        //     printf("%d ", cnt[j]);
        // }
        // puts("======\n");

        if(exists.count(cur)) {
            ret++;
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
        }

        ret += calc_match(i, j-1);
        i = j;
    }
    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        cerr << tc << endl;
        read();
        prepare();

        printf("Case #%d: %d\n", tc, work());
    }
    return 0;
}