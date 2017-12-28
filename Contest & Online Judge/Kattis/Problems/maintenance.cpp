#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int LIM = 500000;
const long long MOD = (long long)(1e9) + 7;
const double EPS = 1e-13;

vector<pii> v[2];
vector<pair<double,long long> > divi[2];
map<int,int> cnt;
string s;
double tot = 0;
long long all = 1;

int modpow(long long base,int po) {
    long long res = 1;
    while(po) {
        if(po & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        po >>= 1;
    }
    return res;
}

void rec(int id,int pos,double lg,long long mul) {
    if(pos == v[id].size()) {
        //printf("%d %.9lf %d\n",id,lg,mul);
        divi[id].push_back({lg,mul});
    }
    else {
        double add = log(v[id][pos].first);
        for(int i = 0 ; i <= v[id][pos].second ; i++) {
            rec(id,pos + 1,lg,mul);
            lg += add;
            mul = ((long long)(mul) * (v[id][pos].first)) % MOD;
        }
    }
}

int main() {
    cin >> s;
    for(int i = 0 ; i < s.length() ; i += 2) {
        int val = (s[i] - '0') * 10 + s[i + 1] - '0';
        cnt[val]++;
        tot += log(val);
        all = (all * val) % MOD;
    }
    
    int mul = 1;
    for(auto it = cnt.begin() ; it != cnt.end() ; it++) {
        int val = it -> first;
        int jum = it -> second;
        int iter = 0;
        
        while(iter <= jum && mul * (iter + 1) <= LIM) {
            iter++;
        }
        mul *= iter;
        iter--;
        v[0].push_back({val,iter});
        v[1].push_back({val,jum - iter});
    }
    
    rec(0,0,0,1);
    rec(1,0,0,1);
    
    sort(divi[0].begin(),divi[0].end());
    sort(divi[1].begin(),divi[1].end());
    
    double best = 1e9;
    int ans = 0;
    
    tot /= 2.0;
    //printf("%.9lf\n",tot);
    int iter = divi[1].size() - 1;
    for(pair<double,long long> x : divi[0]) {
        while(iter > 0 && x.fi + divi[1][iter - 1].fi + EPS > tot)
            iter--;
        //printf("%d %.9lf %.9lf\n",iter,x.fi,divi[1][iter].fi);    
        if(x.fi + divi[1][iter].fi + EPS > tot && best > x.fi + divi[1][iter].fi) {
            best = x.fi + divi[1][iter].fi;
            long long temp = (x.se * divi[1][iter].se) % MOD;
            long long inve = modpow(temp,MOD - 2);
            ans = (temp + all * inve) % MOD;
            //printf("%.9lf %d %lld\n",best,x.se,all * inve);
        }   
    }   
    
    printf("%d\n",ans);     
    return 0;
}

