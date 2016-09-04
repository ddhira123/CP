#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int cnt[N];
int SA[N],tmpS[N];
int RA[N],tmpR[N];
int phi[N],PLCP[N],LCP[N];
int inve[N];

int bestTree[4 * N];
int LCPTree[4 * N];
int bestIndex[N];
int occ[N];

char s[N];
int len;

// start of suffix array routine

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

    for(int i = 0 ; i < len ; i++)
    		inve[SA[i]] = i;
}

void Build_LCP(){
    phi[SA[0]] = -1;
    for(int i = 1 ; i < len ; i++)
        phi[SA[i]] = SA[i - 1];
    for(int i = 0, l = 0 ; i < len ; i++){
        if(phi[i] == -1)
            PLCP[i] = 0;
        else{
            while(s[i + l] == s[phi[i] + l]) l++;
            PLCP[i] = l;
            l = max(0,l - 1);
        }    
    }
    for(int i = 0 ; i < len ; i++)
        LCP[i] = PLCP[SA[i]];
}

void Print(){
    for(int i = 0 ; i < len ; i++){
        printf("Index %d\n",i);
        printf("%d %s\n",SA[i],s + SA[i]);
        printf("LCP %d\n",LCP[i]);
        puts("");
    }
}

// end of suffix array routine

// start of LCP RMQ routine

void buildLCPTree(int id,int l,int r) {
	if(l == r) {
		LCPTree[id] = LCP[l];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		buildLCPTree(chld,l,m);
		buildLCPTree(chld + 1,m + 1,r);
		LCPTree[id] = min(LCPTree[chld],LCPTree[chld + 1]);
	}
}

int queryLCPTree(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return LCPTree[id];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		int ret = (int)1e9;

		if(x <= m) ret = min(ret,queryLCPTree(chld,l,m,x,y));
		if(y > m)  ret = min(ret,queryLCPTree(chld + 1,m + 1,r,x,y));

		return ret;
	}
}

// end of LCP RMQ routine

// start of Best Tree routine

void propagate(int id) {
	if(bestTree[id] == -1) return;

	int chld = id << 1;
	for(int i = 0 ; i < 2 ; i++)
		bestTree[chld + i] = bestTree[id];

	bestTree[id] = -1;
}

void update(int id,int l,int r,int x,int y,int val) {
	if(x <= l && r <= y) {
		bestTree[id] = val;
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		propagate(id);
		if(x <= m)	update(chld,l,m,x,y,val);
		if(y > m)	update(chld + 1,m + 1,r,x,y,val);
	}
}

void dropTheTable(int id,int l,int r) {
	if(l == r) {
		bestIndex[l] = bestTree[id];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		propagate(id);
		dropTheTable(chld,l,m);
		dropTheTable(chld + 1,m + 1,r);
	}
}

// end of Best Tree routine

// solver

void read() {
	scanf("%d",&len);
	scanf("%s",s);
}

void makeSuffixArray() {
    s[len++] = '$';
    s[len] = '\0';
    
    Build_Suffix_Array();
    Build_LCP();
    buildLCPTree(1,1,len - 1);
}

#define length(x) len-x-1

void solve() {
	memset(bestTree,-1,sizeof bestTree);
	update(1,1,len - 1,1,len - 1,0);
	int last = 0;
	//Print();

	for(int i = 1 ; i + 1 < len ; i++) {
		int posLast = inve[last];
		int posNow = inve[i];

		int mins = min(posNow,posLast) + 1;
		int maks = max(posNow,posLast);

		//printf("last %d posLast %d i %d posNow %d\n",last,posLast,i,posNow);

		int lcp = queryLCPTree(1,1,len - 1,mins,maks);
		//printf("lcp %d\n",lcp);

		if(length(i) == lcp || s[i + lcp] > s[last + lcp]) { // lebih payah
			// do nothing
			//puts("loser");
		}
		else {
			//printf("update %d-%d to %d\n",lcp + 1,length(i),i);
			update(1,1,len - 1,lcp + 1,length(i),i);
			last = i;
		}
	}

	dropTheTable(1,1,len - 1);

	for(int i = 1 ; i + 1 <= len ; i++) {
		occ[bestIndex[i]]++;

		//printf("length %d bestIndex %d\n",i,bestIndex[i]);
	}

	long long ans = 0;
	long long prefixSum = 0;
	long long prefixTotal = 0;

	for(long long i = 0 ; i + 1 < len ; i++) {
		ans += (prefixTotal * i - prefixSum) * occ[i];
		prefixSum += i * occ[i];
		prefixTotal += occ[i];
	}

	ans *= 2ll;
	
	printf("%lld\n",ans);	
}

int main(){
    read();
    makeSuffixArray();
    solve();
    //puts("ganteng");
    return 0;
}
