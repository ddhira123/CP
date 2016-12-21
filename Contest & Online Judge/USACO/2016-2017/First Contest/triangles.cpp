/**
	O(N^3 log N)
	AC
*/
#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(),"r",stdin);
	freopen((s + ".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

const int N = 305;
typedef pair<int,int> pii;
#define fi first
#define se second

pii arr[N];
int ans[N];
int n;

long long cross(pii p,pii q,pii r) {
	long long dx1 = q.fi - p.fi;
	long long dy1 = q.se - p.se;
	long long dx2 = r.fi - p.fi;
	long long dy2 = r.se - p.se;

	return dx1 * dy2 - dx2 * dy1;
}

pii pivot;

bool cmp(pii a,pii b) {
	return cross(pivot,a,b) > 0;
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++)
		scanf("%d %d",&arr[i].fi,&arr[i].se);
}

vector<double> bagi;
int BIT[2][N];

void update(int a, int x,int val) {
	for(; x < bagi.size() ; x += x & -x)
		BIT[a][x] += val;
}

int query(int a, int x) {
	int ret = 0;
	while(x) {
		ret += BIT[a][x];
		x -= x & -x;
	}
	return ret;
}

int getIndex(double x) {
	int lo = 0, hi = bagi.size()-1;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(bagi[mid] + 1e-9 > x)
			hi = mid;
		else
			lo = mid+1;
	}
	assert(fabs(bagi[lo]-x) < 1e-9);
	return lo;
}

void solve() {
	sort(arr,arr + n);
	for(int i = 0 ; i+2 < n ; i++) {
		pivot = arr[i];
		sort(arr+i+1,arr+n,cmp);

		for(int j = i+1 ; j+1 < n ; j++) {
			for(int k = 1 ; k < bagi.size() ; k++)
				BIT[0][k] = BIT[1][k] = 0;
			bagi.clear();
			bagi.push_back(-1e9);

			for(int k = j+1 ; k < n ; k++)
				if(arr[k].se != arr[j].se) 
					bagi.push_back((double)(arr[k].fi-arr[j].fi) / (arr[k].se-arr[j].se));

			sort(bagi.begin(),bagi.end());

			int zeroY = 0;
			int xWhenZeroY = 0;

			int positivePRX = 0;
			int negativePRX = 0;
			
			int positivePRY = 0;
			int negativePRY = 0;

			for(int k = j+1 ; k < n ; k++) {
				int inside = 0;

				if(arr[k].se == arr[j].se) {
					if(arr[k].fi-arr[j].fi > 0) {
						inside += positivePRY;
					}
					else {
						inside += negativePRY;
					}
				}
				else {
					double temp = (double)(arr[k].fi-arr[j].fi) / (arr[k].se-arr[j].se);
					int idx = getIndex(temp);
					
					// kasus dy > 0
					if(arr[k].se > arr[j].se) {
						// ambil yang positive kurang dari
						inside += query(0,idx-1);
						// ambil yang negative lebih dari
						inside += (query(1,bagi.size()-1) - query(1,idx));
					}
					else {
						// ambil yang negative kurang dari
						inside += query(1,idx-1);
						// ambil yang positive lebih dari
						inside += (query(0,bagi.size()-1) - query(0,idx));
					}
				}

				if(zeroY) {
					if(arr[k].se-arr[j].se > 0) {
						inside += (xWhenZeroY < 0);
					}
					else {
						inside += (xWhenZeroY > 0);
					}
				}

				ans[inside]++;

				if(arr[k].se == arr[j].se) {
					//assert(!zeroY);
					zeroY = 1;
					xWhenZeroY = arr[k].fi - arr[j].fi;
				}
				else {
					double temp = (double)(arr[k].fi-arr[j].fi) / (arr[k].se-arr[j].se);
					int idx = getIndex(temp);

					if(arr[k].se > arr[j].se)
						update(0,idx,1);
					else
						update(1,idx,1);

					if(arr[k].se - arr[j].se > 0)
						positivePRY++;
					else
						negativePRY++;

					if(arr[k].fi - arr[j].fi > 0)
						positivePRX++;
					else if(arr[k].fi - arr[j].fi < 0)
						negativePRX++;
				}
			}
		}
		sort(arr+i+1,arr+n);
	}

	for(int i = 0 ; i+2 < n ; i++)
		printf("%d\n",ans[i]);
}

int main() {
	OPEN("triangles");
	read();
	solve();
	CLOSE();
	return 0;
}