#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair

const int K = 755;

typedef pair<int,int> pii;

int ans[K];
int arr[K];
int k;

int main(){
    while(scanf("%d",&k) == 1){
        for(int i = 0 ; i < k ; i++)
            ans[i] = (int)1e9;
        ans[0] = 0;    
        for(int i = 0 ; i < k ; i++){
            for(int j = 0 ; j < k ; j++)
                scanf("%d",&arr[j]);
            sort(arr,arr + k);
            arr[k] = (int)1e9;
            
            priority_queue<pii,vector<pii>,greater<pii> > pq;
            for(int it = 0 ; it < k ; it++)
                pq.push(mp(ans[it] + arr[0],0));
            
            for(int it = 0 ; it < k ; it++){
                pii now = pq.top();
                pq.pop();
                ans[it] = now.fi;
                //printf("i %d it %d ans[] %d\n",i,it,ans[it]);
                pq.push(mp(now.fi - arr[now.se] + arr[now.se + 1],now.se + 1));
            }        
        }
        for(int i = 0 ; i < k ; i++)
            printf("%d%c",ans[i],i == k - 1 ? '\n' : ' ');    
    }
    return 0;
}
