#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, m;
int a[N];
int b[N];

int dp[N][N][2];

int get_dist(int a, int b) {
    int diff = abs(a-b);
    return min(diff, m - diff);
}

void read() {
    cin >> m >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; i++) {
        cin >> b[i];
    }
}

int DP() {
    a[0] = 0; b[0] = m/2;
    dp[n+1][n+1][0] = dp[n+1][n+1][1] = 0;

    for(int first_person = n+1 ; first_person >= 1 ; first_person--)
        for(int second_person = n+1 ; second_person >= 1 ; second_person--) 
            for(int last_satisfied = 0 ; last_satisfied <= 1 ; last_satisfied++){
                if(first_person <= n || second_person <= n) {

                    int cur_first_pos = last_satisfied == 0 ? a[first_person-1] : (b[second_person-1] + m/2) % m;
                    int cur_second_pos = (cur_first_pos + m/2) % m;
                    int &ret = dp[first_person][second_person][last_satisfied];

                    ret = 1e9;

                    if(first_person <= n) {
                        ret = min(ret, dp[first_person+1][second_person][0] + get_dist(cur_first_pos, a[first_person]));
                    }
                    if(second_person <= n) {
                        ret = min(ret, dp[first_person][second_person+1][1] + get_dist(cur_second_pos, b[second_person]));
                    }
                }
        }

    return dp[1][1][0];
}

int main() {
    read();
    cout << DP() << endl;
    return 0;
}
