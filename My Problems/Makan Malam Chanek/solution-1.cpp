#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, m;
vector<int> a, b;

void read() {
    cin >> m >> n;
    a.resize(n+1);
    b.resize(n+1);

    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; i++) {
        cin >> b[i];
    }
}

int rec(int first_person, int second_person, int cur_first, int cur_second, int sisa) {
    if(sisa == -1) return 1e9;

    if(first_person == n+1 && second_person == n+1)
        return 0;
    if(first_person <= n && cur_first == a[first_person])
        return rec(first_person+1, second_person, cur_first, cur_second, sisa);
    if(second_person <= n && cur_second == b[second_person])
        return rec(first_person, second_person+1, cur_first, cur_second, sisa);

    return 1 + min(rec(first_person, second_person, (cur_first+1) % m, (cur_second+1) % m, sisa-1),
                   rec(first_person, second_person, (cur_first+m-1) % m, (cur_second+m-1) % m, sisa-1));
}

int main() {
    read();
    int ret = rec(1, 1, 0, m/2, 16);

    cout << ret << endl;
    return 0;
}
