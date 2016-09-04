// salah
#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int MAGIC = 100;

double dp[2][1<<N];
double arr[N];
double ans[N];
double sums[N];
int bits[1<<N];
int n, k;
vector<int> cand;

void prec() {
	for(int i = 1 ; i < (1<<N) ; i++) {
		bits[i] = 1 + bits[i - (i & -i)];
		//sums[i] = arr[i & -i] + sums[i - (i & -i)];
	}
}

void DP() {
	for(int i = 0 ; i < n ; i++) {
		dp[1][1<<i] = arr[i];
	}

	for(int iter = 1 ; iter < k ; iter++) {
		int bit = (iter & 1);
		int nbit = bit ^ 1;

		for(int i = 0 ; i < (1<<n) ; i++)
			dp[nbit][i] = 0;

		for(int i = 0 ; i < (1<<n) ; i++) {
			if(bits[i] > k || dp[bit][i] < 1e-12) continue;
			if(bits[i] < k) {
				for(int j = 0 ; j < n ; j++)
					dp[nbit][i | (1<<j)] += dp[bit][i] * arr[j];
			}
			else {
				dp[nbit][i] += dp[bit][i];
			}
		}
	}
	
	int bit = k & 1;
	for(int i = 1 ; i < (1<<n) ; i++) {
		double add = 0;
		for(int j = 0 ; j < n ; j++) {
			if(i & (1<<j))
				add += arr[j];
		}
		for(int j = 0 ; j < n ; j++)
			if(i & (1<<j))
				ans[j] += dp[bit][i];
			else if(bits[i] < k)
				ans[j] += dp[bit][i]*arr[j]/(1-add);
	}

	for(int i = 0 ; i < n ; i++)
		printf("%.15lf\n",ans[i]);		
}

int main() {
	scanf("%d %d",&n,&k);
	for(int i = 0 ; i < n ; i++)
		scanf("%lf",&arr[i]);
	prec();
	DP();
	return 0;
}