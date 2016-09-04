#include <bits/stdc++.h>
using namespace std;

inline void io(int &ptr){
	ptr = 0;
    register char c;
    while(1){
        c = getchar_unlocked();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else       res = c-'0';
    while(1){
        c = getchar_unlocked();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    ptr =  res * sign;
}

int main(){
	//ios_base::sync_with_stdio(0);
	int tc;
	io(tc);
	for(int t = 1 ; t <= tc ; t++){
		int n;
		int nim = 0;
		io(n);
		for(int i = 0 ; i < n ; i++){
			int x;
			io(x);
			int tot = x ? __builtin_ctz(x) : 0;
			nim ^= tot;
		}
		if(nim)
			puts("Puguh is the bestest player in teh wurld");
		else
			puts("Joke is the bestest player in teh wurld");	
	}
	return 0;
}
