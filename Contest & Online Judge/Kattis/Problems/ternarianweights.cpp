#include <bits/stdc++.h>
using namespace std;

map<long long,int> comp;
vector<pair<long long,int> > v;

void rec(int tipe,int pos,int lmt,long long sum,long long mul,int mask,int mulmask){
    if(pos == lmt){
        if(tipe == 0) comp[sum] = mask;
        else v.push_back({sum,mask});
    }
    else{
        rec(tipe,pos + 1,lmt,sum,mul * 3,mask,mulmask * 3);
        rec(tipe,pos + 1,lmt,sum - mul,mul * 3,mask + mulmask,mulmask * 3);
        rec(tipe,pos + 1,lmt,sum + mul,mul * 3,mask + 2 * mulmask,mulmask * 3);
    }
}

int main(){
    rec(0,0,10,0,1,0,1);
    long long temp = 1;
    for(int i = 0 ; i < 10 ; i++)
        temp *= 3;
    rec(1,10,20,0,temp,0,1);
    sort(v.begin(),v.end());
    int tc;
    scanf("%d",&tc);
    for(int t = 0 ; t < tc ; t++){
        if(t) puts("");
        long long n;
        scanf("%lld",&n);
        int mask,mask2;
        for(int i = 0 ; i < v.size() ; i++)
            if(comp.count(n - v[i].first)){
                mask = comp[n - v[i].first];
                mask2 = v[i].second;
                break;
            }
        vector<long long> ans,ans2;
        temp = 1;
        for(int i = 0 ; i < 10 ; i++){
            if(mask % 3 == 1) ans.push_back(temp);
            else if(mask % 3 == 2) ans2.push_back(temp);
            mask /= 3;
            temp *= 3;
        }   
        for(int i = 0 ; i < 10 ; i++){
            if(mask2 % 3 == 1) ans.push_back(temp);
            else if(mask2 % 3 == 2) ans2.push_back(temp);
            mask2 /= 3;
            temp *= 3;
        }
        sort(ans.begin(),ans.end());
        sort(ans2.begin(),ans2.end());
        printf("left pan:");
        for(int i = (int)ans.size() - 1 ; i >= 0 ; i--)
            printf(" %lld",ans[i]);
        printf("\n");   
        printf("right pan:");
        for(int i = (int)ans2.size() - 1 ; i >= 0 ; i--)
            printf(" %lld",ans2[i]);            
        printf("\n");   
    }   
    return 0;
}

