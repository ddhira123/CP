#include <bits/stdc++.h>
using namespace std;

const int MX = 100005;
const int LETTER = 26;

int n,k;
char s[MX];
int need[LETTER];
int cnt[LETTER];

int main(){
	scanf("%d",&n);
	scanf("%s",s);
	scanf("%d",&k);
	for(int i = 0 ; i < k ; i++){
		int x;
		char ch[5];
		scanf("%d %s",&x,ch);
		need[ch[0] - 'a'] = x;
	}
	int ok = 0;
	for(int i = 0  ; i < LETTER ; i++)
		if(need[i] == 0) ok++;
	int l = 0,r = 0;
	int ans = (int)1e9;
	while(r < n){
		cnt[s[r] - 'a']++;
		if(cnt[s[r] - 'a'] == need[s[r] - 'a'])
			ok++;
		r++;
		while(l < r && cnt[s[l] - 'a'] > need[s[l] - 'a']){
			cnt[s[l] - 'a']--;
			l++;
		}	
		if(ok == LETTER)
			ans = min(ans,r - l);
	}
	if(ok == LETTER)
		printf("%d\n",ans);
	else
		puts("Andy rapopo");	
	return 0;
}
