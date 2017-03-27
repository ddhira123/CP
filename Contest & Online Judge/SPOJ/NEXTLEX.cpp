#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int cnt[N];
int SA[N],tmpS[N];
int RA[N],tmpR[N];

char s[N];
int len;

void Radix_Sort(int k){
    int maxx = max(len,300);
    for(int i = 0 ; i < maxx ; i++)
        cnt[i] = 0;
    for(int i = 0 ; i  < len ; i++)
        cnt[i + k < len ? RA[i + k] : 0]++;
    
    int tot = 0;
    for(int i = 0 ; i < maxx ; i++){
        int tmp = cnt[i];
        cnt[i] = tot;
        tot += tmp;
    } 
    
    for(int i = 0 ; i < len ; i++)
        tmpS[cnt[SA[i] + k < len ? RA[SA[i] + k] : 0]++] = SA[i];
    for(int i = 0 ; i < len ; i++)
        SA[i] = tmpS[i];           
}

void Build_Suffix_Array(){
    for(int i = 0 ; i < len ; i++){
        SA[i] = i;
        RA[i] = s[i];
    }
    for(int lg = 1 ; lg < len ; lg <<= 1){
        Radix_Sort(lg);
        Radix_Sort(0);
        int tot = 0;
        tmpR[SA[0]] = 0;
        for(int i = 1 ; i < len ; i++)
            tmpR[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && SA[i] + lg < len && SA[i - 1] + lg < len 
                            && RA[SA[i] + lg] == RA[SA[i - 1] + lg]) ? tot : ++tot;
        
        for(int i = 0 ; i < len ; i++)
            RA[i] = tmpR[i];
        if(RA[SA[len - 1]] == len - 1) break;                        
    }
}

void Print() {
	for(int i = 0 ; i < len ; i++) {
		printf("RANK %d : %d -> %s\n",i,SA[i],s + SA[i]);
	}
}

char qu[N];
int qLen;
int q;

bool isHigher(int st) {
	//printf("%d\n",st);
	int lmt = min(qLen,len - st - 1);
	for(int i = 0 ; i < lmt ; i++)
		if(qu[i] < s[st + i])
			return 1;
		else if(qu[i] > s[st + i])
			return 0;
	if(qLen < len - st - 1)
		return 1;
	return 0;				
}

void solve() {
	scanf("%d",&q);
	while(q--) {
		scanf("%s",qu);
		qLen = strlen(qu);
	
		if(!isHigher(SA[len - 1]))
			puts("-1");
		else {
			int lo = 1;
			int hi = len - 1;
			
			while(lo < hi) {
				int mid = (lo + hi) / 2;
				//printf("%d %d %d %d\n",lo,hi,mid,SA[mid]);
				if(isHigher(SA[mid]))
					hi = mid;
				else
					lo = mid + 1;	
			}
			//printf("%d %d\n",lo,SA[lo]);			
			int st = SA[lo];
			
			for(int i = 0 ; ; i++) {
				printf("%c",s[st + i]);
				if(i == qLen || s[st + i] > qu[i]) {
					puts("");
					break;
				}
			}
		}	
	}
}

int main(){
    scanf("%s",s);
    len = strlen(s);
    s[len++] = '$';
    s[len] = '\0';
    Build_Suffix_Array();
    //Print();
    solve();
    //puts("ganteng");
    return 0;
}