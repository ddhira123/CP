#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 1005;

int arr[N][N];
int n,m,k;
pair<int, long long> row[N][N];
int zeroR[N];
pair<int, long long> col[N][N];
int zeroC[N];
int ansr[N];
int ansc[N];

int main() {
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			scanf("%d",&arr[i][j]);
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 1 ; j <= m ; j++) {
			row[i][j].first = arr[i][j];
			zeroR[i] += (arr[i][j] == 0);
		}
		sort(row[i] + 1,row[i] + m + 1);
		for(int j = 1 ; j <= m ; j++)
			row[i][j].second = row[i][j].first + row[i][j-1].second;
	}

	for(int j = 1 ; j <= m ; j++) {
		for(int i = 1 ; i <= n ; i++) {
			col[j][i].first = arr[i][j];
			zeroC[j] += (arr[i][j] == 0);
		}
		sort(col[j] + 1,col[j] + n + 1);
		for(int i = 1 ; i <= n ; i++)
			col[j][i].second = col[j][i].first + col[j][i-1].second;
	}

	LL best = 4e18;
	int tipe = -1;
	int r = -1;
	int c = -1;

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++) {
			// ubah row baru ubah col
			int pivot = arr[i][j];
			pair<int, long long> temp = {pivot+1,-1};
			int idx = lower_bound(col[j] + 1,col[j] + n + 1,temp) - col[j];
			idx--;
			long long tot = 0;
			// ubah row
			tot += ((LL)pivot * idx - col[j][idx].se);
			tot += ((LL)pivot * (n - idx));
			tot += ((LL)(n - idx) * k);
			tot -= (col[j][n].se - col[j][idx].se);
			// ubah col
			tot += ((LL)k * m - row[i][m].se);
			tot -= ((LL)k * zeroR[i]);

			if(tot < best) {
				best = tot;
				tipe = 0;
				r = i;
				c = j;
			}

			// ubah col baru row
			pivot = arr[i][j];
			temp = {pivot+1,-1};
			idx = lower_bound(row[i] + 1,row[i] + m + 1,temp) - row[i];
			idx--;
			tot = 0;
			// ubah col
			tot += ((LL)pivot * idx - row[i][idx].se);
			tot += ((LL)pivot * (m - idx));
			tot += ((LL)(m - idx) * k);
			tot -= (row[i][m].se - row[i][idx].se);
			// ubah col
			tot += ((LL)k * n - col[j][n].se);
			tot -= ((LL)k * zeroC[j]);

			if(tot < best) {
				best = tot;
				tipe = 1;
				r = i;
				c = j;
			}
		}

	printf("%lld\n",best);
	if(tipe == 0) {
		int pivot = arr[r][c];
		for(int ii = 1 ; ii <= n ; ii++) {
			int diff = pivot - arr[ii][c];
			if(diff < 0) diff += k;
			printf("%d ",diff);
		}
		puts("");
		for(int j = 1 ; j <= m ; j++) {
			int diff = k - arr[r][j];
			if(diff == k) diff = 0;
			printf("%d ",diff);
		}
		puts("");
	}
	else {
		int pivot = arr[r][c];
		for(int i = 1 ; i <= n ; i++) {
			int diff = k - arr[i][c];
			if(diff == k) diff = 0;
			printf("%d ",diff);
		}
		puts("");
		for(int jj = 1 ; jj <= m ; jj++) {
			int diff = pivot - arr[r][jj];
			if(diff < 0) diff += k;
			printf("%d ",diff);
		}
		puts("");
	}		
	return 0;
}