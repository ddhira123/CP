#include <bits/stdc++.h>
using namespace std;

const int BASE = 3600;
const int BASE2 = BASE * BASE / 10;
double PI = acos(-1.0);

bool vis[BASE2 + 5];

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        double r;
        int n,deg,mins,secs;
        cin >> r >> n >> deg >> mins >> secs;
        deg = 3600 * deg + 60 * mins + secs; 
        int tdeg = deg; 
        //printf("%d\n",deg);
        int now = 0;
        n--;
        for(int i = 0 ; i < n + 1; i++)
            if(vis[now]){
                break;
            }
            else{
                vis[now] = 1;
                //printf("%d\n",now);
                now += deg;
                if(now >= BASE2) now -= BASE2;
            }
        int maks = 0;
        int sum = 0;
        for(int i = 0 ; i < BASE2 ; i++){
            if(vis[i]){
                //printf("%d\n",i);
                sum = 0;
            }
            else sum++;
            maks = max(maks,sum);
        }   
        //printf("%d\n",maks);
        maks++;
        deg = maks / 3600;
        maks %= 3600;
        mins = maks / 60;
        maks %= 60;
        secs = maks;
        double angle = deg + (double)mins / 60.0 + (double)secs / 3600.0;
        //printf("%.7lf %.7lf\n",angle,PI);
        double area = r * r * PI * angle / 360.0;
        printf("%.7lf\n",area); 
        deg = tdeg;
        now = 0;
        //memset(vis,0,sizeof vis);
        for(int i = 0 ; i < n + 1; i++)
            if(!vis[now]){
                break;
            }
            else{
                vis[now] = 0;
                now += deg;
                if(now >= BASE2) now -= BASE2;
            }
    }
    return 0;
}

