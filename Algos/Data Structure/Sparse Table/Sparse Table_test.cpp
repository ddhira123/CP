// SPOJ - RMQSQ
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 20;

int sparseTable[LOG][N];
int n,q;
int arr[N];

void buildSparseTable() {
	for(int i = 1 ; i <= n ; i++)
		sparseTable[0][i] = arr[i];
	
	for(int i = 1 ; (1 << i) <= n ; i++)  { 
		for(int j = 1 ; j + (1 << i) - 1 <= n ; j++) {
			sparseTable[i][j] = min(sparseTable[i - 1][j],sparseTable[i - 1][j + (1 << (i - 1))]); 
		}
	}	
}

int query(int l,int r) {
	int gap = 0;
	
	while((1 << gap) <= r - l + 1) {
		gap++;
	}
	
	gap--;
	
	int result = min(sparseTable[gap][l],sparseTable[gap][r - (1 << gap) + 1]);
	return result;
}

void readInput() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&arr[i]);
	}	
}

void solveQuery() {
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		int l,r;
		scanf("%d %d",&l,&r);
		l++; r++;
		printf("%d\n",query(l,r));
	}
}

int main() {
	readInput();
	buildSparseTable();
	solveQuery();
	return 0;
}
