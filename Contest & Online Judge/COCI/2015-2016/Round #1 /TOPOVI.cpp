#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
#define mp make_pair

int n,k,q;
long long ans;
map<int,int> colWithVal;
map<int,int> rowWithVal;
map<int,int> row;
map<int,int> col;
map<pair<int,int> ,int> inPosition;
int r[N],c[N],pwr[N];

int main(){
	scanf("%d %d %d",&n,&k,&q);
	colWithVal[0] = n;
	rowWithVal[0] = n;
	for(int i = 1 ; i <= k ; i++){
		scanf("%d %d %d",&r[i],&c[i],&pwr[i]);
		int rr = r[i];
		int cc = c[i];
		
		if(colWithVal.count(row[rr]))
			ans -= (n - colWithVal[row[rr]]);
		else
			ans -= n;	

		if(rowWithVal.count(col[cc]))
			ans -= (n - rowWithVal[col[cc]]);
		else
			ans -= n;
		
		if(row[rr] ^ col[cc]) ans++;				
		//cout << ans << endl;
			
		colWithVal[col[cc]]--;
		col[cc] ^= pwr[i];
		colWithVal[col[cc]]++;
		
		rowWithVal[row[rr]]--;
		row[rr] ^= pwr[i];
		rowWithVal[row[rr]]++;
		
		//cout << row[rr] << endl;
		
		if(colWithVal.count(row[rr]))
			ans += (n - colWithVal[row[rr]]);
		else
			ans += n;
					
		if(rowWithVal.count(col[cc]))
			ans += (n - rowWithVal[col[cc]]);
		else
			ans += n;		
		
		if(row[rr] ^ col[cc]) ans--;
		
		inPosition[mp(rr,cc)] = i;		
		//printf("%lld\n",ans);	

	}
	for(int i = 1 ; i <= q ; i++) {
		int a,b,rr,cc;
		scanf("%d %d %d %d",&a,&b,&rr,&cc);
		int idx = inPosition[mp(a,b)];

		if(colWithVal.count(row[r[idx]]))
			ans -= (n - colWithVal[row[r[idx]]]);
		else
			ans -= n;	

		if(colWithVal.count(row[rr]))
			ans -= (n - colWithVal[row[rr]]);
		else
			ans -= n;			

		if(rowWithVal.count(col[c[idx]]))
			ans -= (n - rowWithVal[col[c[idx]]]);
		else
			ans -= n;	

		if(rowWithVal.count(col[cc]))
			ans -= (n - rowWithVal[col[cc]]);
		else
			ans -= n;
		
		if(row[r[idx]] ^ col[c[idx]]) ans++;
		if(row[r[idx]] ^ col[cc]) ans++;
		if(row[rr] ^ col[c[idx]]) ans++;
		if(row[rr] ^ col[cc]) ans++;						
		
		//cout << ans << endl;
				
		colWithVal[col[c[idx]]]--;
		col[c[idx]] ^= pwr[idx];
		colWithVal[col[c[idx]]]++;
		
		rowWithVal[row[r[idx]]]--;
		row[r[idx]] ^= pwr[idx];
		rowWithVal[row[r[idx]]]++;
		
		colWithVal[col[cc]]--;
		col[cc] ^= pwr[idx];
		colWithVal[col[cc]]++;
		
		rowWithVal[row[rr]]--;
		row[rr] ^= pwr[idx];
		rowWithVal[row[rr]]++;
		
		if(colWithVal.count(row[r[idx]]))
			ans += (n - colWithVal[row[r[idx]]]);
		else
			ans += n;	

		if(colWithVal.count(row[rr]))
			ans += (n - colWithVal[row[rr]]);
		else
			ans += n;							

		if(rowWithVal.count(col[c[idx]]))
			ans += (n - rowWithVal[col[c[idx]]]);
		else
			ans += n;	

		if(rowWithVal.count(col[cc]))
			ans += (n - rowWithVal[col[cc]]);
		else
			ans += n;
		
		if(row[r[idx]] ^ col[c[idx]]) ans--;
		if(row[r[idx]] ^ col[cc]) ans--;
		if(row[rr] ^ col[c[idx]]) ans--;
		if(row[rr] ^ col[cc]) ans--;			
		
		r[idx] = rr;
		c[idx] = cc;
		inPosition[mp(rr,cc)] = idx;
		printf("%lld\n",ans);	
	}
	return 0;
}
