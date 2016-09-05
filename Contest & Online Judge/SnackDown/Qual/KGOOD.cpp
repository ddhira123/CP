#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int cnt[300];
char s[N];
int k;

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%s %d",s,&k);

		memset(cnt,0,sizeof cnt);
		int len = strlen(s);

		for(int i = 0 ; i < len ; i++)
			cnt[s[i]]++;

		vector<int> v;
		for(int i = 'a' ; i <= 'z' ; i++)
			if(cnt[i])
				v.push_back(cnt[i]);

		sort(v.begin(),v.end());
		int ans = N;	
		
		for(int i = 0 ; i < v.size() ; i++) {
			int tot = 0;
			for(int j = 0 ; j < i ; j++)
				tot += v[j];
			for(int j = i ; j < v.size() ; j++)
				tot += max(0,v[j] - (v[i] + k));
			ans = min(ans,tot);
		}		

		printf("%d\n",ans);				 
	}
	return 0;
}