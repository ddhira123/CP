#include <bits/stdc++.h>
using namespace std;

long long with_add(long long x) {
    long long ori = x;
    vector<int> v;
    
    while(x > 0) {
        v.push_back(x % 10);
        x /= 10;
    }

    for(int i = 0 ; i < v.size() ; i++) {
        if(v[i] % 2 == 1) {
            v[i]++;
            for(int j = 0 ; j < i ; j++) {
                v[j] = 0;
            }

            if(v[i] == 10) {
                v[i] = 0;
                for(int j = i+1 ; j < v.size() ; j++) {
                    v[j]++;

                    if(v[j] == 10) {
                        v[j] = 0;
                    } else {
                        break;
                    }
                }

                if(v.back() == 0) {
                    v.push_back(1);
                }
            }
        }
    }

    long long res = 0;
    for(int i = (int)v.size()-1 ; i >= 0 ; i--) {
        res = 10 * res + v[i];
    }

    return res - ori;
}

long long with_minus(long long x) {
    long long ori = x;
    vector<int> v;
    
    while(x > 0) {
        v.push_back(x % 10);
        x /= 10;
    }

    for(int i = v.size()-1 ; i >= 0 ; i--) {
        if(v[i] % 2 == 1) {
            v[i]--;
            for(int j = i-1 ; j >= 0 ; j--) {
                v[j] = 8;
            }
            break;
        }
    }   

    long long res = 0;
    for(int i = (int)v.size()-1 ; i >= 0 ; i--) {
        res = 10 * res + v[i];
    }

    return ori - res; 
}

long long work(long long x) {
    long long a = with_add(x);
    long long b = with_minus(x);

    return min(a, b);
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        long long x; cin >> x;

        printf("Case #%d: %lld\n", tc, work(x)); 
    }
    return 0;
}