#include <bits/stdc++.h>
using namespace std;

void rec(int a,int b) {
	if(a == 0) return;
	int sisa = a / b;
	while(sisa*b > a) sisa++;
	rec(sisa,b);
	sisa = a - sisa*b;
	printf("%d",sisa);
}

int main() {
	string x;
	cin >> x;
	while(x != "end") {
		string n; cin >> n;

		if(x[0] == 'f') {
			int base = x[5] - '0';
			if(x.length() > 6) base = base*10 + x[6]-'0';
			int ret = 0;
			int mul = 1;

			for(int i = n.length()-1 ; i >= 0 ; i--) {
				//printf("%d %d %d\n",i,mul,base);
				ret = ret + (int)(n[i] - '0') * mul;
				mul *= (-1 * base);
			}

			cout << ret << "\n";
		}
		else {
			int base = x[3] - '0';
			if(x.length() > 4) base = base*10 + x[4]-'0';

			if(n == "0") cout << "0\n";
			else {
				int nn = 0;
				int mul = n[0] == '-' ? -1 : 1;
				for(char z : n) {
					if(z == '-') continue;
					nn = nn * 10 + (z - '0');
				}
				//printf("%d\n",mul*nn);
				rec(mul*nn,-base);
				puts("");
			}
		}
		cin >> x;
	}
	return 0;
}