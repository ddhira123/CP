#include <bits/stdc++.h>
using namespace std;

string mapping[1000];

void precompute() {
	mapping[0] = "nol";
	mapping[1] = "satu";
	mapping[2] = "dua";
	mapping[3] = "tiga";
	mapping[4] = "empat";
	mapping[5] = "lima";
	mapping[6] = "enam";
	mapping[7] = "tujuh";
	mapping[8] = "delapan";
	mapping[9] = "sembilan";
	mapping[10] = "sepuluh";
	mapping[11] = "sebelas";
	for(int i = 2 ; i <= 9 ; i++)
		mapping[10 + i] = mapping[i] + " belas";
	for(int i = 20 ; i <= 99 ; i++) {
		mapping[i] = mapping[i / 10] + " puluh";
		if(i % 10 != 0) {
			mapping[i] = mapping[i] + " " + mapping[i % 10];
		}
	}
	mapping[100] = "seratus";
	for(int i = 101 ; i <= 199 ; i++) {
		mapping[i] = "seratus " + mapping[i % 100];
	}
	for(int i = 200 ; i <= 999 ; i++) {
		mapping[i] = mapping[i / 100] + " ratus";
		if(i % 100 != 0) {
			mapping[i] = mapping[i] + " " + mapping[i % 100];
		}
	}
}

string get_read(int x) {
	if(x == 1000000000) {
		return "satu milyar";
	}
	if(x < 1000) return mapping[x];

	string ret = "";
	int y = x % 1000;
	if(y != 0) {
		ret = mapping[y];
	}

	x /= 1000;
	y = x % 1000;
	if(y == 1) {
		if(ret.length() == 0) ret = "seribu";
		else ret = "seribu " + ret;
	} else if(y != 0) {
		if(ret.length() == 0) ret = mapping[y] + " ribu";
		else ret = mapping[y] + " ribu " + ret; 
	}

	x /= 1000;
	if(x != 0) {
		y = x % 1000;
		if(ret.length() == 0) ret = mapping[y] + " juta";
		else ret = mapping[y] + " juta " + ret; 
	}

	return ret;
}

int main() {
	precompute();
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;
		set<int> s;
	
		printf("Kasus #%d: ", tc);
		for(int i = 1 ; ; i++) {
			if(s.count(n)) {
				printf("%d\n", n);
				break;
			} else {
				s.insert(n);
				// cout << n << " " << get_read(n) << endl;
				n = get_read(n).length();
			}
		}
	}
	return 0;
}