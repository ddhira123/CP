/**
	Sparse Table
	
	An easy data structure which used DP principles
	Can be used if there is no update in the data
	I'll use range min query for example
	
	Complexity : O(N log N) for building
				 O(log N) for query
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 20;

int sparseTable[LOG][N];
int n,q;
int arr[N];

void buildSparseTable() {
	//building base case, where each partition consists of length 1 or 2^0
	for(int i = 1 ; i <= n ; i++)
		sparseTable[0][i] = arr[i];
	
	for(int i = 1 ; (1 << i) <= n ; i++)  { // for each power of 2
		for(int j = 1 ; j + (1 << i) - 1 <= n ; j++) { // for each start point which can extends with length 2^i
			sparseTable[i][j] = min(sparseTable[i - 1][j],sparseTable[i - 1][j + (1 << (i - 1))]); 
		}
	}	
}

int query(int l,int r) {
	// find highest power of 2 which is <= r - l + 1
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
		printf("Minimum from %d to %d is %d\n",l,r,query(l,r));
	}
}

int main() {
	readInput();
	buildSparseTable();
	solveQuery();
	return 0;
}
