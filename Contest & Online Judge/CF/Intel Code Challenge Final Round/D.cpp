#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

char s[N];
int n, m;
set<int> sets, temp;

int main() {
	scanf("%d",&m);
	scanf("%s",s);
	n = strlen(s);
	for(int i = 0 ; i+m-1 < n ; i++)
		sets.insert(i);
	for(int i = 0 ; i < 26 ; i++) {
		temp = sets;

		for(int j = 0 ; j < n ; j++)
			if(s[j]-'a' == i) {
				vector<int> seen;
				auto it = temp.lower_bound(j-m+1);
				while(it != temp.end() && (*it) <= j) {
					seen.push_back(*it);
					it++;
				}
				for(int x : seen)
					temp.erase(x);
			}

		if(temp.empty()) {
			vector<int> pos;
			for(int j = 0 ; j < n ; j++)
				if(s[j]-'a' == i)
					pos.push_back(j);
			while(!sets.empty()) {
				int cur = *(sets.begin());

				int idx = upper_bound(pos.begin(),pos.end(),cur+m-1) - pos.begin();
				idx = pos[idx-1];
				//printf("%d %d\n",idx,*sets.begin());
				while(!sets.empty() && *sets.begin() <= idx) {
					sets.erase(sets.begin());
				}
				printf("%c",i + 'a');
			}
			break;
		}	
		else {
			for(int j = 0 ; j < n ; j++)
				if(s[j]-'a' == i) {
					vector<int> seen;
					auto it = sets.lower_bound(j-m+1);
					while(it != sets.end() && (*it) <= j) {
						seen.push_back(*it);
						it++;
					}
					for(int x : seen)
						sets.erase(x);
					printf("%c",s[j]);
				}
		}
	}
	puts("");
	return 0;
}