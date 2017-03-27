#include <bits/stdc++.h>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_cxx; //namespace with rope and some additional stuff

char s[100005];
rope<char> ropes;
int len;
int q;

int main() {
	scanf("%s",s);
	len = strlen(s);
	for(int i = 0 ; i < len ; i++)
		ropes.push_back(s[i]);

	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int opt; scanf("%d",&opt);
		if(opt == 3) {
			int x; scanf("%d",&x);
			printf("%c\n",ropes[x]);
		}
		else {
			int l, r;
			scanf("%d %d",&l,&r);

			if(opt == 1) {
				rope<char> temp = ropes.substr(l,r-l+1);
				ropes.erase(l,r-l+1);
				ropes.insert(0,temp);
			}
			else {
				rope<char> temp = ropes.substr(l,r-l+1);
				ropes.insert(len,temp);
				ropes.erase(l,r-l+1);
			}
		}
	}
	return 0;
}