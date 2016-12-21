/**
	O(NK log K) with funny optimization
	10/15 TC
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

const int K = 1e5 + 5;
const int M = 11;

typedef pair<long long,int> pli;

int n, k;
long long smallest[K];
int arr[M];
vector<vector<int>> asu;

bool cmp(vector<int> a,vector<int> b) {
	if(a.size() == 1) return 1;
	if(b.size() == 1) return 0;
	return a[1]-a[0] < b[1]-b[0];
}

int main() {
	OPEN("roboherd");

	scanf("%d %d",&n,&k);
	for(int i = 0 ; i < k ; i++)
		smallest[i] = 4e18;
	smallest[0] = 0;

	long long tambah = 0;
	for(int i = 0 ; i < n ; i++) {
		int m; scanf("%d",&m);
		for(int j = 0 ; j < m ; j++)
			scanf("%d",&arr[j]);
		
		vector<int> v;

		for(int j = 0 ; j < m ; j++) {
			v.push_back(arr[j]);	
		}
		sort(v.begin(),v.end());
		if(v.size() == 1)
			tambah += v[0];
		else
			asu.push_back(v);

		/*
		if(v.size()>1 && smallest[0]+v[1] < smallest[k-1] + v[0]) {
			priority_queue<pli,vector<pli>,greater<pli> > pq;
			for(int j = 0 ; j < k ; j++)
				pq.push({smallest[j] + v[0],0});

			for(int j = 0 ; j < k ; j++) {
				pli temp = pq.top();
				pq.pop();
				int idx = temp.second;
				smallest[j] = temp.first;
				if(idx+1 < v.size())
					pq.push({temp.first - v[idx] + v[idx+1], idx+1});
			}
		}
		else {
			tambah += v[0];
		}*/
	}

	sort(asu.begin(),asu.end(),cmp);
	for(vector<int> v : asu) {
		if(v.size()>1 && smallest[0]+v[1] < smallest[k-1] + v[0]) {
			priority_queue<pli,vector<pli>,greater<pli> > pq;
			for(int j = 0 ; j < k ; j++)
				pq.push({smallest[j] + v[0],0});

			for(int j = 0 ; j < k ; j++) {
				pli temp = pq.top();
				pq.pop();
				int idx = temp.second;
				smallest[j] = temp.first;
				if(idx+1 < v.size())
					pq.push({temp.first - v[idx] + v[idx+1], idx+1});
			}
		}
		else {
			tambah += v[0];
		}
	}

	printf("%lld\n",accumulate(smallest,smallest + k,0ll) + tambah * k);

	CLOSE();
	return 0;
}