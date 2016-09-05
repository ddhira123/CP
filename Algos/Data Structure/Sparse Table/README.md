# Sparse Table

Sparse Table adalah struktur data yang berguna ketika semua data sudah diberikan dan tidak terdapat update pada data. Struktur data ini menggunakan prinsip dynamic programming. Misal, untuk tiap query [l,r], kita ingin menghitung f(A[l], A[l+1], ..., A[r]), untuk suatu fungsi f. Maka, kita bisa membuat Sparse Table dengan metode berikut:

- Base case: ST[i][0] = f(A[i]), untuk 1 <= i <= n.
- Rekurens: ST[i][j] = f(ST[i][j-1], f(ST[i + 2<sup>j-1</sup>][j-1])), untuk 1 <= i <= n - 2<sup>j</sup> + 1.

Untuk query, cari x terbesar, sehingga 2<sup>x</sup> <= r - l + 1. Maka, kita bisa mendapat hasil query dengan memanggil f(ST[l][x], ST[r - 2<sup>x</sup> + 1][x]).

Kompleksitas untuk membuat adalah O(N log N), dan untuk query dibutuhkan O(log N) untuk mencari x. Maka, total operasinya jika terdapat Q query adalah O((N + Q) log N).

Contoh soal:

- [SPOJ - RMQSQ](http://www.spoj.com/problems/RMQSQ/)
- [Codeforces - CGCDSSQ](http://codeforces.com/problemset/problem/475/D)
