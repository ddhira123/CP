#include <bits/stdc++.h>
using namespace std;

const int N = 20;

int nxt[1 << N];
int used[1 << N];
int cut;
int n,k;

void print(int x) {
	for(int i = n - 1 ; i >= 0 ; i--)
		printf("%d",min(1,x & (1 << i)));	
}

void greedyMake() {
	int last = 0;
	cut = (1 << n) - 1;
	for(int i = 0 ; i < (1 << n) ; i++) {
		int inter = last << 1;
		inter &= cut;
		int nex = -1;
		for(int j = 1 ; j >= 0 && nex == -1 ; j--)
			if(!used[inter + j])
				nex = inter + j;
		assert(nex != -1);
		used[nex] = 1;
		nxt[last] = nex;
		last = nex;		
	}
}

void solve(int st) {
	printf("%d\n",(1 << n) + n - 1);
	print(st);
	for(int i = 1 ; i < (1 << n) ; i++) {
		st = nxt[st];
		printf("%d",(int)(st & 1));
	}
	puts("");
}

int main() {
	scanf("%d %d",&n,&k);
	greedyMake();
	int st = 0;
	if(k > 0) {
		char s[N + 5];
		scanf("%s",s);
		for(int i = 0 ; i < k ; i++) {
			st <<= 1;
			st += (int)(s[i] - '0');
		}
	}
	st <<= (n - k);
	solve(st);
	return 0;
}