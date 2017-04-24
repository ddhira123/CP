#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second
#define pb push_back

const int N = 150005;

int arr[N];
int n;

vector<pii> shit;
set<pii> st;
int salah[N];
int total;

void update(int x) {
	total -= salah[x];
	salah[x] = (x == n ? 0 : x & 1 ? arr[x] >= arr[x + 1] : arr[x] <= arr[x + 1]);
	total += salah[x];
} 

void updater(int x) {
	for(int i = max(1,x - 1) ; i <= min(n,x + 1) ; i++)
		update(i);
}

int query(int a,int b) {
	swap(arr[a],arr[b]);
	updater(a); updater(b);

	int res = 0;
	//printf("%d %d %d\n",a,b,total);
	if(total == 0) res = 1;

	swap(arr[a],arr[b]);
	updater(a); updater(b);

	return res;	
}

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
	for(int i = 1 ; i <= n ; i++)
		update(i);
	for(int i = 1 ; i <= n ; ) 
		if(salah[i]) {
			int j = i;
			while(j <= n && salah[j]) j++;
			shit.pb({i,j - 1});
			//printf("%d %d\n",i,j);
			i = j;
		}
		else {
			i++;
		}
	
	if(shit.size() <= 4 && total <= 6) {
		vector<int> candidate;

		for(int idx = 0 ; idx < shit.size() ; idx++)
			for(int i = max(1,shit[idx].fi - 1) ; i <= min(n,shit[idx].se + 1) ; i++)
				candidate.pb(i);


		sort(candidate.begin(), candidate.end());
		candidate.erase(unique(candidate.begin(), candidate.end()),candidate.end());	

		for(int x : candidate)
			for(int i = 1 ; i <= n ; i++) 
				if(i != x){
				int ret = query(i,x);
				if(ret == 1)
					st.insert({min(x,i),max(x,i)});
			}
	}	

	cout << st.size() << endl;
	return 0;
}