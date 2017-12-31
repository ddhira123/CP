#include <bits/stdc++.h>
using namespace std;

int convert_from_octal(string x) {
    int ret = 0;
    int pwr = 1;

    for(char ch : x) {
        ret += pwr * (ch - '0');
        pwr *= 8;
    }

    return ret;
}

string convert_to_hexa(int x) {
    string ret = "";

    for(int i = 0 ; i < 3 ; i++) {
        int res = x % 16;
        x /= 16;

        if(res < 10) ret += ('0' + res);
        else ret += ('A' + res - 10);
    }

    return ret;
}

int main() {
    string s; cin >> s;
    reverse(s.begin(), s.end());

    string cur = "";
    string ret = "";

    for(char ch : s) {
        cur += ch;
        if(cur.length() == 4) {
            ret += convert_to_hexa(convert_from_octal(cur));
            cur = "";
        }
    }

    if(cur.length() > 0) {
        ret += convert_to_hexa(convert_from_octal(cur));
    }

    while(ret.length() > 1 && ret[ret.length()-1] == '0') {
        ret.erase(ret.begin() + ret.length() - 1);
    }

    reverse(ret.begin(), ret.end());
    
    cout << ret << endl;
    return 0;
}