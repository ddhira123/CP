# Modular Exponentiation

Perpangkatan Modular adalah salah satu algoritma untuk melakukan perpangkatan secara cepat. Bentuk umumnya, diberikan a, b, c, hitung a<sup>b</sup> mod c. Terdapat 2 cara mengimplementasikan algoritma ini, yaitu rekursif dan iteratif.

Rekursif:
- jika b=0, a<sup>b</sup> = 1 mod c
- jika b mod 2 = 1, a<sup>b</sup> mod c = (a * a<sup>b-1</sup>) mod c
- jika b mod 2 = 0, a<sup>b</sup> mod c = (a<sup>b/2</sup>)<sup>2</sup> mod c

Iteratif:
Hitung a<sup>1</sup>, a<sup>2</sup>, a<sup>4</sup> dan seterusnya. Nyatakan b dalam basis 2, misal hasilnya b<sub>k</sub>b<sub>k-1</sub>...b<sub>0</sub>. Maka, a<sup>b</sup> mod c dapat dihitung sebagai b<sub>k</sub>*2<sup>k</sup> + b<sub>k-1</sub>*2<sup>k-1</sup> + ... + b<sub>0</sub>*2<sup>0</sup> mod c.