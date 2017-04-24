#include <stdio.h>

int cnt[15];
int f,t,ii;
int i,j;

int main() {
	scanf("%d %d %d",&f,&ii,&t);	
	for(i = 0 ; i < f ; i++) {
		char s[15];
		scanf("%s",s);
		for(j = 0 ; j < ii ; j++)
			if(s[j] == 'Y')
				cnt[j]++;
	}
	int ans = 0;
	for(i = 0 ; i < ii ; i++)
		if(cnt[i] >= t) ans++;
	printf("%d\n",ans);
	return 0;
}