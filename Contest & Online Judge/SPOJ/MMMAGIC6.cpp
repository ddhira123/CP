#include <bits/stdc++.h>
using namespace std;

const int N = 725;
const int K = 6;

vector<int> permut[125];

int fact(int x) {
	int res = 1;
	for(int i = 2 ; i <= x ; i++)
		res *= i;
	return res;	
}

void init() {
	vector<int> v;
	for(int i = 0 ; i < K - 1 ; i++)
		v.push_back(i);
	int cntr = 0;
	
	do{
		permut[cntr++] = v;
	}while(next_permutation(v.begin(),v.end()));	
}

pair<int,vector<int> > solveMickey(vector<int> v) {
	vector<int> kopy = v;
	kopy.push_back(0);
	sort(kopy.begin(),kopy.end());
	
	int sum = 0;
	for(int x : v)
		sum += x;
	sum %= K;
	
	int tgt = kopy[sum + 1];
	int sisa = (sum + K - tgt) % K;	
	int urutan = 0;
	
	for(int i = 1 ; i <= sum + 1 ; i++) {
		int cur = kopy[i];
		int prv = kopy[i - 1];
		//printf("%d %d\n",cur,prv);
		
		int y = ((i - 1) - sisa + K) % K;
		
		int sisCur = cur % K;
		int sisPrv = prv % K;
		
		int addCur = (y - sisCur + K) % K;
		int addPrv = (y - sisPrv + K) % K;
		
		cur += addCur;
		prv -= ((K - addPrv) % K);
		
		int inter = (cur - prv) / K - 1;
		urutan += inter;	
	}
	
	vector<int> res;
	kopy.erase(kopy.begin() + sum + 1);
	for(int i = 0 ; i < K - 1 ; i++) {
		res.push_back(kopy[permut[urutan][i] + 1]);
		//printf("%d%c",res.back(),i + 1 == K - 1 ? '\n' : ' ');
	}	
	return {tgt,res};	
}

int solveDonald(vector<int> v) {
	vector<int> kopy = v;
	kopy.push_back(0);
	kopy.push_back(N + 1);
	sort(kopy.begin(),kopy.end());
	
	int urutan = 0;
	int mul = fact(K - 1);
	int tot = 0;
	
	for(int i = 0 ,iter = K - 1 ; i + 1 < v.size() ; i++, iter--) {
		mul /= iter;
		tot += (v[i]);
		for(int j = i + 1 ; j < v.size() ; j++)
			if(v[i] > v[j])
				urutan += mul;
	}
	
	tot += v.back();
	
	//for(int x : kopy)
	//	printf("yey %d\n",x);
	
	tot %= K;
	urutan++;
	//printf("tot %d urutan %d\n",tot,urutan);
	
	for(int i = 1 ; i < kopy.size() ; i++) {
		int cur = kopy[i];
		int prv = kopy[i - 1];
		//printf("%d %d\n",cur,prv);
		
		int y = ((i - 1) - tot + K) % K;
		
		int sisCur = cur % K;
		int sisPrv = prv % K;
		
		int addCur = (y - sisCur + K) % K;
		int addPrv = (y - sisPrv + K) % K;
		
		cur += addCur;
		prv -= ((K - addPrv) % K);
		
		int inter = (cur - prv) / K - 1;
		//printf("y %d cur %d prv %d\n",y,cur,prv);
		if(inter >= urutan) {
			return prv + K * urutan;
		}
		else {
			urutan -= inter;
		}
	}
	
	assert(0);
	return -1;
}

int main() {
	init();
	int m,d;
	scanf("%d %d",&m,&d);
	
	for(int i = 0 ; i < m ; i++) {
		vector<int> v;
		for(int i = 0 ; i < K ; i++) {
			int x;
			scanf("%d",&x);
			v.push_back(x);
		}
		
		pair<int,vector<int> > res = solveMickey(v);
		for(int j = 0 ; j < res.second.size() ; j++)
			printf("%d%c",res.second[j],j + 1 == res.second.size() ? '\n' : ' ');
	}
	
	for(int i = 0 ; i < d ; i++) {
		vector<int> v;
		for(int i = 0 ; i < K - 1 ; i++) {
			int x;
			scanf("%d",&x);
			v.push_back(x);		
		}
		
		printf("%d\n",solveDonald(v));
	}
	return 0;
}