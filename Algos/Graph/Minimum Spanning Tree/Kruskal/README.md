# Kruskal's

Algoritma ini merupakan salah satu algo yang sering dipakai untuk mencari MST dan varian-variannya. Algo ini bisa dibilang memakai observasi greedy. Observasi penting pada algo ini:

- Pada tree tidak ada cycle. Sehingga, kita bisa menambahkan edge satu per satu, selama ini tidak menyebabkan munculnya cycle.
- Memanfaatkan observasi di atas, kita bisa mengurutkan edge, dan selalu memasukkan yang harganya paling murah serta tidak menyebabkan munculnya cycle.

Kemudian, cara untuk mengaplikasikan kedua observasi tersebut:

- Mengecek cycle bisa dilakukan dengan Disjoint Set. Apabila penambahan edge akan membuat cycle, pasti edge tersebut menghubungkan dua vertex yang berada pada component yang sama.
- Sort saja edgenya.

Sehingga, kompleksitas akhir untuk algo ini adalah O(E log E).