# Disjoint Set

Disjoint Set adalah struktur data yang biasa dipakai untuk merepresentasikan keterhubungan dalam graf. Suatu komponen yang terhubung dinyatakan oleh salah satu nodenya, yang kadang disebut root. Root dinyatakan sebagai node yang memiliki parent dirinya sendiri. 

Dalam mencari root dari suatu node, kita bisa men-traverse parent dari node, hingga kita mencapai root. Dalam pencarian, ada baiknya kita melakukan path compression, atau mengeset nilai dari parent semua node yang di-traverse menjadi root.

Menggabungkan dua komponen berbeda dapat dilakukan dengan mudah. Misal root dari komponen yang ingin digabungkan adalah u dan v. Maka, kita tinggal mengeset parent dari u menjadi v, atau sebaliknya. Terdapat satu optimisasi dalam menentukan yang mana yang dijadikan parent, yaitu rank. Namun, biasanya tanpa rank juga jalannya sudah cukup cepat, :v.

Apabila dilakukan penggabungan semua node, dengan path compression namun tanpa rank, kompleksitasnya O(N log N). Dengan rank, kompleksitasnya menjadi amortized O(N \alpha(N)).

Contoh soal:

- [UVa - Friends](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1549)
- [SPOJ - LEXSTR](http://www.spoj.com/problems/LEXSTR/)
- [Codeforces - Brain Network (easy)](http://codeforces.com/problemset/problem/690/C1)
- [Codeforces - Vessels](http://codeforces.com/problemset/problem/371/D)
