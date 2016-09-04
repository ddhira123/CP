#include <bits/stdc++.h>
using namespace std;

string s;

int parse(int l,int tab) {
	for(int i = 0 ; i < tab ; i++) printf(" ");
	printf("{\n");
	l++;
	tab += 2;
	while(s[l] != '}') {
		if(s[l] == '{') {
			l = parse(l,tab) + 1;
			if(s[l] == ',') l++,printf(",\n");
			else printf("\n");
		}
		else {
			int r = l;
			while(s[r] != ',' && s[r] != '}') r++;
			if(s[r] == '}') r--;
			for(int i = 0 ; i < tab ; i++) printf(" ");
			for(int i = l ; i <= r ; i++) printf("%c",s[i]);
			puts("");
			l = r + 1;
		}
	}
	tab -= 2;
	for(int i = 0 ; i < tab ; i++) printf(" ");
	printf("}");
	return l;
}

int main() {
	cin >> s;
	int temp = parse(0,0);
	puts("");
	return 0;
}