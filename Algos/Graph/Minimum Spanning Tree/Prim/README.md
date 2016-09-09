# Prim's

Algoritma ini merupakan salah satu algo yang sering dipakai untuk mencari MST dan varian-variannya. Algo ini menggunakan strategi greedy, yaitu mengekspansi component, dengan menggunakan edge termurah.

Terdapat 2 implementasi untuk algo ini, masing-masing bekerja dalam O((E+V) log E) dan O(V<sup>2</sup>). Pada saat grafnya sparse, O((E+V) log E) berjalan lebih cepat. Namun, ketika grafnya dense (contohnya complete graph), maka O(V<sup>2</sup>) berjalan lebih cepat. 

## O((E+V) log E)

Algo O((E+V) log E) memanfaatkan priority_queue dengan prioritas cost minimal. Awalnya, buat sebuah dummy edge, dengan cost tak hingga, dan terhubung pada vertex pertama. Perhatikan, seandainya yang ingin dicari adalah Minimum Spanning Forest, kita cukup mengubah sehingga tedapat V buah dummy edge, Kemudian, proses isi priority_queue. Ambil topnya. Ada beberapa kasus:

- Apabila ternyata vertex sudah diambil, skip.
- Apabila ternyata cost-nya tak hingga, ubah costnya menjadi 0. Dummy edge ini menandai awal suatu komponen. 

Selanjutnya, ambil edge (sekaligus vertex) tersebut dan catat costnya. Lalu, lakukan ekspansi, masukkan edge-edge yang terhubung dengan vertex tersebut ke priority_queue. Ulangi sampai semua vertex diambil.

## O(V<sup>2</sup>)

Buat sebuah array minDist[], dengan minDist[x] adalah cost termurah yang menghubungkan x dengan component saat ini. Awalnya, minDist[] bernilai tak hingga semua. Lalu, buat minDist[vertex_pertama] menjadi 0. Lalu, jalankan langkah-langkah berikut:

1. Cari vertex yang belum diambil, dengan minDist[] terkecil.
2. Seandainya semua vertex sudah diambil, berhenti.
3. Jika tidak, artinya kita akan mengambil vertex tersebut, sebut saja y. Apabila minDist[y] bernilai tak hingga, berhenti, karena tidak ada vertex yang menghubungkan pada component sekarang ke y. Namun, apabila ingin mencari Minimum Spanning Forest, jangan berhenti, namun ubah minDist[y] menjadi 0.
4. Tambahkan minDist[y] pada total cost dan tandai y sebagai sudah diambil.
5. Ekspansi y, untuk setiap vertex v, minDist[v]=min(minDist[v],cost[y][v]).
6. Kembali ke langkah 1.