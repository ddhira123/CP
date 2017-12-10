#include <bits/stdc++.h>
using namespace std;

int psum[50005];
int n, k;
string s;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    cin >> n >> k;
    cin >> s;
    s = "." + s;
    for(int i = 1 ; i < s.length() ; i++) {
        psum[i] = psum[i-1] + (s[i] == ')');
    }

    long long atas = 0;
    long long bawah = 0;
    for(int i = 1 ; i < s.length() ; i++) {
        int kanan = i + k;
        kanan = min(kanan, (int)s.length()-1);

        bawah += kanan - i;
        if(s[i] == '(')
            atas += psum[kanan] - psum[i];
    }

    bawah = max(bawah, 1ll);
    long long fpb = gcd(atas, bawah);
    atas /= fpb;
    bawah /= fpb;
    cout << atas << "/" << bawah << endl;
    return 0;
}