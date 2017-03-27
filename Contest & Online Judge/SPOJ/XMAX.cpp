#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL calc(vector<LL> &v){
    sort(v.rbegin(),v.rend());
    //reverse(v.begin(),v.end());
    LL pwr = 1;
    while(pwr <= v[0]) pwr <<= 1;
    pwr >>= 1;
    for(int i = 0 ; pwr >= 1 ; pwr >>= 1){
        int j = i;
        while(j < v.size() && (v[j] & pwr) == 0) j++;    
        if(j >= v.size()) continue;
        swap(v[j],v[i]);
        for(int it = 0 ; it < v.size() ; it++)
            if(it != i && (v[it] & pwr) > 0)
                v[it] ^= v[i];
        i++;        
    }
    LL res = 0;
    for(int i = 0 ; i < v.size() ; i++)
        res ^= v[i];
    return res;    
}

int main(){
    ios_base::sync_with_stdio(0);
    int n; vector<LL> v;
    cin >> n;
    while(n--){
        LL x;
        cin >> x;
        v.push_back(x);
    }
    printf("%lld\n",calc(v));
}