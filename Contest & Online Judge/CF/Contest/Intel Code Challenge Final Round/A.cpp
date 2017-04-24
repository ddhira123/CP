#include <bits/stdc++.h>
using namespace std;

int arr[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string str[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};

int main() {
	string a, b; cin >> a >> b;
	int aa, bb;
	for(int i = 0 ; i < 7 ; i++) {
		if(a == str[i]) aa = i;
		if(b == str[i]) bb = i;
	}
	// /cerr << aa << " " << bb << "\n";
	for(int i = 0 ; i < 7 ; i++) {
		int sum = i;
		for(int j = 0 ; j+1 < 12 ; j++) {
			if(sum == aa && (sum + arr[j]) % 7 == bb) {
				cout << "YES\n";
				return 0;
			}
			sum = (sum + arr[j]) % 7;
		}
	}
	cout << "NO\n";
	return 0;
}