#include <bits/stdc++.h>
using namespace std;

map<string,int> mp;

void init() {
	mp["Kamen"] = 0;
	mp["Rock"] = 0;
	mp["Pierre"] = 0;
	mp["Stein"] = 0;
	mp["Ko"] = mp["Koe"] = 0;
	mp["Sasso"] = mp["Roccia"] = 0;
	mp["Guu"] = 0;
	mp["Kamien"] = 0;
	mp["Piedra"] = 0;

	mp["Nuzky"] = 1;
	mp["Scissors"] = 1;
	mp["Ciseaux"] = 1;
	mp["Schere"] = 1;
	mp["Ollo"] = 1;
	mp["Olloo"] = 1;
	mp["Forbice"] = 1;
	mp["Choki"] = 1;
	mp["Nozyce"] = 1;
	mp["Tijera"] = 1;

	mp["Papir"] = 2;
	mp["Paper"] = 2;
	mp["Feuille"] = 2;
	mp["Papier"] = 2;
	mp["Papir"] = 2;
	mp["Carta"] = mp["Rete"] = 2;
	mp["Paa"] = 2;
	mp["Papier"] = 2;
	mp["Papel"] = 2;
}

int main() {
	init();
	string str = "-";
	int tc = 1;
	while(str[0] != '.') {
		string a, b;
		cin >> str >> a;
		cin >> str >> b;

		int x = 0, y = 0;
		while(cin >> str) {
			if(str == "-" || str == ".") break;
			string str2; cin >> str2;

			int sc1 = mp[str];
			int sc2 = mp[str2];

			if(sc1 == sc2) continue;
			if((sc1+1) % 3 == sc2) x++;
			else y++;
		}

		cout << "Game #" << tc++ << ":\n";
		
		cout << a << ": " << x << " point";
		if(x != 1) cout << "s";
		cout << "\n";

		cout << b << ": " << y << " point";
		if(y != 1) cout << "s";
		cout << "\n";

		if(x == y) cout << "TIED GAME\n";
		else {
			cout << "WINNER: ";
			if(x > y) cout << a << "\n";
			else cout << b << "\n";
		}

		cout << "\n";
	}
	return 0;
}