#include <bits/stdc++.h>
using namespace std;

double arr[15];
int n;

vector<char> op;
vector<double> operand;
string s;

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; i++) cin >> arr[i];
	cin >> s;
	for(int i = 0 ; i < s.length() ; ) {
		//cout << i << " " << s[i] << endl;
		if(s[i] == 'R') {
			operand.push_back(arr[s[i + 1] - '0']);
			i += 2;
		}
		else if(s[i] == ')') {
			if(op.back() == '(') {
				op.pop_back();
			}
			else if(op.back() == '-') {
				//printf("adding\n");
				double ret = 0;
				while(op.back() != '(') {
					ret += operand.back();
					operand.pop_back();
					op.pop_back();
				}
				operand.back() += ret;
				op.pop_back();
			}
			else {
				double ret = 0;
				while(op.back() != '(') {
					ret += 1 / operand.back();
					operand.pop_back();
					op.pop_back();
				}
				ret += 1 / operand.back();
				operand.pop_back();
				op.pop_back();
				operand.push_back(1 / ret);
			}
			i++;
		}
		else {
			//printf("put %c\n",s[i]);
			op.push_back(s[i]);
			i++;
		}
	}	
	printf("%.10lf\n",operand.back());	
	return 0;
}