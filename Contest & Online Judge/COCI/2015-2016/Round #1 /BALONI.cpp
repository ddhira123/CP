#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

int n;
pii arr[N + 5];

pii getIndice(int x){
	int l = upper_bound(arr + 1,arr + n + 1,mp(x - 1,N)) - arr;
	int r = upper_bound(arr + 1,arr + n + 1,mp(x,N)) - arr;
	return mp(l,r); 
}

queue<int> q[2];

int get(int x){
	pii atas = getIndice(x);
	pii bawah = getIndice(x - 1);
	for(int i = atas.fi ; i < atas.se ; i++)
		q[0].push(arr[i].se);
	for(int i = bawah.fi ; i < bawah.se ; i++)
		q[1].push(arr[i].se);
	int ret = 0;
	while(!q[0].empty()) {
		while(!q[1].empty() && q[1].front() < q[0].front()) {
			q[1].pop();
			ret++;
		}	
		q[0].pop();
		if(!q[1].empty())
			q[1].pop();	
	}		
	while(!q[1].empty()) {
		q[1].pop();
		ret++;
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&arr[i].fi);
		arr[i].se = i;
	}
	sort(arr + 1,arr + n + 1);
	int ans = 0;	
	for(int i = N + 1 ; i >= 2 ; i--)
		ans += get(i);
	printf("%d\n",ans);		
	return 0;
}
