// WA
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 200005;

pair<int,int> arr[N];
int kiri[N];
int kanan[N];
int n;

long long cross(int a,int b,int c) {
	long long dx1 = arr[b].fi - arr[a].fi;
	long long dx2 = arr[c].fi - arr[a].fi;
	long long dy1 = arr[b].se - arr[a].se;
	long long dy2 = arr[c].se - arr[a].se;
	return dx1 * dy2 - dx2 * dy1;
}

void make() {
	vector<int> v;
	v.clear();
	for(int i = 1 ; i <= n ; i++) {
		if(!v.empty()){
			kiri[i] = v.back();
			for(int j = (int)v.size() - 2 ; j >= 0 && cross(v[j],kiri[i],i) < 0 ; j--)
				kiri[i] = v[j];
		}
		while(v.size() > 1 && cross(v[v.size()-2],v.back(),i) <= 0) v.pop_back();
		v.push_back(i);
		if(arr[v.back()].se >= arr[v[0]].se) {
			v.clear();
			v.push_back(i);
		}
	}
	
	v.clear();
	for(int i = n ; i >= 1 ; i--) {
		if(!v.empty()) {
			kanan[i] = v.back();
			for(int j = (int)v.size() - 2 ; j >= 0 && cross(v[j],kanan[i],i) < 0 ; j--)
				kanan[i] = v[j];
		}
		while(v.size() > 1 && cross(v[v.size()-2],v.back(),i) <= 0) v.pop_back();
		v.push_back(i);
		if(arr[v.back()].se >= arr[v[0]].se) {
			v.clear();
			v.push_back(i);
		}
	}
}

double toRad(double x) {
	static double PI = acos(-1);
	return x / 180.0 * PI;
}

double toDeg(double x) {
	static double PI = acos(-1);
	return x / PI * 180.0;
}

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d %d",&arr[i].fi,&arr[i].se);
		assert(arr[i].fi > arr[i-1].fi);
	}
	make();
	for(int i = 1 ; i <= n ; i++) {
		double all = 180.0;
		if(arr[kiri[i]].se >= arr[i].se) {
			int idx = kiri[i];
			double lost = 0;
			lost = toDeg(atan2(arr[idx].se - arr[i].se,arr[i].fi - arr[idx].fi));
			all -= lost;
		}
		if(arr[kanan[i]].se >= arr[i].se) {
			int idx = kanan[i];
			double lost = 0;
			lost = toDeg(atan2(arr[idx].se - arr[i].se,arr[idx].fi - arr[i].fi));
			all -= lost;
		}
		//printf("%d %d %d\n",i,kiri[i],kanan[i]);
		printf("%.6lf\n",all * 12 / 180);
	}
	return 0;
}