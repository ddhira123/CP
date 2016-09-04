#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		long long R,C,a,b,c;
		scanf("%lld %lld %lld %lld %lld",&R,&C,&a,&b,&c);
		bool ok = 0;
		if(R*C != a + b + c) ok = 0;
		else {
			// jejer 1 baris
			if(a % R == 0 && b % R == 0 && c % R == 0 && (a+b+c)/R == C) ok = 1;
			// jejer 1 kolom
			if(a % C == 0 && b % C == 0 && c % C == 0 && (a+b+c)/C == R) ok = 1;

			for(int i = 0 ; i < 2 ; i++) {
				if(a % R == 0) {
					long long sisa = C - a / R;
					if(sisa > 0 && b % sisa == 0 && c % sisa == 0 && (b + c) / sisa == R)
						ok = 1;
				}
				if(b % R == 0) {
					long long sisa = C - b / R;
					if(sisa > 0 && a % sisa == 0 && c % sisa == 0 && (a + c) / sisa == R)
						ok = 1;
				}
				if(c % R == 0) {
					long long sisa = C - c / R;
					if(sisa > 0 && a % sisa == 0 && b % sisa == 0 && (a + b) / sisa == R)
						ok = 1;
				}
				swap(R,C);
			}	
		}

		if(ok) puts("Yes");
		else puts("No");
	}
	return 0;
}