#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 805;
const int Q = 1005;

vector<int> uniq;
vector<pii> isi[N*N];
vector<int> haha[N*N];
int BIT[N][N];
int l[Q], r[Q];
int a[Q], b[Q], c[Q], d[Q]; 
int arr[N][N];
int n, q;

void update(int x,int y, int val) {
	x++; y++;
	for(int i = x ; i <= n ; i += i & -i)
		for(int j = y ; j <= n ; j += j & -j)
			BIT[i][j] += val;
}

int query(int x,int y) {
	x++; y++;
	int ret = 0;
	for(int i = x ; i > 0 ; i -= i & -i)
		for(int j = y ; j > 0 ; j -= j & -j)
			ret += BIT[i][j];
	return ret;	
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++)
			scanf("%d", &arr[i][j]);
	}

	for(int i = 0 ; i < q ; i++) {
		scanf("%d %d %d %d", a + i, b + i, c + i, d + i);
		a[i]--;
		b[i]--;
		c[i]--;
		d[i]--;
	}
}

void prepare() {
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++)
			uniq.push_back(arr[i][j]);
	}
	sort(uniq.begin(), uniq.end());
	uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			//printf("%d",arr[i][j]);
			arr[i][j] = lower_bound(uniq.begin(), uniq.end(), arr[i][j]) - uniq.begin();
			//printf(" %d\n", arr[i][j]);
			isi[arr[i][j]].push_back({i, j});
		}

	for(int i = 0 ; i < q ; i++) {
		l[i] = 0;
		r[i] = uniq.size()-1;
		haha[(uniq.size()-1) / 2].push_back(i);
	}
}

void solve() {
	bool ada = 1;
	while(ada) {
		ada = 0;
		memset(BIT, 0, sizeof BIT);
		int udah = 0;
		for(int i = 0 ; i < uniq.size() ; i++) {
			for(pii x : isi[i]) {
				udah++;
				update(x.fi, x.se, 1);
			}

			while(!haha[i].empty()) {
				int x = haha[i].back();
				haha[i].pop_back();

				int A = a[x];
				int B = b[x];
				int C = c[x];
				int D = d[x];

				int size = (C-A+1) * (D-B+1);
				int active = query(C, D) - query(A-1,D) - query(C,B-1) + query(A-1,B-1);

				// if(x == 0) {
				// 	printf("%d %d %d %d\n", A, B, C, D);
				// 	printf("size %d active %d\n", size, active);
				// 	printf("l %d r %d\n", l[x], r[x]);
				// 	printf("udah %d\n", udah);
				// }

				if(active * 2 >= size) {
					r[x] = i;
				} else {
					l[x] = i+1;
				}

				if(l[x] < r[x]) {
					haha[(l[x] + r[x]) / 2].push_back(x);
					ada = 1;
				}
			}
		}
	}

	for(int i = 0 ; i < q ; i++)
		printf("%d\n", uniq[l[i]]);
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}