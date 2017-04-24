#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

int main() {
	OPEN("java2016");
	int s; cin >> s;
	if(s == 0) cout << "?/?/?\n";
	else {
		printf("a = ? max ?\n");
		for(int i = 1 ; i < 18 ; i++)
			printf("%c = %c max %c\n",i + 'a',i-1 + 'a',i-1 + 'a');
		printf("%c = %c/%c\n",'a' + 18,'a'+17,'a'+17);
		for(int i = 19 ; i < 26 ; i++)
			printf("%c = %c+%c\n",i + 'a',i-1 + 'a',i-1 + 'a');
		vector<int> use;
		for(int i = 0 ; i < 18 ; i++)
			if(s & (1<<i))
				use.push_back(i);

		for(int i = 0 ; i < use.size() ; i++)
			printf("%c%c",use[i]+18+'a',i+1 == use.size() ? '\n' : '+');	
	}
	CLOSE();
	return 0;
}