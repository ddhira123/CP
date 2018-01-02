#include <bits/stdc++.h>
using namespace std;

const int LG = 19;
const int N = 200005;
const int OFFSET = 50000;

//typedef long double LD;
#define LD double

struct Complex{
    LD r;
    LD i;
    
    Complex(LD _r = 0,LD _i = 0){
        r = _r;
        i = _i;
    }
    
    Complex operator +(Complex other) const{
        return Complex(r + other.r,i + other.i);
    }
    
    Complex operator -(Complex other) const{
        return Complex(r - other.r,i - other.i);
    }
    
    Complex operator *(Complex other) const{
        return Complex(r * other.r - i * other.i,r * other.i + i * other.r);
    }
};

void FFT(vector<Complex> &poly, int N, bool invert){
    const LD PI = acos(-1.0);
    for(int i = 1, j = 0; i < N ; i++){
        int bit = N >> 1;
        for(; j >= bit ; bit >>= 1)
            j -= bit;
        j += bit;
        if(i < j)
            swap(poly[i], poly[j]);    
    }

    vector<Complex> roots(N+5);

    for(int d = 2 ; d <= N ; d <<= 1){
        int half = d >> 1;
        LD angle = 2.0 * PI / (LD)d * (invert ? -1 : 1);
        Complex wlen = Complex(cos(angle),sin(angle)), u, v;

        roots[0] = Complex(1,0);
        for(int i = 1 ; i < half ; i++)
            roots[i] = roots[i - 1] * wlen;

        for(int i = 0 ; i < N ; i += d){
            for(int j = 0, m = i + half ; j < half ; j++,m++){
                u = poly[i + j];
                v = roots[j] * poly[m];
                poly[i + j] = u + v;
                poly[m] = u - v;
            }
        }
    }
}

int cnt[4 * OFFSET + 5];
long long combined[4 * OFFSET + 5];
int n;

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        int x; scanf("%d", &x);

        cnt[x + OFFSET]++;
    }
}

long long solve() {
    int len = (1 << LG);
    vector<Complex> v(len + 1);

    for(int i = 0 ; i <= 2 * OFFSET ; i++) {
        if(i != OFFSET) v[i].r = cnt[i];
    }

    FFT(v, len, 0);

    for(int i = 0 ; i <= len ; i++) {
        v[i] = v[i] * v[i];
    }

    FFT(v, len, 1);

    for(int i = OFFSET ; i <= 3 * OFFSET ; i++) {
        combined[i - OFFSET] = (long long)(v[i].r / len + 0.5);
    }

    for(int i = 0 ; i <= 2 * OFFSET ; i++) {
        int j = 2 * i - OFFSET;

        if(i != OFFSET && j >= 0) {
            combined[j] -= cnt[i];
        }
    }

    long long ret = 0;

    for(int i = 0 ; i <= 2 * OFFSET ; i++) {
        ret += combined[i] * cnt[i];
    }

    // pake 0
    for(int i = 0 ; i <= 2 * OFFSET ; i++) {
        if(i != OFFSET && cnt[i] >= 2) {
            ret += 2ll * cnt[i] * (cnt[i] - 1) * cnt[OFFSET];
        }
    }

    if(cnt[OFFSET] >= 3) {
        ret += 1ll * cnt[OFFSET] * (cnt[OFFSET] - 1) * (cnt[OFFSET] - 2);
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}