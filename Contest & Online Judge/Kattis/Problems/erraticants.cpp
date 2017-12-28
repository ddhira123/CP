#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};

set<pair<pii,int> > seen;
set<pii> proc;

int main(){
    int tc,n;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        seen.clear();
        pii now = {0,0};
        for(int i = 0 ; i < n ; i++){
            char c[5];
            scanf("%s",c);
            int arah = -1;
            if(c[0] == 'E') {arah = 3;}
            else if(c[0] == 'W') {arah = 1;}
            else if(c[0] == 'N') {arah = 0;}
            else {arah = 2;}            
            seen.insert({now,arah});
            //printf("%d %d\n",now.fi,now.se);
            if(c[0] == 'E') {arah = 3,now.se++;}
            else if(c[0] == 'W') {arah = 1,now.se--;}
            else if(c[0] == 'N') {arah = 0,now.fi--;}
            else {arah = 2,now.fi++;}
            seen.insert({now,(arah + 2) % 4});
        }
        //for(auto it : seen)
        //  printf("%d %d %d\n",it.fi.fi,it.fi.se,it.se);
        pii tgt = now;
        queue<pair<pii,int> > q;
        q.push({{0,0},0});
        proc.clear();
        proc.insert({0,0});
        while(!q.empty()){
            now = q.front().fi;
            int step = q.front().se;
            //printf("aa %d %d %d\n",now.fi,now.se,step);
            q.pop();
            if(now == tgt){
                printf("%d\n",step);
                break;
            }
            for(int i = 0 ; i < 4 ; i++){
                pii nxt = now;
                nxt.fi += dr[i];
                nxt.se += dc[i];
                if(seen.count({now,i}) == 1 && proc.count(nxt) == 0){
                    proc.insert(nxt);
                    q.push({nxt,step + 1});
                }
            }
        }
    }
    return 0;
}


