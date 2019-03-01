# Petunjuk Penggunaan Program
<br>
1. Open your terminal from directory that possess this file
2. Type 'make' to compile this program
3. Type './radix_sort threads_count' to run the program
<br>

# Pembagian tugas
- Yuly Haruka Berliana Gunawan / 13516031
	- Parallel the radix sort
	- Main Program
- M. Fadhriga Bestari / 13516154
	- Radix Sort Algorithm
	- Main Program
<br>

# Laporan Pengerjaan
## Deskripsi Solusi Paralel
Pada program yang telah kami buat, pada algortima radix sort terdapat banyak looping untuk mencari flag, index down, index up, dan permutasi dalam proses radix sort. Setiap looping yang terjadi pada radix sort bersifat independen ( data pada looping tidak bergantung pada looping lainnya ) kecuali looping pada proses pengisian index down dan index up. Maka dari itu, kami mengimplementasikan OpenMP paralel pada looping yang terdapat pada algoritma radix sort sehingga per-looping nya akan dibagi menjadi banyak nya thread yang diinginkan. 
<br>

## Analisis Solusi
Menurut kami, penerapan OpenMP paralel pada radix sort dapat mempercepat proses sorting karena dengan dilakukannya pembagian proses pada setiap thread, proses pengisian array flag dan proses permutasi yang dilakukan dalam radix sort dipercepat.
<br>

## Jumlah thread yang digunakan
Jumlah thread yang digunakan adalah 4 karena sesuai dengan core yang dialokasikan pada Virtual Machine yang kami gunakan untuk menjalankan program. 
<br>

## Pengukuran Kinerja
<br>

- N = 5000 dengan thread = 4
Uji Coba 1
Radix Sort dengan paralel : 21672 ms
Radix Sort dengan serial : 23079 ms

Uji Coba 2
Radix Sort dengan paralel : 21409 ms
Radix Sort dengan serial : 22530 ms

Uji Coba 3
Radix Sort dengan paralel : 19414 ms
Radix Sort dengan serial : 20562 ms

- N = 50000 dengan thread = 4
Uji Coba 1
Radix Sort dengan paralel : 105996 ms
Radix Sort dengan serial : 117882 ms

Uji Coba 2
Radix Sort dengan paralel : 106440 ms
Radix Sort dengan serial : 118108 ms

Uji Coba 3
Radix Sort dengan paralel : 105162 ms
Radix Sort dengan serial : 122656 ms

- N = 100000 dengan thread = 4
Uji Coba 1
Radix Sort dengan paralel : 220076 ms
Radix Sort dengan serial : 244303 ms

Uji Coba 2
Radix Sort dengan paralel : 195386 ms
Radix Sort dengan serial : 218235 ms

Uji Coba 3
Radix Sort dengan paralel : 195626 ms
Radix Sort dengan serial : 219280 ms

- N = 200000 dengan thread = 4
Uji Coba 1
Radix Sort dengan paralel : 450837 ms
Radix Sort dengan serial : 495986 ms

Uji Coba 2
Radix Sort dengan paralel : 387034 ms
Radix Sort dengan serial : 433822 ms

Uji Coba 3
Radix Sort dengan paralel : 362393 ms
Radix Sort dengan serial : 408307 ms

- N = 400000 dengan thread = 4
Uji Coba 1
Radix Sort dengan paralel : 946567 ms
Radix Sort dengan serial : 1.04382e+06 ms

Uji Coba 2
Radix Sort dengan paralel : 705935 ms
Radix Sort dengan serial : 807857 ms

Uji Coba 3
Radix Sort dengan paralel : 712231 ms
Radix Sort dengan serial : 801536 ms
<br>
## Analisis Perbandingan kinerja serial dan paralel
Berdasarkan hasil uji coba yang telah dilakukan, untuk setiap N, kinerja dari radix sort paralel lebih baik dibandingkan dengan radix sort serial. Rata-rata perbedaan waktu antara keduanya adalah 0.1 s