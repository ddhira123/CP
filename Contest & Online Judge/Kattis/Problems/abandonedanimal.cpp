#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

string read_string() {
    static char s[105];
    scanf("%s", s);
    return (string)s;
}

vector<string> v[N];
vector<int> items[N];

map<string, int> order;
int dp[N];

int n, k, m;

void read() {
    scanf("%d", &n);

    scanf("%d", &k);
    for(int i = 0 ; i < k ; i++) {
        int idx; 
        string str;

        scanf("%d", &idx);
        str = read_string();

        v[idx].push_back(str);
    }

    scanf("%d", &m);
    for(int i = 1 ; i <= m ; i++) {
        string str;
        str = read_string();

        order[str] = i;
    }
}

void prepare() {
    for(int i = 0 ; i < n ; i++) {
        for(string x : v[i]) {
            if(order.count(x)) {
                items[i].push_back(order[x]);
            }
        }

        sort(items[i].begin(), items[i].end());
        items[i].erase(unique(items[i].begin(), items[i].end()), items[i].end());
    }
}

string work() {
    dp[0] = 1;

    for(int i = 0 ; i < n ; i++) {
        for(int idx : items[i]) {
            dp[idx] = min(dp[idx] + dp[idx-1], 2);
        }
    }

    string ret = "impossible";
    if(dp[m] == 2) {
        ret = "ambiguous";
    } else if(dp[m] == 1) {
        ret = "unique";
    }

    return ret;
}

int main() {
    read();
    prepare();

    string ret = work();
    cout << ret << endl;
    return 0;
}