#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int MAGIC = 400;
const int N = 100005;

int arr[N];
int sum[MAGIC][MAGIC];
int n,m;

void precompute() {
	//puts("start");
	for(int i = 0 ; i < MAGIC ; i++)
		for(int j = 0 ; j < i ; j++) {
			for(int k = j ; k < n ; k += i)
				sum[i][j] += arr[k];
		}
}

int solve(int p,int q) {
	//printf("haha %d %d\n",p,q);
	if(p < MAGIC)
		return sum[p][q];
	int tot = 0;
	for(int i = q ; i < n ; i += p)
		tot += arr[i];
	return tot;
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++)
		scanf("%d",arr + i);
	precompute();
	for(int tc = 1 ; tc <= m ; tc++) {
		int p, q;
		scanf("%d %d",&q,&p);
		printf("%d\n",solve(p,q));
	}
	return 0;
}