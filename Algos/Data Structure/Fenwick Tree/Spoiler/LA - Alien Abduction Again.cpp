#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXX = 1000000;
const int MOD = 1e9 + 7;

void add(int &x,int y){
    x+=y;
    if(x >= MOD) x-=MOD;
    if(x < 0)    x+=MOD;
}

int BIT[5][MAXX+5];

void update(int id,int x,int getVal){
    x++;
    for(; x <= MAXX ; x+= x&-x)
        add(BIT[id][x],getVal);
}

LL getVal(int pwr,LL x){
    LL ans,ans2,ans3;
    if(pwr == 0)
        ans = x+1;
    else if(pwr == 1){
        ans = x;
        ans2 = x+1;

        if(ans%2 == 0) ans /= 2;
        else ans2 /= 2;

        ans = (ans*ans2)%MOD;
    } 
    else if(pwr == 2){
        ans = x;
        ans2 = x+1;
        ans3 = x*2LL + 1;

        if(ans%2 == 0) ans /= 2;
        else if(ans2%2 == 0) ans2 /= 2;
        else ans3 /= 2;

        if(ans%3 == 0) ans /= 3;
        else if(ans2%3 == 0) ans2 /= 3;
        else ans3 /= 3;  

        ans = (ans * ans2) % MOD;
        ans = (ans * ans3) % MOD;
    }
    else{
        ans2 = getVal(1,x);
        ans = (ans2 * ans2)%MOD;
    }
    return ans;
}

LL query(int idx){
    int subs=0;
    int tot[4] = {0,0,0,0};

    for(int i = idx+1 ; i ; i-= i&-i){
        for(int j=0;j<4;j++){
            add(tot[j],BIT[j][i]);
        }
        add(subs,BIT[4][i]);
    }

    LL ret = -subs;
    for(int i = 0 ; i < 4 ; i++)
        ret = (ret + (LL)tot[i] * getVal(i,idx)) % MOD;
    if (ret < 0) ret += MOD; 
    return ret; 
}

void updateWorker(LL st,LL en,LL a,LL b,LL c,LL d){
    int tmp = 0,tmp2 = 0; // tmp : dari a, tmp2 : dari b+1
    LL lol;

    update(0,st,d);
    update(0,en+1,-d);

    update(1,st,c);
    update(1,en+1,-c);

    update(2,st,b);
    update(2,en+1,-b);

    update(3,st,a);
    update(3,en+1,-a);

    lol = (getVal(0,st-1) * d)%MOD;
    add(tmp,lol);
    lol = (getVal(1,st-1) * c)%MOD;
    add(tmp,lol); 
    lol = (getVal(2,st-1) * b)%MOD;
    add(tmp,lol);
    lol = (getVal(3,st-1) * a)%MOD;
    add(tmp,lol);
    update(4,st,tmp);

    lol = (getVal(0,en) * d)%MOD;
    add(tmp2,lol);
    lol = (getVal(1,en) * c)%MOD;
    add(tmp2,lol); 
    lol = (getVal(2,en) * b)%MOD;
    add(tmp2,lol);
    lol = (getVal(3,en) * a)%MOD;
    add(tmp2,lol);
    update(4,en+1,-tmp2); 
}

LL queryWorker(LL st,LL en,LL a,LL b,LL c,LL d){
    LL ans = query(en) - query(st-1);

    while(ans >= MOD) ans -= MOD;
    while(ans < 0) ans += MOD;

    LL lol = MAXX;
    LL tmp = (ans*st)%lol;
    LL tmp2 = (ans*en)%lol;

    if(tmp > tmp2) swap(tmp,tmp2);
    updateWorker(tmp,tmp2,a,b,c,d);
    return ans;
}

int main(){
    int t;
    scanf("%d",&t);

    for(int tc = 1; tc <= t; tc++){
        printf("Case #%d:\n",tc);
        memset(BIT,0,sizeof BIT);

        int q;
        scanf("%d",&q);
        while(q--){
            char s[5];
            LL a,b,c,d,st,en;

            scanf("%s %lld %lld %lld %lld %lld %lld",s,&st,&en,&a,&b,&c,&d);
            while(a >= MOD) a-= MOD; while(a < 0) a+= MOD;
            while(b >= MOD) b-= MOD; while(b < 0) b+= MOD;   
            while(c >= MOD) c-= MOD; while(c < 0) c+= MOD;
            while(d >= MOD) d-= MOD; while(d < 0) d+= MOD;

            if(s[0] == 'p')
                updateWorker(st,en,a,b,c,d);
            else
                printf("%lld\n",queryWorker(st,en,a,b,c,d));
        }
    }
    return 0;
}

