#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

struct data {
	int day;
	int month;
	int year;
	int id;

	bool operator <(data other) const {
		if(year == other.year) {
			if(month == other.month) {
				if(day == other.day)
					return id < other.id;
				return day < other.day;
			}
			return month < other.month;
		}
		return year < other.year;
	}

	int getAge(data other) {
		int ret = other.year - year;
		if(other.month < month || (other.month == month && other.day < day))
			ret--;
		return ret;
	}

	void read() {
		cin >> day >> month >> year;
	}
};

data arr[105];
int n;

int main() {
	OPEN("king");
	arr[0].read();
	cin >> n;
	for(int i = 1 ; i <= n ; i++) arr[i].read(), arr[i].id = i;
	sort(arr + 1,arr + n + 1);
	for(int i = n ; i >= 1 ; i--)
		if(arr[i].getAge(arr[0]) >= 18) {
			cout << arr[i].id << "\n";
			return 0;
		}
	cout << "-1\n";	
	CLOSE();
	return 0;
}