#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)

const int MAXN = 5e5 + 5;

class base {
	double re, im;

	public:
		base() {re = im = 0;}
		base(int v) {re = v; im = 0;}
		base(double a, double b) {re = a; im = b;}
		double real() {return re;}
		double imag() {return im;}
		base operator *= (base z) {
			const double r = re * z.real() - im * z.imag();
			im = re * z.imag() + im * z.real();
			re = r;
			return *this;
		}

		base operator *(const base b) {
			base tmp = *this;
			tmp *= b;
			return tmp;
		}

		base operator +=(base z) {
			re += z.real();
			im += z.imag();
			return *this;
		}

		base operator +(const base b) {
			base tmp = *this;
			tmp += b;
			return tmp;
		}

		base operator -=(base z) {
			re -= z.real();
			im -= z.imag();
			return *this;
		}

		base operator -(const base b) {
			base tmp = *this;
			tmp -= b;
			return tmp;
		}

		base operator /=(double z) {
			re /= z;
			im /= z;
			return *this;
		}
};

int rev (int num, int lg_n) {
	int res = 0;
	for(int i = 0 ; i < lg_n ; i++)
		if(num & (1 << i))
			res |= (1 << (lg_n-1-i));
	return res;
}

void fft(vector<base> &a, bool invert) {
	int n = (int)a.size();
	int lg_n = 0;
	while((1 << lg_n) < n) lg_n++;

	for(int i = 0 ; i < n ; i++)
		if(i < rev(i, lg_n)) {
			swap(a[i], a[rev(i, lg_n)]);
		}

	for(int len = 2; len <= n ; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));

		for(int i = 0 ; i < n ; i += len) {
			base w(1);
			for(int j = 0 ; j < len/2 ; j++) {
				base u = a[i+j], v = a[i+j+len/2] * w;

				a[i+j] = u+v;
				a[i+j+len/2] = u-v;
				w *= wlen;
			}
		}
	}

	if(invert) {
		for(int i = 0 ; i < n ; i++) {
			a[i] /= n;
		}
	}
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

	size_t n = 1;
	while(n < max(fa.size(), fb.size())) n <<= 1;
	n <<= 1;

	// for(int i = 0 ; i < n ; i++)
	// 	cout << fa[i].real() << " " << fa[i].imag() << endl;

	fa.resize(n); fb.resize(n);

	fft(fa, false);
	fft(fb, false);
	for(int i = 0 ; i < n ; i++)
		fa[i] *= fb[i];

	fft(fa, true);
	res.resize(n);
	for(int i = 0 ; i < n ; i++)
		res[i] = (int)(fa[i].real() + 0.5);
}

vector<int> init_ways() {
	vector<int> res(MAXN, 0);

	for(int i = 1 ; i < MAXN ; i++)
		for(int j = i ; j < MAXN ; j += i)
			res[j]++;

	vector<int> res2 = res;
	vector<int> ways;

	// for(int i = 1 ;i <= 10 ; i++)
	// 	cout << i << " " << res[i] << endl;

	multiply(res, res2, ways);

	// for(int i = 1 ;i <= 10 ; i++)
	// 	cout << i << " " << ways[i] << endl;

	return ways;
}

vector<int> arr;
int stree[4*MAXN];

void build(int id, int l, int r) {
	if(l == r) {
		stree[id] = l;
	} else {
		int m = (l + r) / 2;
		int chld = id << 1;

		build(chld, l, m);
		build(chld+1, m+1, r);

		stree[id] = arr[stree[chld]] > arr[stree[chld+1]] ? stree[chld] : stree[chld+1];
	}
}

int query(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y) {
		return stree[id];
	} else {
		int m = (l + r) / 2;
		int chld = id << 1;

		int r1 = -1;
		int r2 = -1;

		if(x <= m) r1 = query(chld, l, m, x, y);
		if(y > m)  r2 = query(chld+1, m+1 ,r, x, y);

		if(r2 == -1) return r1;
		if(r1 == -1) return r2;
		return arr[r1] > arr[r2] ? r1 : r2;
	}
}

int main() {
	arr = init_ways();
	build(1, 1, MAXN-1);

	int n; cin >> n;
	for(int i = 0 ; i < n ; i++) {
		int l, r;
		cin >> l >> r;

		int ret = query(1, 1, MAXN-1, l, r);
		cout << ret << " " << arr[ret] << endl;
	}
	return 0;
}