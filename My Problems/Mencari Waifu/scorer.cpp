#include <bits/stdc++.h>
using namespace std;

const string NO_ANSWER = "-1 -1";
const long long MAX_VAL = 2000;
const long long MIN_VAL = 0;

void wa() {
    puts("WA");
    exit(0);    
}

vector<long long> parse_contestant(int n, string s) {
    stringstream ss(s);
    vector<long long> ret(n);

    for(int i = 0 ; i < n ; i++) {
        if(!(ss >> ret[i])) {
            wa();
        }
    }

    string temp;
    if(ss >> temp) {
        wa();
    }

    return ret;
}

long long calc_pairwise(vector<long long> v) {
	sort(v.begin(), v.end());

	long long pref_sum = 0;
	long long ret = 0;

	for(int i = 0 ; i < v.size() ; i++) {
		ret += (v[i] * i - pref_sum);
		pref_sum += v[i];
	}

	return ret;
}

long long calc_pairwise_manhattan(vector<pair<long long, long long>> v) {
	vector<long long> x, y;

	for(auto it : v) {
		x.push_back(it.first);
		y.push_back(it.second);
	}

	return calc_pairwise(x) + calc_pairwise(y);
}

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    ifstream out(argv[2]);
    ifstream con(argv[3]);
    string dummy;

    int tc; in >> tc;
   
   	for(int t = 1 ; t <= tc ; t++) {
   		int n;
   		long long k;
   		vector<pair<long long, long long>> waifus;

   		in >> n >> k;
   		for(int i = 0 ; i < n ; i++) {
   			int a, b;
   			in >> a >> b;
   			waifus.push_back({a, b});
   		}

   		string judge;
   		getline(out, judge);

   		string contestant;
   		if(!(getline(con, contestant))) {
   			wa();
   		}

   		if(judge == NO_ANSWER) {
   			if(contestant != NO_ANSWER) {
   				wa();
   			}
   		} else {
   			if(contestant == NO_ANSWER) {
   				wa();
   			}
   			
   			vector<long long> ret = parse_contestant(2, contestant);

   			// impossible range
   			if(ret[0] < MIN_VAL || ret[0] > MAX_VAL) {
   				wa();
   			}

   			// impossible range
   			if(ret[1] < MIN_VAL || ret[1] > MAX_VAL) {
   				wa();
   			}

   			waifus.push_back({ret[0], ret[1]});

   			if(calc_pairwise_manhattan(waifus) != k) {
   				wa();
   			}
   		}
   	}

   	if(getline(con, dummy)) {
   		wa();
   	}

    puts("AC");
    return 0;
}