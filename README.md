# Shop Transaction and Database System in C
- Deskripsi
- Fitur Utama
- Cara Penggunaan

## Deskripsi
Program "Shop Transaction and Database System in C" adalah sebuah sistem yang dirancang untuk memudahkan pengelolaan transaksi dan basis data di toko. Dengan menggunakan bahasa pemrograman C, program ini bertujuan untuk menjalankan fungsi merekam, mengelola, dan melacak transaksi penjualan serta informasi produk di sebuah toko. Dalam program ini terdapat 2 mode, yaitu mode admin dan mode pelanggan.

## Fitur Utama
1. Manajemen Barang:
   - Fitur untuk menambah, mengedit, dan menghapus barang dari database.
   - Menyimpan informasi barang seperti ID, nama, stok, dan harga.
   - Implementasikan filter untuk mempermudah pencarian barang.

2. Manajemen Membership:
   - Fitur untuk menambah, mengedit, dan menghapus membership dari database.
   - Menyimpan informasi member seperti ID, username, password, nama, no telp, alamat, tanggal regist, dan saldo.
   - Implementasi filter untuk mempermudah pencarian member.
   - Fitur top up saldo dan edit data diri bagi pengguna yang telah mendaftar membership.

3. Transaksi Penjualan:
   - Pelanggan dapat memilih barang untuk dimasukkan ke keranjang untuk dibeli.
   - Hitung total pembelian dan perbarui stok produk setelah transaksi sukses.
   - Menyimpan riwayat transaksi dan struk yang bisa dilihat di mode admin.

4. Tampilan Antarmuka:
   - Input arrow atas dan bawah pada keyboard untuk memilih aksi.
   - Input string yang dibatasi sesuai keperluan (cnth: input khusus huruf, input khusus angka, dsb).
   - Tampilan berwarna.
   - Data barang, member, dan transaksi ditampilkan dalam tabel

## Cara Penggunaan
### Pra-syarat:
- Pastikan compiler C (seperti GCC) sudah terinstal di sistem Anda.
- Karena program memanfaatkan ANSI escape sequences untuk mendukung tampilan, aktifkan ANSI escape sequences terlebih dahulu dengan cara mengetikkan
  ```reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1``` di CMD. Sebagai informasi tambahan, ketikkan ```reg delete HKCU\Console /v VirtualTerminalLevel /f``` di CMD untuk menonaktifkan ANSI escape sequences.
- Download source code dan file lainnya [di sini]().

### Instalasi:
- Ekstrak file .zip yang sebelumnya didownload.
- Jalankan file ```main.exe```. Jika file ```main.exe``` bermasalah, compile file ```main.c``` untuk mendapatkan file ```main.exe``` yang baru.
- Cara compile:
  - Menggunakan C/C++ IDE
  - Menggunakan CMD
    1. Buka CMD di directori saat ini.
    2. Ketik ```gcc main.c -o main```.
    3. Kemudian jalankan file ```main.exe```.

### Menjalankan Aplikasi:
1. Jalankan file ```main.exe```.
2. Tekan arrow atas dan bawah serta ```Enter``` pada keyboard untuk menentukan pilihan.
3. Tekan ```Esc``` untuk membatalkan proses atau kembali ke halaman berikutnya.
4. Untuk login ke mode admin, gunakan username ```admin1``` dan password ```123```.
5. Untuk tampilan yang lebih baik, jalankan program dalam ukuran layar lebar atau full screen.

## Pengembang
Proyek ini dikembangkan oleh:
[Muh Buyung Saloka](https://instagram.com/mbsaloka)
