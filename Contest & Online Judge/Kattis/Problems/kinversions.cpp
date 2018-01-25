#include <bits/stdc++.h>
using namespace std;

const int LG = 21;
const int MAXN = 1 << LG;

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

char s[MAXN];

int main(){
    scanf("%s", s);
    int len = strlen(s);

    vector<Complex> a(MAXN), b(MAXN);

    for(int i = 0 ; i < len ; i++) {
        if(s[i] == 'A') {
            a[i].r = 1;
        } else {
            b[len-i].r = 1;
        }
    }

    FFT(a, MAXN, 0);
    FFT(b, MAXN, 0);
    for(int i = 0 ; i < MAXN ; i++) {
        a[i] = a[i] * b[i];
    }
    FFT(a, MAXN, 1);

    for(int i = 1 ; i < len ; i++) {
        printf("%d\n", (int)(a[i+len].r / MAXN + 0.5));
    }

    return 0;
}