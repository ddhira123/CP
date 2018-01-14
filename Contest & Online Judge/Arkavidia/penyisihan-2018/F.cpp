#include <bits/stdc++.h>
using namespace std;

const int LG = 17;
const int LEN = 1 << LG;
const int N = 1e5 + 5;

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

int a[N], b[N];
int n, q;

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &b[i]);
    }
}

vector<long long> prepare() {
    vector<Complex> x(LEN+1), y(LEN+1);
    for(int i = 0 ; i < n ; i++) {
        x[a[i]].r += 1;
        y[b[i]].r += 1;
    }

    FFT(x, LEN, 0);
    FFT(y, LEN, 0);

    for(int i = 0 ; i <= LEN ; i++) {
        x[i] = x[i] * y[i];
    }

    FFT(x, LEN, 1);

    vector<long long> ret(LEN+1);

    for(int i = 0 ; i <= LEN ; i++) {
        ret[i] = (long long)(x[i].r / LEN + 0.5);
    }

    return ret;
}

void work() {
    vector<long long> ans = prepare();

    int q; scanf("%d", &q);
    for(int i = 0 ; i < q ; i++) {
        long long x; scanf("%lld", &x);

        long long ret = 0;
        if(x < ans.size()) {
            ret = ans[x];
        }

        printf("%lld\n", ret);
    }
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        work();
    }
    return 0;
}