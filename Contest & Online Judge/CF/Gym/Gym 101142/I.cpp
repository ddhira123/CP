#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

typedef long long LL;

const int N = 2e5 + 5;

int cnt[2*N][2][2][2];
int occ[2][2][2];
int sums[2*N];
int x[2*N], y[2*N];
int tmp[2*N];
int n;

LL cross(LL a,LL b,LL c,LL d) {
	return a*c - b*d;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d %d", x + i, y+i);
}

void clean() {
	int idx = -1;
	for(int i = n+1 ; i <= 2*n ; i++) {
		x[i] = x[i-n];
		y[i] = y[i-n];
	}

	for(int i = 1 ; idx == -1 ; i++)
		if(cross(x[i+1]-x[i],y[i+1]-y[i],x[i+2]-x[i],y[i+2]-y[i]) != 0)
			idx = i;
	//printf("idx %d\n",idx);
	for(int i = 1 ; i <= n ; i++)
		tmp[i] = x[i];
	for(int i = 1 ; i <= n ; i++) {
		int now = i - idx + 1;
		if(now <= 0) now += n;
		x[now] = tmp[i];
		//cout << now << " " << x[now] << "\n";
	}

	for(int i = 1 ; i <= n ; i++)
		tmp[i] = y[i];
	for(int i = 1 ; i <= n ; i++) {
		int now = i - idx + 1;
		if(now <= 0) now += n;
		y[now] = tmp[i];
	}

	for(int i = n+1 ; i <= 2*n ; i++) {
		x[i] = x[i-n];
		y[i] = y[i-n];
	}
}

LL countPolygon() {
	for(int i = 1 ; i < 2*n ; i++) {
		LL mul = 1ll * x[i] * y[i+1] - 1ll * x[i+1] * y[i];
		mul = abs(mul) % 2;
		sums[i] = abs(sums[i-1] + mul) % 2;

		LL xx = abs(x[i+1]) % 2;
		LL yy = abs(y[i+1]) % 2;

		for(int a = 0 ; a < 2 ; a++)
			for(int b = 0 ; b < 2 ; b++)
				for(int c = 0 ; c < 2 ; c++)
					cnt[i][a][b][c] = cnt[i-1][a][b][c];
		//printf("%d -> %d %lld %lld\n",i,sums[i],xx,yy);
		cnt[i][sums[i]][xx][yy]++;		
	}

	LL ret = 0;
	for(int i = n ; i >= 1 ; i--) {
		LL add = 0;
		for(int a = 0 ; a < 2 ; a++)
			for(int b = 0 ; b < 2 ; b++)
				for(int c = 0 ; c < 2 ; c++) {
					LL area = a - sums[i-1];
					LL xx = 1ll * b * y[i];
					LL yy = 1ll * x[i] * c;
					LL all = area + xx - yy;
					all = abs(all) % 2;
					if(all == 0) {
						//printf("i %d abc %d%d%d\n",i,a,b,c);
						add += (cnt[i+n-3][a][b][c] - cnt[i][a][b][c]);
					}
				}
		ret += add;
		//printf("%d %lld %d %d\n",i,add,x[i],y[i]);				
	}
	//cout << ret << "\n";
	ret /= 2;
	return ret;			
}

LL countLine() {
	LL ret = 0;
	for(int i = 1 ; i+1 <= n ;) {
		int j = i+1;
		while(j+1 <= n && cross(x[j]-x[i],y[j]-y[i],x[j+1]-x[i],y[j+1]-y[i]) == 0)
			j++;
		LL add = j-i+1;
		add = add * (add-1) / 2;
		add -= (j-i);
		ret += add;
		i = j;
	}
	return ret;
}

int main() {
	OPEN("integral");
	read();
	clean();
	LL ans = countPolygon();
	ans -= countLine();
	if(sums[n] != 0) ans = 0;
	cout << ans << "\n";
	CLOSE();
	return 0;
}