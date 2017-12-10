#include <bits/stdc++.h>
using namespace std;

const int N = 22;

int a[N];
int b[N];
int n;

void read() {
    // srand(time(NULL))
    cin >> n;
    for(int i = 0 ; i < n ; i++) {
        cin >> a[i];
        // a[i] = rand() % (1e9+1);
        b[i] = a[i];
    }
}

vector<int> v, v2;
unordered_map<long long, int> m1;

bool check() {
    v.clear();
    v2.clear();

    for(int i = 0 ; i < n ; i++) {
        if(i & 1) {
            v.push_back(a[i] - b[i]);
        } else {
            v2.push_back(b[i] - a[i]);
        }
    }

    unordered_map<long long, int> m1;
    int tot = 0;
    for(int i = 1 ; i < (1 << v.size()) ; i++) {
        long long cnt = 0;
        for(int j = 0 ; j < v.size() ; j++) {
            if(i & (1 << j))
                cnt += v[j];
        }

        if(cnt == 0) return false;
        m1[cnt]++;
    }

    for(int i = 1 ; i < (1 << v2.size()) && tot <= 1; i++) {
        long long cnt = 0;
        for(int j = 0 ; j < v2.size() ; j++) {
            if(i & (1 << j))
                cnt += v2[j];
        }

        if(cnt == 0) return false;
        tot += m1.count(cnt) ? m1[cnt] : 0;
    }

    return tot == 1;
}

void solve() {
    if(n == 1) {
        cout << a[0] << endl;
        return;
    }

    int MAGIC = 2e9;
    int trial = MAGIC / (1 << ((n+1)/2));
    // trial = 250000;

    // cerr << trial << endl;

    srand(1337);
    for(int i = 0 ; i < trial ; i++) {
        random_shuffle(b, b + n);

        if(check()) {
            for(int j = 0 ; j < n ; j++)
                cout << b[j] << " ";
            cout << endl;
            return;
        }
    }

    cout << "-1\n";
}

int main() {
    read();
    solve();
    return 0;
}