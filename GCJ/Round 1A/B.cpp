#include <bits/stdc++.h>
using namespace std;

const int MAXX = 2505;
const int N = 55;

vector<int> v[2 * N];
int n;
int lol[N][N];
bool udah[2][N];

bool can(int mode,int idx,int pos) {
	bool ok = 1;
	if(mode == 0) {
		for(int i = 0 ; i < n ; i++)
			ok &= (lol[pos][i] == -1 || lol[pos][i] == v[idx][i]);
	}
	else {
		for(int i = 0 ; i < n ; i++)
			ok &= (lol[i][pos] == -1 || lol[i][pos] == v[idx][i]);	
	}
	return ok;
}

void place(int mode,int idx,int pos) {
	if(mode == 0) {
		for(int i = 0 ; i < n ; i++) {
			lol[pos][i] = v[idx][i];
			//printf("pos %d i %d %d\n",pos,i,v[idx][i]);
		}
	}
	else {
		for(int i = 0 ; i < n ; i++) {
			lol[i][pos] = v[idx][i];
			//printf("C pos %d i %d %d\n",pos,i,v[idx][i]);
		}
	}
}

void pasangDepan() {
	for(int i = 0 ; i < 2 * n - 1 ; i++) {
		for(int iter = 0 ; iter < n ; iter++) {
			if(!udah[0][iter] && can(0,i,iter)) {
				place(0,i,iter);
				udah[0][iter] = 1;
				//printf("0 %d %d\n",i,iter);
				break;
			}
			if(!udah[1][iter] && can(1,i,iter)) {
				place(1,i,iter);
				udah[1][iter] = 1;
				//printf("1 %d %d\n",i,iter);
				break;
			}
		}
	}
}

void pasangBelakang() {
	for(int i = 2*n - 1 ; i >= 0 ; i--) {
		for(int iter = n-1 ; iter >= 0 ; iter--) {
			if(!udah[0][iter] && can(0,i,iter)) {
				place(0,i,iter);
				udah[0][iter] = 1;
				//printf("%d %d\n",i,iter);
				break;
			}
			if(!udah[1][iter] && can(1,i,iter)) {
				place(1,i,iter);
				//printf("%d %d\n",i,iter);
				udah[1][iter] = 1;
				break;
			}
		}
	}
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> n;
		for(int i = 0 ; i < 2 * n - 1 ; i++) {
			v[i].clear();
			for(int j = 0 ; j < n ; j++) {
				int x;
				cin >> x;
				v[i].push_back(x);
			}
		}
		sort(v,v + 2 * n - 1);
		memset(lol,-1,sizeof lol);
		memset(udah,0,sizeof udah);
		if(v[0][0] == v[1][0])
			pasangDepan();
		else
			pasangBelakang();
		vector<int> ans;
		for(int i = 0 ; i < n ; i++) {
			if(!udah[0][i]) {
				for(int j = 0 ; j < n ; j++)
					ans.push_back(lol[i][j]);
				break;
			}
			if(!udah[1][i]) {
				for(int j = 0 ; j < n ; j++)
					ans.push_back(lol[j][i]);
				break;
			}
		}
		puts("CASE");
		for(int i = 0 ; i <2*n-1 ; i++) {
			for(int x : v[i]) printf("%d ",x);
				puts("");
		}
		for(int i = 0 ; i < n ; i++)
			for(int j = 0 ; j < n ; j++)
				printf("%d%c",lol[i][j],j+1==n ? '\n' : ' ');
		assert(!ans.empty());
		printf("Case #%d:",tc);
		for(int x : ans) {
			printf(" %d",x);
			assert(x != -1);
		}
		puts("");
	}
	return 0;
} 