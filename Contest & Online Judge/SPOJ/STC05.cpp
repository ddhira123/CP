#include <bits/stdc++.h>
using namespace std;
#define mp make_pair

const int N = 100005;

struct point {
	int x;
	int y;
	int idx;
};

point pnt[N];
pair<int,int> arr[N];
int n;

int atas[N], cntAtas[N];
int kiri[N], cntKiri[N];

bool byX(point a,point b) {
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

bool byY(point a,point b) {
	if(a.y == b.y)
		return a.x < b.x;
	return a.y < b.y;
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d %d",&arr[i].first,&arr[i].second);
	}
	sort(arr,arr + n);
	for(int i = 0 ; i < n ; i++) {
		pnt[i].x = arr[i].first;
		pnt[i].y = arr[i].second;
		pnt[i].idx = i;
	}
}

void initialize() {
	// bikin atas
	sort(pnt,pnt + n,byX);
	for(int i = 0 ; i < n ;) {
		int j = i;
		while(j < n && pnt[i].x == pnt[j].x) {
			int idx = pnt[j].idx;
			if(j == i) {
				atas[idx] = -1;
			}
			else {
				atas[idx] = pnt[j - 1].idx;
				cntAtas[idx] = j - i;
			}

			j++;
		}

		i = j;
	}

	// bikin kiri
	sort(pnt,pnt + n,byY);
	for(int i = 0 ; i < n ;) {
		int j = i;
		while(j < n && pnt[i].y == pnt[j].y) {
			int idx = pnt[j].idx;
			if(j == i) {
				kiri[idx] = -1;
			}
			else {
				kiri[idx] = pnt[j - 1].idx;
				cntKiri[idx] = j - i;
			}

			j++;
		}

		i = j;
	}	
}

int calc() {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		if(cntAtas[i] <= cntKiri[i]) {
			for(int j = atas[i] ; j != -1 ; j = atas[j]) {
				int xx = arr[i].first;
				int yBawah = arr[i].second;
				int yAtas = arr[j].second;
				int diff = abs(yBawah - yAtas);

				pair<int,int> temp = mp(xx - diff,yBawah);
				pair<int,int> temp2 = mp(xx - diff,yAtas);

				if(binary_search(arr,arr + n,temp) && binary_search(arr,arr + n,temp2))
					ret++;
			}
		}
		else {
			for(int j = kiri[i] ; j != -1 ; j = kiri[j]) {
				int yy = arr[i].second;
				int xKanan = arr[i].first;
				int xKiri = arr[j].first;
				int diff = abs(xKanan - xKiri);

				pair<int,int> temp = mp(xKiri,yy - diff);
				pair<int,int> temp2 = mp(xKanan,yy - diff);

				if(binary_search(arr,arr + n,temp) && binary_search(arr,arr + n,temp2))
					ret++;
			}
		}
	return ret;	
}

int main() {
	read();
	initialize();
	printf("%d\n",calc());
	return 0;
}