#include<bits/stdc++.h>
using namespace std;

#define ll long long 
#define ii pair<ll, ll>

ll n, c[5005], ans = 1e18; 
vector<ii> largeOn, sorted;
string str1, str2;
bool state[5005] = {0};

ll solve(ll k){
    memset(state, 0, sizeof state);
    ll curCost = 0, ansa = 0;
    for(ll i = 0; i < largeOn.size(); i++){
        curCost += - largeOn[i].first;
        state[largeOn[i].second] = 1;
    }
    for(ll i = 0; i < k; i++){
        ll tmp = largeOn[i].second;
        curCost += largeOn[i].first;
        ansa += curCost;
        state[tmp] = 0;
    }

    for(ll i = n-1; i >= 0; i--){
        int idx = sorted[i].second;
        if(state[idx] != 1 || str2[idx] != '0') continue;

        curCost -= sorted[i].first;
        ansa += curCost;
        state[idx] = 0;
    }

    for(ll i = 0; i < n; i++){
        ll tmp = sorted[i].second;
        if(state[tmp] != 0 || str2[tmp] != '1') continue;

        curCost += sorted[i].first;
        ansa += curCost;
        state[tmp] = 1;
    }
    return ansa;
}

int main(){
    scanf("%lld", &n);
    for(ll i = 0; i < n; i++){
        scanf("%lld", &c[i]);
    }
    cin >> str1;
    cin >> str2;

    ll tmpAns = 0;
    for(ll i = 0; i < n; i++){
        if(str1[i] == '1'){
            largeOn.push_back(ii(-c[i], i));
            tmpAns += c[i];
        }
        sorted.push_back(ii(c[i], i));
    }
    sort(sorted.begin(), sorted.end());
    sort(largeOn.begin(), largeOn.end());

    for(ll i = 0; i <= largeOn.size(); i++){
        ans = min(ans, solve(i));
    }
    printf("%lld\n", ans);
}